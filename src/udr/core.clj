(ns udr.core)
;; supposing we add provides.
;; provides: name, version -> name, version

;; requirements used to be setof(setof), but I changed
;; it to listof(listof). setof(setof) implied
;; nondeterminism. Therein lies madness.
;; Instead, I went with lists. Determinism is good,
;; and the users probably will like it.

;;    requirements ->_     _<- possibilities: requirement
;; requirements: (listof (name -> listof (string, relation, pattern)))
;; already-installed: (name -> version)
;; conflicts: name -> setof (string, relation, pattern)
;; returns: (name -> {:version vers, :url url})
;; As coded, this does not keep track of conflicts picked up along the way.
(defun resolve [requirements
                already-installed
                conflicts
                query]
  (loop [solution-so-far {}
         requirements requirements
         already-installed already-installed
         conflicts conflicts]
    (if (empty? to-install)
      solution-so-far
      (let [requirement (first requirements)
            other-requirements (rest requirements)]
        (let [{:packages fulfillment
               :conflicts fulfillment-conflicts}
              (let [check-result (reduce-kv
               (fn [stuffs
                    package-name
                    package-constraints]
                 (if (and (contains? already-installed package-name)
                          (let [package-version (get already-installed package-name)]
                            ;; This form will return `true` if constraints are empty
                            ;; Yay!
                            (reduce
                             (fn [cum test]
                               (and cum
                                    (let [{:explain string :relation relation :pattern pattern} test]
                                      (relation
                                       package-version
                                       pattern))))
                             true package-constraints)))
                   (reduced {:packages {} :conflicts {}})
                   stuffs))
               :thatsnotit
               requirement)]
              (if (not (= check-result :thatsnotit))
                check-result
                (reduce-kv
                 (fn [stuffs
                      package-name
                      package-constraints]
                   ;; can only check conflicts with a concrete candidate
                   ;; short circuit check done here.
                   (if (and (contains? conflicts package-name)
                            (empty? (get conflicts package-name)))
                     stuffs
                     ;; and here i recursively call
                     
                            (let [(get conflicts package-name) package-constraints]
                            (reduce
                             (fn [cum test]
                               (and cum
                                    (let [{:explain string :relation relation :pattern pattern} test]
                                      (relation
                                       package-version
                                       pattern))))
                             true
                             package-constraints)))
                     stuffs
                     



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
                     

                 
                
                
               


               (reduce-kv
                (fn [stuffs
                     package-name
                     package-
                )

               
               requirement)

              

          ]
          (recur (into solutions-so-far fulfillment)
                 other-requirements
                 (into already-installed
                       (map
                        (fn [entry]
                          [(key entry)
                           (:version (val entry))])))
                 (into conflicts fulfillment-conflicts)))))))

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
