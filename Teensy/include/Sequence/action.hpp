#ifndef ACTION_HPP
#define ACTION_HPP

#include <robot.hpp>
#include <Vectors/kinetic.hpp>

typedef struct {
    MOVEMENT_ACT,
    OPEN_CLAWS_ACT,
    CLOSE_CLAWS_ACT
} action_kind;

class Action {
    public :
        Action (action_kind kind);
        Action (action_kind kind, Kinetic movement (float t), float time_distortion (float t), float endTime);

        void run (float timer, float dt, Robot *robot);

    private :
        action_kind kind;
        bool isDone;

        /* for movements only */
        Kinetic movement (float t);         // time-function that returns the Kinetic over linear time
        float time_distortion (float t); // time-function that returns the local time refering to the global ones. This enable us to modify over the time the robot's accemeration/velocity
        float endTime;

}

#endif  // ACTION_HPP