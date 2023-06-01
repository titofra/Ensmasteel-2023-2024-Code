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

typedef std::function<Kinetic (unsigned long, Kinetic, Kinetic)> trajectory_fn;
typedef std::function<unsigned long (unsigned long)> time_distortion_fn;

class Action {
    public :
        Action (action_kind kind, unsigned long endTime);
        Action (action_kind kind, trajectory_fn trajectory, time_distortion_fn time_distortion, Kinetic beginKinetic, Kinetic endKinetic, unsigned long endTime);

        void run (unsigned long timer, unsigned long dt, Robot *robot);

        // fake run to monitor the action
        void monitor (unsigned long timer, unsigned long dt, action_kind *actionKind, Kinetic *goal);

        bool isDone ();

        void reset ();

    private :
        action_kind kind;
        bool isFinished;
        unsigned long endTime;

        /* for movements only */
        trajectory_fn trajectory;         // time-function that returns the Kinetic over linear time
        time_distortion_fn time_distortion; // time-function that returns the local time refering to the global ones. This enable us to modify over the time the robot's accemeration/velocity
        Kinetic beginKinetic, endKinetic;

};

#endif  // ACTION_HPP