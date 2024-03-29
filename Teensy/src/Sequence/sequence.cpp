#include "sequence.hpp"

Sequence::Sequence () {
    currentStep = 0;
}

void Sequence::add (Action action) {
    steps.push_back (action);
}

void Sequence::pop () {
    steps.pop_back ();
}

void Sequence::reset () {
    steps.clear ();
    currentStep = 0;
}

void Sequence::run (unsigned long timer, unsigned long dt, Robot *robot) {
    if (currentStep < (int) steps.size ()) {
        // sequence is not finished

        steps [currentStep].run (timer, dt, robot);

        if (steps [currentStep].isDone ()) {
            currentStep ++;
        }
    }
}

void Sequence::monitor (unsigned long timer, unsigned long dt, action_kind *kind, Kinetic *goal) {
    if (currentStep < (int) steps.size ()) {
        // sequence is not finished

        steps [currentStep].monitor (timer, dt, kind, goal);

        if (steps [currentStep].isDone ()) {
            currentStep ++;
        }
    }
}

void Sequence::goToStep (int istep) {
    currentStep = istep;
}

bool Sequence::isDone () {
    return currentStep < (int) steps.size ();
}