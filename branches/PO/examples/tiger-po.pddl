; This is a modified version of the "tiger.pddl" file provided with
; MDPSim. It is changed in two ways:
; - it is now partially observable (as any tiger problem should be) and
; - it has been turned into a stochastic shortest-path problem.

(define (domain tiger-po-domain)
  (:requirements :negative-preconditions :conditional-effects
		 :probabilistic-effects :partial-observability)
  (:predicates (:no tiger-on-left) (hear-tiger-on-left) (hear-tiger-on-right) (door-opened) (success))
  (:action listen
	   :precondition (not (door-opened))
	   :effect (and (probabilistic 0.05 (door-opened))
			(when (tiger-on-left)
			  (probabilistic 0.85 (and (hear-tiger-on-left)
						   (not (hear-tiger-on-right)))
					 0.15 (and (not (hear-tiger-on-left))
						   (hear-tiger-on-right))))
			(when (not (tiger-on-left))
			  (probabilistic 0.85 (and (not (hear-tiger-on-left))
						   (hear-tiger-on-right))
					 0.15 (and (hear-tiger-on-left)
						   (not (hear-tiger-on-right)))))))
  (:action open-left-door
	   :precondition (not (door-opened))
	   :effect (and (door-opened)
			(when (not (tiger-on-left))
			  (success))))
  (:action open-right-door
	   :precondition (not (door-opened))
	   :effect (and (door-opened)
			(when (tiger-on-left)
			  (success))))
  )
  
(define (problem tiger-po-problem)
  (:domain tiger-po-domain)
  (:init (probabilistic 0.5 (tiger-on-left)))
  (:goal success)
  )
