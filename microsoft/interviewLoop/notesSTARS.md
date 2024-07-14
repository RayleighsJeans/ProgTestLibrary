CODING =======================================================================
  >> U -- Understand the problem
  >> M -- Match the problem with the interviewer
  >> P -- Plan your approach and solution
  >> I -- Implement your solution
  >> R -- Review your solution
  >> E -- Evaluate your solution

STARS ========================================================================
  >> Situation: describe situation you were in or task you needed to accomplish
     describe specific event or situation, not generalized description of what you have done
     give enough detail for interviewer to understand
  >> Task: What goal were you working toward?
  >> Action: describe actions you took to address the situation 
     keep the focus on YOU; specify steps you took, what was your particular
     contribution? use the word “I,” not “we” when describing actions
  >> Result: describe outcome of your actions
     What happened? How did the event end? What did you accomplish?
     What did you learn? Make sure your answer contains multiple positive results.

EXAMPLES =====================================================================

  >> Describe a situation in which you were able to use persuasion to successfully convince someone to see things your way.
     -[S]- implementation of real time feedback system for bolometer required updated and changed design of diagnostic program (better understanding)
     -[T]- add and extend the software suite running the calibration, data acquisition, storage etc. to accommodate both RT capability and sampling speed
     -[A]-
       dug through documentation of original equipment, contacted engineer who 'constructed' the first software revision and made myself familiar with respective schematics/layouts of the chip
       understood challenging mess of said program, tidied up and verified each own revision with lab tests to ensure validness along the way; added above requirements to best of possibilities, encountered additional unforeseen limitations due to underlying system/proprietary software
       verified with more lab test and clearly marked out boundaries and communicated accordingly to superiors - contrast to what they believed must have worked before, though nobody actually checked or could show me
    -[R]- system was deployed as reliably as possible within the realm of feasibility documented, results could be reproduced and communicated to others afterwards

  >> Describe a time when you were faced with a stressful situation that demonstrated your coping skills.
     -[S-T]-
       see above
       software and setup had to be ready in time for upcoming experimental campaign with strict layout and time slots available to that particular set of tests
       diagnostic was also used beyond that during that campaign outside that particular use case for general measurements, lasting whole days, weeks at a time, rare chances to get at it or use or test it outside of that 
     -[A]- design, programming, construction, documentation and lab verification were done, mostly in-parallel to overall scientific evaluation that was necessary to support said investigations
     -[R]- made it just in time, resulting in the some of the first experiments of that kind at W7-X, especially for that metric
    
  >> Give me a specific example of a time when you used good judgment and logic in solving a problem.
     -[S]- navigation takes a large portion of the available/used computation cycles in our simulation and breaks down/driver fails to proceed as needed in very close ranges due to the nature of MBTs size/maneuverability, i.e. in cities, small towns or in dense traffic  
     -[T]-
       new fast close range navigation prediction method and lightweight AI driver needed for the CGFs in the large scale battlefield training simulation
     -[A]-
        used reduced scientific models for wheeled vehicles (ODEs etc), adapted them to the task and verified against the existing full model in the simulation (complex custom, secret tank models by engineers/scientists taken from the actual thing) and produced a routine that takes a physical state and steering/throttle input to reliably predict the next ~2s of slow-ish driving
        got rid of the old, convoluted (spaghetti) and badly documented driver routine, wrote a new plug-and-play driver suite for all vehicle types that can be unit tested without physics system running - prev. not possible - and easily exchanged with different concepts for e.g. AI systems, partial human control etc.
        set up a PID suite for various level of intricacy for maximum flexibility, from basic/bare bones to self-adjusting that can be used with almost all core/STL types
     -[R]- well documented scientifically based prediction model and new drivers suite that is simple, performant, easy to understand and work with and future proof 
     
  >> Give me an example of a time when you set a goal and were able to meet or achieve it.
     -[S]- old and undocumented tomography suite for LOS tracing in a specific volume for bolometer detectors in deprecated IDL programming language without proper visualization and extendability
     -[T]- write own suite that exceeds the olds performance, gives better feedback, works for any volumetric setup and camera setup in an adequate language that can be used with any post-processor for tomography
     -[A]-
       from the ground up, constructed new routines that produce LOS from detector data, volumetric voxel grids from magnetic field configurations or any 2D slices in 3D space, traces the LOS in 3D and corrects results with respect to position/distance from aperture for a 2D representation
       verified against old results for edge cases, perturbation study etc
       synthetic image tests and tuning for various sampling methods (square, triangulation)
     -[R]- reasonably fast O(N * log(klm)) algorithm in python yielding improved accuracy for 3D LOS tracing
    
  >> Tell me about a time when you had to use your presentation skills to influence someone's opinion.
     -[S]- monthly meetings with my doctoral supervisors to discuss recent personal results and findings in the process
     -[T]- each meeting, formulate the key points and pitch enclosing investigations worth doing with potential hypothesis and approach for feasibility
     -[A]- find trends in the newest data, highlight promising characteristics and produce visualization and short and concise statements justifying the further evaluation in this particular direction
     -[R]- develop and take responsibility/capability of directing ones own work flow with support of superiors

  >> Give me a specific example of a time when you had to conform to a policy with which you did not agree.
     -[S]- short staffed for/not enough time available or alloted for the development of proper solutions for found inadequacies/bugs in the AI/physics of the training simulation
     -[T]- implementation of new features tied to deadlines or specific customer projects were put in front of necessary re-implementation of ill-formed subroutines
     -[A]- complying with the companies scheduling to meet requirements
     -[R]- TODOs piling up or only quick/simplified fixes implemented

  >> Please discuss an important written document you were required to complete.
     -[S]-
       PhD thesis not completed before end of contract at IPP and before new position at KMW
       end of contract at IPP and new software to be passed on to other scientists
       simple 1D model for near field navigation prediction
     -[T]-
       finish thesis in parallel to new full time software developer position at KMW
       write notebooks/documentation and how-tos for own algorithms and in directions to use them effectively and properly
       round up information and formulate limitations of the produced model
     -[A]-
       see above
     -[R]-
       completed thesis in early 2024 after finishing scientific endeavour end of 2021
       individual markdown documents/notebooks for tomography, phantom image benchmarking, raw data evaluation, API interactions etc
       stand-alone program for model prediction results given an input as described above with respective document highlighting the physics behind and the equations

  >> Tell me about a time when you had to go above and beyond the call of duty in order to get a job done.
     -[S]- evaluation of LOS perturbations towards tomography and their influence necessary for thesis results
     -[T]- adjustments/extensions to the LOS tracing algorithm and surrogate data generation to do phantom benchmarks with
     -[A]- re-wrote 3D stereoscopic LOS tracing algorithm for the above requirements entirely in a short amount of time with improved performance to edge out accuracy tests
     -[R]- new updated and future proof algo, easily extendable


  >> Tell me about a time when you had too many things to do and you were required to prioritize your tasks.
     -[S]- implementation of real time feedback system for bolometer required updated and changed design of diagnostic program (better understanding)
     -[T]- improve overall system to handle longer acquisition task at greater sampling frequency while also doing multiple RT tasks with no additional latency
     -[A]- not enough time to change to RT system or work around proprietary limits of the software, do as much as possible and limit program to within its capabilities
     -[R]- certain improvements made within the given time frame and possibilities of the scientific program

  >> Give me an example of a time when you had to make a split second decision.
     -[S]- experimental program might change within seconds given the results of the previous
     -[T]- setup of the diagnostic has to be changed to accommodate the experiment as best as possible to best of its own capabilities
     -[A]- rewritten the routine to do so as required and change it in accordance live during the session
     -[R]- proper acquisition timelines over the course of the campaign with minimal manual input

  >> What is your typical way of dealing with conflict? Give me an example.
  >> Tell me about a time you were able to successfully deal with another person even when that individual may not have personally liked you (or vice versa). 
     -[S]- fellow and superior scientists (software engineers) always challenge ones explanations and interpretations or approaches
     -[T]- near field navigation model to be promoted as new approach to superiors, one particular reluctant or unable to understand the method and goal (language barrier)
     -[A]- don't lose confidence and remember what one knows and that decisions have been deliberated on together with others, don't lose your cool and stay polite, calm and confidently defend your point - if not brought out invalid
     -[R]- professional course and result maintained

  >> Tell me about a difficult decision you've made in the last year.
     -[S]- new part of life after marriage, Munich is not a place forever
     -[T]- find a 'forever' home and place to settle down with perspective
     -[A]- move to Ireland (like where I grew up)
     -[R]- making the change and stay confident throughout

  >> Give me an example of a time when something you tried to accomplish and failed.
     -[S]- master thesis: PIC code has one single-threaded pinhole where a large LU matrix decomposition happens
     -[T]-
       extract model from motivating paper and apply to known systems
       implement a electrostatic PIC model algorithm for cold reactive plasma physics simulation that is multi-threadable 
     -[A]- implement and verify particle tracking, bookkeeping and equation calculation, then test with minimum example
     -[R]- didn't work due to omitted aspect in the original derivation (not magnetostatic)

  >> Give me an example of when you showed initiative and took the lead.
     -[S]- regression test for AI and combat behavior failing many cases for a long time due to under staffing
     -[T]- evaluate tests and find what goes wrong, fix whatever bugs are underlying or what behavior trees have gone deprecated and fixing them
     -[A]- one by one and individually look at the ARS, collect issues and fix them
     -[R]- updating the behavior engine and test cases to suite the current state of the AI

  >> Give me an example of a time when you motivated others.
     -[S]- testing of simulation training facility with full setup and as many vehicles as possible for performance evaluation necessary
     -[T]- gather many people to man the stations
     -[A]- signed up as loader (heavy lifting, literally) so actual setup can be verified
     -[R]- 2-6h of fun for everybody and happy superiors seeing the product in action, otherwise very rare
    
  >> Give me an example of a time when you used your fact-finding skills to solve a problem.
     -[S]- implementation of real time feedback system for bolometer required updated and changed design of diagnostic program (better understanding)
     -[T]- verify performance and limits of system
     -[A]- edge out system and proprietary program limitations and correspond with respective developers, in contrast to what they claimed
     -[R]- cemented the parameters in which the acquisition can be used safely and reliably

  >> Tell me about a time when you missed an obvious solution to a problem.
     -[S]- multifaceted PID suite for AI control tasks
     -[T]- implement such a suite with as many possibilities as hidden as possible from the the using developer
     -[A]- factory pattern applied, too overkill and convoluted
     -[R]- simple templated inheritance with obscured headers/instantiation sufficient and easy
  
  >> When working within a team, what role do you typically take on? Please provide an example. 
     -[S]- CGF and AI development team joined at KMW
     -[T]- improve computer forces reliability and features
     -[A]- extended AI capabilities and fixing bugs, aiding stability but also do embedded work around the simulator hardware and particularly physics
     -[R]- best at working oneself into topics, gaining crucial knowledge and deliberating solutions to complex problems, abstracting underlying issues and formulating possible approaches and optimizing models; particularly with mathematical/physical background 
  
  >> Describe a time when you set your sights too high.
     -[S]- contractual limit for PhD was 3.5 years
     -[T]- finish scientific tasks and write thesis within this time +/- 0.5 years
     -[A]- scope of thesis and data collected/evaluation done to much and while working full time not advisable 
     -[R]- took +3 years to write thesis to entirety


  >> Describe a time when you anticipated potential problems and developed preventive measures. 
     -[S]-
     -[T]-
     -[A]-
     -[R]-

  >> Tell me about a time when you were forced to make an unpopular decision.
     -[S]-
     -[T]-
     -[A]-
     -[R]-

  >> Tell me about a time that you made a mistake and how did you handle it.
     -[S]- 
     -[T]-
     -[A]-
     -[R]-

  >> Give an example of how you’ve worked well on a team.
     -[S]- 
     -[T]-
     -[A]-
     -[R]-

  >> Tell us about a time when you made a bad decision. What did you learn from the situation?
     -[S]-
     -[T]-
     -[A]-
     -[R]-

  >> What strategies have you used to get individuals to work well together to achieve a common goal? 
     -[S]-
     -[T]-
     -[A]-
     -[R]-

  >> Tell us about a time when you witnessed a friend or colleague do something wrong. How did you respond? 
     -[S]-
     -[T]-
     -[A]-
     -[R]-
