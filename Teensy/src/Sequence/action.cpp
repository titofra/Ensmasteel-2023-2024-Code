#include <Sequence/action.hpp>

Action::Action (action_kind kind) :
    kind (kind)
{
    isDone = false;
}

Action::Action (action_kind kind, Kinetic movement (float t), float time_distortion (float t)) :
    kind (kind),
    movement (movement),
    time_distortion (time_distortion),
    endTime (endTime)
{
    isDone = false;
}

void Action::run (float timer, float dt, Robot *robot) {
    switch (kind) {
        case MOVEMENT_ACT:
            robot->goTo (                           // goto
                movement (                          // the kinetic at t = timer + dt
                    time_distortion (timer + dt)    // but the instant timer + dt is disturbed by time_distortion ()
                ), dt                               // do it in dt
            );
            if (timer + dt >= endTime) {
                isDone = true;   // the action is done
            }
            break;
        case OPEN_CLAWS_ACT;
            robot->openClaws ();
            isDone = true;   // the action is almost instant, so it is done
            break;
        case CLOSE_CLAWS_ACT;
            robot->closeClaws ();
            isDone = true;   // the action is almost instant, so it is done
            break;
    }
}