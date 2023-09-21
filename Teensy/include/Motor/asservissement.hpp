#ifndef ASSERVISSEMENT_HPP
#define ASSERVISSEMENT_HPP

class Asservissement{
    public :
        /**
         * @brief Construct a new Asservissement object
         */
        Asservissement (double kp, double ki, double kd);
        Asservissement () {};

        /**
         * @brief Computes the control signals for the robotic system based on the PID controllers and desired setpoints
         * @param dt Time elapsed since the last control signal was computed
         */
        double compute (double error, unsigned long dt);
    
    private:
        double kp;  // Proportional gain
        double ki;  // Integral gain
        double kd;  // Derivative gain

        double previousError;
        double integralError;
        double derivativeError;

};

#endif  // ASSERVISSEMENT_HPP