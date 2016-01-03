;; TODO: Remove c++ stuff, fix license, set up & commit proper lein project.


;; requirements ->_     _<- possibilities
;; to-install: (setof (name -> setof (string, relation, pattern)))
;; already-installed: (name -> version)
;; conflicts: name -> (string, relation, pattern)
;; returns: list of URLs, and package conflicts listof URL, (name -> (relation, version))
(defun resolve [requirements
                already-installed
                conflicts
                query]
  (reduce (fn [package-urls-so-far
               possibilities]
            (reduce (fn [best-solution-so-far
                         possibility]
                      (let [name (key possibility)
                            constraints (val possibility)]
                        (if (contains? already-installed name)
                          (if (reduce
                               (fn [satisfies-so-far test]
                                 (and
                                  satisfies-so-far
                                  (let [[string relation pattern] test]
                                    (relation
                                     (get already-installed name)
                                     pattern))))
                               true
                               constraints)
                            package-urls-so-far
                            (reduced :unsatisfiable))
                          (into package-urls-so-far
                                ; listof [version , url, (name -> (string,relation,pattern) ,(setof (name -> setof (string, relation, pattern))))])
                                  ; This reduce feels wrong, maybe it is?
                                  (reduce
                                   (fn [cum next]
                                     (let [[candidate-version
                                            candidate-url
                                            candidate-conflicts
                                            candidate-depends] next]
                                       ;; match to see if candidate is in conflict first, if not,
                                       ;; then go get it.
                                       (if (and (contains? conflicts name)
                                                (reduce
                                                 (fn [satisfiability thing]
                                                   
                                         
                                       (if (reduce
                                            (fn [cum next]
                                              (and
                                               (
                                           (resolve candidate-depends
                                                    (assoc already-installed
                                                           name
                                                           candidate-version)
                                                    (into conflicts candidate-conflicts)
                                                    query) candidate-result]
                                       (if 
                                       (if (= :unsatisfiable candidate-result)
                                         cum
                                         (reduced (conj candidate-result candidate-url)))))
                                   :unsatisfiable
                                   (query name)))
                                       
                                              [:unsatisfiable] cum
                                              :else
                                       (if (= candidate-result :unsatisfiable)
                                           
                                                
                             b

                            (dissoc possiblities (key possiblity))
            (conj cum
                  (reduce
                   (fn [cum possibility]
                     (map (fn [
                     (if (contains? already-installed 
                     (into conflicts (disj requirement possibility))
                     
                     (disj requirement possibility)
                     
                     
                  (let [
                        ]
                  
            ) [] to-install))

  (let [requirement (first to-install)
        still-to-install (disj to-install requirement)]
    (loop [terms requirement]
      (let [term (first terms)
            blackout-terms (disj terms term)]
        (reduce (fn [cum next]
                  (key next)
                  term)
        (if (contains? already-installed 
        
        
      )
        
    (let [
  (reduce

   
  (mapcat (fn [terms]
            (let [
                  options
                  

                  


                  
                  ]
              (reduce (fn [a b] (if (< (size a) (size b))
                                  a
                                  b))
                    options))

            ) to-install))
