#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <vector>
#include "action.hpp"

/**
 * @brief Class that represents a sequence of actions
 */
class Sequence {
    public :
        /**
         * @brief Construct a new Sequence object
         */
        Sequence ();

        /**
         * @brief Push back an action to the sequence
         * 
         * @param action The action to be pushed back
         */
        void add (Action action);

        /**
         * @brief Pop back an action of the sequence
         */
        void pop ();

        /**
         * @brief Reset the sequence
         * 
         */
        void reset ();

        /**
         * @brief Run the sequence
         * 
         * @param timer The current time
         * @param dt The time to run the action
         * @param robot Pointer to the robot where the action should be run
         */
        void run (unsigned long timer, unsigned long dt, Robot *robot);

        /**
         * @brief Monitor the sequence. It is like a fake `run`. This function has no effect on the robot but it can act on the actions themselves
         * 
         * @param timer The current time
         * @param dt The step time to run the actions
         * @param actionKind Pointer to an action kind variable. Used to retrieve the kind of the current action
         * @param goal Pointer to a kinetic variable. Used to retrieve the goal kinetic of the robot
         */
        void monitor (unsigned long timer, unsigned long dt, action_kind *kind, Kinetic *goal);

        /**
         * @brief Change the step of the sequence
         * 
         * @param istep The new step
         */
        void goToStep (int istep);

        /**
         * @brief Check if the sequence is finished
         * 
         * @return true if the sequence is finished, else false
         */
        bool isDone ();

    private :
        std::vector<Action> steps;
        int currentStep;
};

#endif // SEQUENCE_HPP