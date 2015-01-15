#lang scheme
(define state '((A #t) (B #f) (C #t) (D #f)))
(define clause '(A (not B) (not C)))
(define clauses '((A (not B) C) (A (not B) (not C)) (A (not B) D)))
;;(define clauses '((A B C) (A (not B) (not C)) (A (not B) D)))
;;(define state '((A #f) (B #t) (C #t) (D #f)))

(define clauses1 '((F (NOT B) E) (C (NOT D) E) ((NOT G) F (NOT B)) (D C (NOT A)) (D F B)
   (D (NOT I) (NOT E)) ((NOT H) E I) ((NOT G) F I) (C F (NOT H)) (J G (NOT A))
   ((NOT H) E (NOT A)) (A (NOT F) E) ((NOT G) (NOT E) B) (E (NOT D) (NOT I))
   ((NOT G) I E) ((NOT G) (NOT B) E) (J D (NOT F)) (F (NOT H) E) (D (NOT H) E)
   ((NOT H) (NOT B) C) ((NOT E) I (NOT D)) (B (NOT F) (NOT A)) (E (NOT I) J)
   (E (NOT A) I) (D (NOT F) (NOT H)) (A H D) ((NOT D) G (NOT J)) (F D (NOT A))
   (C D F) ((NOT A) (NOT H) E)) )
(define clauses2 '((J (NOT C) D) (D (NOT G) (NOT H)) ((NOT D) (NOT E) (NOT G)) (F (NOT J) C)
   (D (NOT H) C) ((NOT G) C F) (A (NOT I) (NOT B)) ((NOT J) (NOT D) E) (H A C)
   (A C B) ((NOT B) I C) ((NOT J) (NOT G) (NOT B)) ((NOT H) A (NOT C))
   (F (NOT A) C) ((NOT H) G I) (F (NOT B) E) ((NOT C) (NOT B) I)
   ((NOT I) F (NOT D)) (B (NOT G) C) (J (NOT C) (NOT H)) (C F (NOT D))
   ((NOT J) (NOT D) (NOT C)) ((NOT J) E C) (E (NOT I) D) (C (NOT D) (NOT J))
   ((NOT G) F I) ((NOT D) B I) (B (NOT H) J) ((NOT G) (NOT D) B) ((NOT H) F I)
   (I F C) ((NOT A) D F) ((NOT D) (NOT F) (NOT J)) ((NOT J) I (NOT A))
   ((NOT E) (NOT H) I) (H (NOT B) J) (E F C) ((NOT D) E J) ((NOT A) J (NOT F))
   ((NOT D) (NOT H) (NOT F)) ((NOT B) H (NOT I)) (D (NOT H) C)
   ((NOT J) (NOT I) H) (J G F) (A G (NOT J)) (J (NOT D) (NOT H))
   ((NOT J) (NOT C) D) (I D E) ((NOT E) (NOT B) (NOT I)) (G D A)))

(define clauses3 '(((NOT I) (NOT H) (NOT F)) ((NOT B) E (NOT G)) (H (NOT C) E)
   ((NOT G) (NOT E) (NOT I)) ((NOT A) C (NOT J)) ((NOT G) (NOT A) H)
   ((NOT I) F (NOT H)) (I (NOT A) (NOT E)) ((NOT E) I J) (I (NOT J) (NOT A))
   (D I E) ((NOT B) C A) ((NOT G) E I) ((NOT G) (NOT A) F) ((NOT B) A (NOT I))
   ((NOT G) J E) (D (NOT G) C) (G (NOT B) (NOT C)) ((NOT H) F (NOT J)) (C D F)
   (B (NOT G) (NOT E)) (A (NOT D) I) (C A H) (F (NOT B) (NOT A))
   ((NOT J) (NOT F) (NOT D)) ((NOT A) E (NOT J)) ((NOT I) (NOT G) (NOT C))
   (J A C) (H (NOT G) (NOT E)) ((NOT H) (NOT I) (NOT E)) ((NOT H) D (NOT B))
   ((NOT D) E (NOT I)) (I (NOT G) C) (F (NOT G) (NOT A)) (G I E)
   (E (NOT B) (NOT G)) ((NOT C) (NOT I) D) ((NOT G) (NOT B) (NOT H))
   (D (NOT I) B) (H I A) ((NOT H) (NOT G) (NOT A)) ((NOT G) (NOT B) F)
   (E (NOT G) (NOT A)) (I (NOT H) (NOT A)) ((NOT J) E C) ((NOT B) (NOT A) F)
   (G J (NOT A)) ((NOT F) A D) (C D H) (F H E) (E J A) (J A F)
   ((NOT J) (NOT B) (NOT A)) (E A (NOT J)) ((NOT I) (NOT G) (NOT C))
   (I (NOT E) G) (I (NOT A) D) ((NOT F) E (NOT J)) ((NOT H) I D)
   (F (NOT B) (NOT H)) (E (NOT H) C) ((NOT F) (NOT D) I) (H (NOT J) (NOT D))
   (G (NOT A) (NOT F)) ((NOT E) C J) ((NOT C) E (NOT F)) (D (NOT E) (NOT F))
   ((NOT H) (NOT A) F) (F E (NOT G)) (D F (NOT J)) ((NOT A) (NOT J) (NOT I))
   (J (NOT F) (NOT H)) ((NOT I) (NOT H) J) (C G (NOT E)) (I C F) (I (NOT F) J)
   (A (NOT H) (NOT E)) (C (NOT A) (NOT H)) (D (NOT F) (NOT A))
   ((NOT E) (NOT G) I)))

(define state1 '((A #t) (B #f) (C #t) (D #f) (E #t) (F #f) (G #t) (H #f) (I #t) (J #f)))
#|
eval-var searches for a given variable within a list that can be pre-defined or
passed to it. If the variable is found within the list the truth value associated
with it is returned. If it is not found within the list (void) is returned.

Assumption is that each variable is stored as a pair along with the associated
truth value in state.
|#
(define eval-var(lambda(var state)
                  (if(empty? state)
                     (void)
                     (if(equal? var(caar state))
                        (cadar state)
                        (eval-var var(cdr state))))))

#|
eval-clause uses logical AND to evaluate a clause and return the truth value.
While this assignment assumes three elements within a clause eval-clause is
able to evaluate clauses of arbitray length because it uses a recursive method.

Assumption is that a clause is a list of variables that have truth values 
associated with them in the manner defined by eval-var, passed to eval-clause
in state.
|#
(define eval-clause(lambda(clause state)
                     (if(empty? clause)
                        (void)
                        (if(eqv? (car(flatten clause)) 'not)
                           (and(not(eval-var(cadar clause) state)) (eval-clause (cdr clause) state))
                           (and(eval-var(car clause) state) (eval-clause (cdr clause) state))))))

#|
get-vars returns the variables contained within a clause. Duplicates are
not removed. Flatten is not used here since we need only create a list.
Recursion is again used.

Assumption is that a clause is defined in the manner specified by
eval-clause. 
|#
(define get-vars(lambda(clause)
                  (if(empty? clause)
                     null
                     (if(pair? (car clause))
                        (cons (cadar clause) (get-vars(cdr clause)))
                        (cons (car clause) (get-vars(cdr clause)))))))

#|
get-all-vars leverages get-vars to create lists of variables contained
within a list of clauses. Remove-duplicates and flatten are used to 
simplify the process.

Assumption is that clauses are defined in the manner specified by
eval-clause.
|#
(define get-all-vars(lambda(clauses)
                      (if(empty? clauses)
                         null
                         (remove-duplicates(flatten(cons (get-vars (car clauses)) (get-all-vars(cdr clauses))))))))

#|
unsat-clauses returns a list containing any clause in a list of
clauses that evaluates to #f. eval-clause is leveraged and a
recursive call to unsat-clauses passes an ever shorter list to 
evaluate.

Assumption is that a clause is defined in the manner specified 
by eval-clause
|#
(define unsat-clauses(lambda(clauses state)
                       (if(empty? clauses)
                          null
                          (if(empty? state)
                             null
                             (if(eval-clause(car clauses) state)
                                (unsat-clauses(cdr clauses) state)
                                (cons (car clauses) (unsat-clauses (cdr clauses) state)))))))

#|
flip-var inverts the truth value of a variable in a list specified
by state. A list is returned of the new truth values associated with
each variable contained in state. Recursive calls to flip-var are used
to build the list

Assumption is that state is defined in the manner specified by eval-var
|#
(define flip-var (lambda (var state)
                   (if (empty? state)
                      null
                      (if (equal? var (car(car state)))
                          (cons (list var (not(eval-var var state))) (flip-var var (cdr state)))
                          (cons (car state) (flip-var var (cdr state)))))))

#|
get-better-neighbor attempts to find a variation of state where the
truth value of one variable contained in state is inverted that then
yields fewer unsatisfied clauses. Lists containing clauses and states
are passed along with a list of variables to check and the number
of unsatisfied clauses we begin with. If we traverse the list of
variables and do not find a better neighbor #f is returned, indicating
we already have the best possible neighbor. If a better neighbor is
found a list containing the state that yielded the better neighbor
is returned.

Assumption is that clauses are defined in the manner specified by 
eval-clause, state is defined in the manner specified by eval-var,
vars contains a list of variables that have truth values associated
with them inside state, num-unsat is obtained by calling
(unsat-clauses clauses state) using the same list of clauses and
state that are being passed to get-better-neighbor.
|#
(define get-better-neighbor(lambda(clauses state vars num-unsat)
                             (if(empty? clauses)
                                null
                                (if(empty? state)
                                   null
                                   (if(empty? vars)
                                   #f
                                   (if(= num-unsat 0)
                                      state
                                      (if(< (length(unsat-clauses clauses (flip-var (car vars) state))) num-unsat)
                                         (flip-var(car vars) state)
                                         (get-better-neighbor clauses state(cdr vars) num-unsat))))))))

#|
simple-hill-climb attempts to use the other functions to find
some assignment of true and false to the variables contained
within a boolean expression so that the entire boolean expression
evaluates to 'true'. 

If either clauses or state are empty then
null is returned because the function was not called correctly.

If dist = 0 then we have run out of attempts to find a solution
and should return the best result found. 

If unsat is empty there are no more unsatisfied clauses and we
have found a solution that is returned.

If the first call to get-better-neighbor evaluates to #f we have
no neighbors that can be found and the best result is returned.

Otherwise successive calls to simple-hill-climb are performed
until we reach the number of attempts specified.

Assumption is that clauses and state are defined according to the 
manner specified by eval-clause and eval-var respectively, dist
is an int, unsat is obtained by calling (unsat-clauses clauses state)
|#
(define simple-hill-climb(lambda(clauses state dist unsat)
                           (if(empty? clauses)
                              null
                              (if(empty? state)
                                 null
                                 (if(= dist 0)
                                    state
                                    (if(empty? unsat)
                                       state
                                       (if(equal? (get-better-neighbor clauses state (get-all-vars (unsat-clauses clauses state)) (length(unsat-clauses clauses state))) #f)
                                          state
                                          (simple-hill-climb clauses (get-better-neighbor clauses state (get-all-vars (unsat-clauses clauses state)) (length unsat)) (- dist 1) (unsat-clauses clauses (get-better-neighbor clauses state (get-all-vars (unsat-clauses clauses state)) (length unsat)))))))))))

