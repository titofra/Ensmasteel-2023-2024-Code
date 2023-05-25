#include "action.hpp"

Action::Action (const action_kind kind) :
    kind (kind)
{
    isFinished = false;
}

Action::Action (const action_kind kind, Kinetic trajectory (float t), float time_distortion (float t), float endTime) :
    kind (kind),
    trajectory (trajectory),
    time_distortion (time_distortion),
    endTime (endTime)
{
    isFinished = false;
}

void Action::run (float timer, float dt, Robot *robot) {
    switch (kind) {
        case MOVEMENT_ACT:
            robot->goTo (                           // goto
                trajectory (                        // the kinetic at timer + dt
                    time_distortion (timer + dt)    // but the instant timer + dt is disturbed by time_distortion ()
                ), dt                               // do it in dt
            );
            if (timer + dt >= endTime) {
                isFinished = true;   // the action is done
            }
            break;
        case OPEN_CLAWS_ACT:
            robot->openClaws ();
            isFinished = true;   // the action is almost instant, so it is done
            break;
        case CLOSE_CLAWS_ACT:
            robot->closeClaws ();
            isFinished = true;   // the action is almost instant, so it is done
            break;
        case DELAY:
            if (timer + dt >= endTime) {
                isFinished = true;   // the action is done
            }   // else we do nothing
            break;
    }
}

void Action::monitor (float timer, float dt, action_kind *actionKind, Kinetic *goal) {
    *actionKind = kind;

    switch (kind) {
        case MOVEMENT_ACT:
            *goal = trajectory (                // the kinetic at timer + dt
                time_distortion (timer + dt)    // but the instant timer + dt is disturbed by time_distortion ()
            );
            if (timer + dt >= endTime) {
                isFinished = true;   // the action is done
            }
            break;
        case OPEN_CLAWS_ACT:
            isFinished = true;   // the action is almost instant, so it is done
            break;
        case CLOSE_CLAWS_ACT:
            isFinished = true;   // the action is almost instant, so it is done
            break;
        case DELAY:
            if (timer + dt >= endTime) {
                isFinished = true;   // the action is done
            }
            break;
    }
}

bool Action::isDone () {
    return isFinished;
}


void Action::reset () {
    isFinished = false;
}