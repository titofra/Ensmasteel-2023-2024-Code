#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <Vector>
#include <Sequence/action.hpp>

class Sequence {
    public :
        Sequence ();

        void add (Action action);
        Action pop ();
        void reset ();

        void run (float timer, float dt);
        void goTo (int istep);

    private :
        std::vector<Action> steps;
        int currentStep;
}

#endif // SEQUENCE_HPP