#include "action.hpp"

Action::Action (action_kind kind, trajectory_fn trajectory, time_distortion_fn time_distortion, unsigned long endTime) :
    kind (kind),
    endTime (endTime),
    trajectory (trajectory),
    time_distortion (time_distortion)
{
    isFinished = false;
}

Action::Action (action_kind kind, unsigned long endTime) :
    kind (kind),
    endTime (endTime)
{
    isFinished = false;
}

void Action::run (unsigned long timer, unsigned long dt, Robot *robot) {
    switch (kind) {
        case MOVEMENT_ACT:
            robot->goTo (                           // goto
                trajectory (                        // the kinetic at timer + dt
                    time_distortion (               // but the instant timer + dt is disturbed by time_distortion ()
                        timer + dt
                    )
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
        case DELAY_ACT:
            if (timer + dt >= endTime) {
                isFinished = true;   // the action is done
            }   // else we do nothing
            break;
    }
}

void Action::monitor (unsigned long timer, unsigned long dt, action_kind *actionKind, Kinetic *goal) {
    *actionKind = kind;

    switch (kind) {
        case MOVEMENT_ACT:
            *goal = trajectory (                // the kinetic at timer + dt
                time_distortion (               // but the instant timer + dt is disturbed by time_distortion ()
                    timer + dt
                )
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
        case DELAY_ACT:
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