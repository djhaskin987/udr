(ns udr.core)
;; supposing we add provides.
;; provides: name, version -> name, version
;; (a(>3&<2)&b(>3&<2))|
;; a|b>2&b<2|c&c|d&d|e ->
;; a&b&c&d | b&c&d&e via
;; a>1&a<1 is valid input, but returns unsatisfiable
;;  requirement ->_     _<- possibilities: requirement
;; to-install: (setof (name -> setof (string, relation, pattern)))
;; already-installed: (name -> version)
;; conflicts: name -> setof (string, relation, pattern)
;; returns: setof {:packages (name -> {:version vers, :url url}), :conflicts (name -> setof (string, relation, version))}
;; As coded, this does not keep track of conflicts picked up along the way.
(defun resolve [requirements
                already-installed
                conflicts
                query]
  (if (or (empty? requirements)
          (null? requirements)
          #{}
          ;; I'm sure i could turn this if/else unwrap into a reduce.
          (let [possibilities (first requirements)
                other-requirements (rest requirements)
                solutions
                (reduce
                 (fn [solutions-so-far
                      possibility]
                   (let [name (key possibility)
                         version (val possibility)]
                     (cond (contains? already-installed name)
                           (if (let [already-installed-version (get already-installed name)]
                                 (reduce
                                  (fn [satisfies-so-far test]
                                    (and
                                     satisfies-so-far
                                     (let [[string relation pattern] test]
                                       (relation
                                        already-installed-version
                                        pattern))))
                                  true
                                  constraints))
                             ;; need to test for a|b where both a and b are already installed
                             ;; to make sure the following line doesn't blow up in my face
                             (conj solutions-so-far {:packages {} :conflicts {}})
                             solutions-so-far)
                           (and (contains? conflicts name)
                                (reduce (fn [conflicts-so-far
                                             test]
                                          (and
                                           conflicts-so-far
                                           (let [[string relation pattern] test]
                                             (relation
                                              version
                                              pattern))))
                                        true
                                        conflicts))
                           solutions-so-far
                           :else
                           (let [non-possibilities
                                 (dissoc possibilities (key possibility))]
                             ;; *DO NOT* put the non-possibilities in the set of conflicts returned
                             ;; you could, but then we'd return them ultimately, which would be bad.
                             ;; also, they'll get filtered out anyway I think.
                             (reduce
                              (fn [cum-solutions-so-far
                                   candidate]
                                (let [{:version candidate-version
                                       :url candidate-url
                                       :conflicts candidate-conflicts
                                       :depends candidate-depends} candidate
                                      ;; match to see if candidate is in conflict first, if not,
                                      ;; then go get it.
                                      (resolve candidate-depends
                                               (assoc already-installed
                                                      name
                                                      candidate-version)
                                               (into conflicts candidate-conflicts
                                                     non-possibilities)
                                               query) candidate-result]
                                  (if (= candidate-result :unsatisfiable)
                                    cum-solutions-so-far
                                    (reduce
                                     (fn [solutions-so-far
                                          solution]
                                       (conj solutions-so-far
                                             (let [{:packages solution-packages
                                                    :conflicts solution-conflicts}
                                                   solution]
                                               {:packages (assoc solution-packages name
                                                                 {:versoin candidate-version
                                                                  :url candidate-url})
                                                :conflicts
                                                (into solution-conflicts candidate-conflicts)})))
                                     cum-solutions-so-far
                                     candidate-result)))))
                             solutions-so-far
                             (query name))))))
                #{}
                possibilities)]
          (if (and
               (empty solutions)
               (not (empty requirements))
               (reduce (fn [result possibilities]
                         (and result
                              (not (empty possibilities))))
                       true
                       possibilities))
            :unsatisfiable
            (reduce
             (fn [total-solutions-so-far
                  sub-solution]
               (let [{:packages sub-solution-packages
                      :conflicts sub-solution-conflicts} sub-solution
                     resolved-solution
                     (resolve
                      other-requirements
                      ;; sub-solution-conflicts does *NOT* include the pseudo-conflicts of the other neighbors
                      ;; this may cause problems and is at best an optimization
                      (into conflicts (sub-solution-conflicts))
                      (into already-installed
                            (reduce-kv (fn [m k v]
                                         (assoc m k (:version v)))
                                       {}
                                       sub-solution-packages)))]
                 (if (= :unsatisfiable resolved-solution)
                   total-solutions-so-far
                   (let [{:packages resolved-solution-packages
                          :conflicts resolved-solution-conflicts} resolved-solution]
                     (conj
                      total-solutions-so-far
                      {:packages
                       (into resolved-solution-packages sub-solution-packages)
                       :conflicts
                       (into resolved-solution-conflicts sub-solution-conflicts)}))))
               (conj total-solutions-so-far
                     resolved-solution))
             #{}
             solutions)))))
