#ifndef ACTION_HPP
#define ACTION_HPP

#include "robot.hpp"
#include "kinetic.hpp"

enum action_kind {
    MOVEMENT_ACT,
    OPEN_CLAWS_ACT,
    CLOSE_CLAWS_ACT,
    DELAY
};

class Action {
    public :
        Action (const action_kind kind);
        Action (const action_kind kind, Kinetic (*trajectory) (float t), float (*time_distortion) (float t), float endTime);

        void run (float timer, float dt, Robot *robot);

        // fake run to monitor the action
        void monitor (float timer, float dt, action_kind *actionKind, Kinetic *goal);

        bool isDone ();

        void reset ();

    private :
        const action_kind kind;
        bool isFinished;

        /* for movements only */
        Kinetic (*trajectory) (float t);         // time-function that returns the Kinetic over linear time
        float (*time_distortion) (float t); // time-function that returns the local time refering to the global ones. This enable us to modify over the time the robot's accemeration/velocity
        float endTime;

};

#endif  // ACTION_HPP