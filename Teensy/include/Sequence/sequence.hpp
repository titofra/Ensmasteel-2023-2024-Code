#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <Vector>
#include "action.hpp"

class Sequence {
    public :
        Sequence ();

        void add (Action action);
        Action pop ();
        void reset ();

        void run (float timer, float dt, Robot *robot);
        void goTo (int istep);

        bool isDone ();

    private :
        std::vector<Action> steps;
        int currentStep;
}

#endif // SEQUENCE_HPP