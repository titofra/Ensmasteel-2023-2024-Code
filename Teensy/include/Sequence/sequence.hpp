#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <vector>
#include "action.hpp"

class Sequence {
    public :
        Sequence ();

        void add (Action action);
        void pop ();
        void reset ();

        void run (unsigned long timer, unsigned long dt, Robot *robot);
        void monitor (unsigned long timer, unsigned long dt, action_kind *kind, Kinetic *goal);
        void goToStep (int istep);

        // save the monitoring ie goals at each dt, actions, etc
        //void save_monitor (const std::string& path, float beginTime, float endTime, float dt);

        // save the sequence
        void save ();

        bool isDone ();

    private :
        std::vector<Action> steps;
        int currentStep;
};

#endif // SEQUENCE_HPP