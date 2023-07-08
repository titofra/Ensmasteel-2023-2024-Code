#ifndef STEPPERMOTOR_HPP
#define STEPPERMOTOR_HPP

#include <Arduino.h>

class StepperMotor {
    public:

        /**
         * Public constructor of the StepperMotor.
         * @param stepPin : pin number of the step pin.
         * @param dirPin : pin number of the direction pin.
         * @param sleepPin : pin number of the sleep pin.
         * @param pinM0 : pin number of the first motor.
         * @param pinM1 : pin number of the second motor.
         */
        StepperMotor (int stepPin, int dirPin, int pinM0, int pinM1);

        /**
         * Method to make the motor move.
         * @param steps : number of steps that the stepper has to do.
         * @param delay : duration while the stepper should wait for the next action.
         * @param up : rotation's direction
         */
        void move(int steps, int delay, bool up);

    private:
        int stepPin;
        int dirPin;
};

#endif 