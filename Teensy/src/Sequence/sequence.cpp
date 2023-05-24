#include "sequence.hpp"

Sequence::Sequence () {
    currentStep = 0;
}

void Sequence::add (Action action) {
    steps.push_back (action);
}

Action Sequence::pop () {
    return steps.pop_back ()
}

void Sequence::reset () {
    steps.clear ();
    currentStep = 0;
}

void Sequence::run (float timer, float dt, Robot *robot) {
    if (currentStep < (int) steps.size ()) {
        // sequence is not finished

        steps [currentStep].run (timer, dt, robot);

        if (steps [currentStep].isDone) {
            currentStep ++;
        }
    }
}

void Sequence::monitor (float timer, float dt, action_kind *kind, Kinetic *goal) {
    if (currentStep < (int) steps.size ()) {
        // sequence is not finished

        steps [currentStep].monitor (timer, dt, kind, goal);

        if (steps [currentStep].isDone) {
            currentStep ++;
        }
    }
}

void Sequence::goToStep (int istep) {
    currentStep = istep;
}
/*
void save_monitor (const std::string& path, float beginTime, float endTime, float dt) {
    float timer = beginTime;
    Kinetic goal;
    action_kind kind;

    std::string data = "{";

    while (timer < endTime) {
        monitor (timer, dt, &kind, &goal);

        timer += dt;
    }
}*/

void Sequence::isDone () {
    return currentStep < (int) steps.size ();
}