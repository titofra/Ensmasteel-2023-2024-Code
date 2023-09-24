#ifndef ACTION_HPP
#define ACTION_HPP

#include "robot.hpp"
#include "kinetic.hpp"
#include <functional>

enum action_kind {
    MOVEMENT_ACT,
    OPEN_CLAWS_ACT,
    CLOSE_CLAWS_ACT,
    DELAY_ACT
};

typedef std::function<Kinetic (double)> trajectory_fn;
typedef std::function<double (unsigned long)> time_distortion_fn;

/**
 * @brief Class that represent any action
 */
class Action {
    public :
        /**
        * @brief Construct a new Action object
        * 
        * @param kind The kind of the action
        * @param endTime The time where the action is finished
        */
        Action (action_kind kind, unsigned long endTime);

        /**
         * @brief Construct a new Action object
         * 
         * @param kind The kind of the action
         * @param trajectory The trajectory function
         * @param time_distortion The time distortion function
         * @param endTime The time where the action is finished
         */
        Action (action_kind kind, trajectory_fn trajectory, time_distortion_fn time_distortion, unsigned long endTime);

        /**
         * @brief Run the action
         * 
         * @param timer The current time
         * @param dt The time to run the action
         * @param robot Pointer to the robot where the action should be run
         */
        void run (unsigned long timer, unsigned long dt, Robot *robot);

        /**
         * @brief Monitor the action. It is like a fake `run`. This function has no effect on the robot but it can act on the action itself
         * 
         * @param timer The current time
         * @param dt The time to run the action
         * @param actionKind Pointer to an action kind variable. Used to retrieve the kind of the action
         * @param goal Pointer to a kinetic variable. Used to retrieve the goal kinetic of the robot
         */
        void monitor (unsigned long timer, unsigned long dt, action_kind *actionKind, Kinetic *goal);

        /**
         * @brief Check if the action is finished
         * 
         * @return true if the action is finished, else false
         */
        bool isDone ();

        /**
         * @brief Set the action to a not finished one
         */
        void reset ();

    private :
        action_kind kind;
        bool isFinished;
        unsigned long endTime;

        /* for movements only */
        trajectory_fn trajectory;         // time-function that returns the Kinetic over linear time
        time_distortion_fn time_distortion; // time-function that returns the local time refering to the global ones. This enable us to modify over the time the robot's accemeration/velocity

};

#endif  // ACTION_HPP