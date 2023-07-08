#ifndef ASSERVISSEMENT_HPP
#define ASSERVISSEMENT_HPP

class Asservissement{
    public :
        /**
         * @brief Construct a new Asservissement object
         */
        Asservissement (float kp, float ki, float kd);
        Asservissement () {};

        /**
         * @brief Computes the control signals for the robotic system based on the PID controllers and desired setpoints
         * @param dt Time elapsed since the last control signal was computed
         */
        float compute (float error, unsigned long dt);
    
    private:
        float kp;  // Proportional gain
        float ki;  // Integral gain
        float kd;  // Derivative gain

        float previousError;
        float integralError;
        float derivativeError;

};

#endif  // ASSERVISSEMENT_HPP