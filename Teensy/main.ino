#include "setup.hpp"

const unsigned long dt = 10;
unsigned long timer, timer_init;

Sequence seq;

void BuildSequence (Sequence *seq);

void setup () {
    // Communications
    Serial.begin (115200);
    Serial1.begin (115200);
    Serial2.begin (115200);

    // SENSORS
    pinMode (PIN_ARRET_URGENCE, INPUT_PULLDOWN);
    //pinMode (PIN_TIRETTE, INPUT_PULLDOWN);

    // Actuators

    // Logger

    // Threads
    threads.setMicroTimer(10);
    threads.setDefaultTimeSlice (1);
    threads.addThread (threadUrgence);

    delay (1000);   // to ensure all the threads are loaded

    // Wait until the beggining of the match
    //Wait_While_Tirette ();

    // Sequence
    BuildSequence (&seq);

    timer_init = millis ();
}

void loop () {
    timer = millis () - timer_init;

    seq.run (timer, dt, &robot);
    robot.updateMovement (dt);

    Wait_Until_Timer (timer_init, timer, dt); 
}

void BuildSequence (Sequence* seq) {
    // kinetics
    VectorOriented P1 (2000.0f, 1000.0f, 3.14f / 2.0f);
    VectorOriented P2 (1650.0f, 1350.0f, 3.14f);
    VectorOriented P3 (1300.0f, 1000.0f, -3.14f / 2.0f);
    VectorOriented P4 (1650.0f, 650.0f, 0.0f);

    const float delta_curve = 200.0f;

    // actions
    Action mvmt12 (
        MOVEMENT_ACT,
        bezier_auto ({P1, P2}, delta_curve),
        trapeze (0, 500, 1500, 1500, 0.7f, 0.7f),
        1500
    );
    Action mvmt23 (
        MOVEMENT_ACT,
        bezier_auto ({P2, P3}, delta_curve),
        trapeze (1500, 1500, 2500, 2500, 0.5f, 0.8f),
        2500
    );
    Action mvmt34 (
        MOVEMENT_ACT,
        bezier_auto ({P3, P4}, delta_curve),
        trapeze (2500, 2500, 3500, 3500, 0.5f, 0.8f),
        3500
    );
    Action mvmt41 (
        MOVEMENT_ACT,
        bezier_auto ({P4, P1}, delta_curve),
        trapeze (3500, 3500, 4500, 5000, 0.5f, 0.8f),
        5000
    );

    // sequence
    seq->add (mvmt12);
    seq->add (mvmt23);
    seq->add (mvmt34);
    seq->add (mvmt41);
}
