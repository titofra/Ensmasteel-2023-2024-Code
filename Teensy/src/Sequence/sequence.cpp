#include <Sequence/sequencer.hpp>

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

void Sequence::goTo (int istep) {
    currentStep = istep;
}

void Sequence::isDone () {
    return currentStep < (int) steps.size ();
}