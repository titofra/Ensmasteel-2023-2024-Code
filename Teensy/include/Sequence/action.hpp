#ifndef ACTION_HPP
#define ACTION_HPP

#include "robot.hpp"
#include "kinetic.hpp"
#include <functional>

enum action_kind {
    MOVEMENT_ACT,
    OPEN_CLAWS_ACT,
    CLOSE_CLAWS_ACT,
    DELAY
};

using trajectory_fn = std::function<Kinetic (unsigned long)>;
using time_distortion_fn = std::function<unsigned long (unsigned long)>;

class Action {
    public :
        Action (action_kind kind, trajectory_fn trajectory, time_distortion_fn time_distortion, unsigned long endTime);
        Action (action_kind kind, unsigned long endTime);

        void run (unsigned long timer, unsigned long dt, Robot *robot);

        // fake run to monitor the action
        void monitor (unsigned long, unsigned long dt, action_kind *actionKind, Kinetic *goal);

        bool isDone ();

        void reset ();

    private :
        action_kind kind;
        bool isFinished;

        /* for movements only */
        trajectory_fn trajectory;         // time-function that returns the Kinetic over linear time
        time_distortion_fn time_distortion; // time-function that returns the local time refering to the global ones. This enable us to modify over the time the robot's accemeration/velocity
        unsigned long endTime;

};

#endif  // ACTION_HPP