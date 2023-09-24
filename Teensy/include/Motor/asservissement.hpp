#ifndef ASSERVISSEMENT_HPP
#define ASSERVISSEMENT_HPP

/**
 * @brief Class that stands for an asservissement
 */
class Asservissement{
    public :
        /**
         * @brief Construct a new Asservissement object
         * 
         * @param kp The proportional gain
         * @param ki The integral gain
         * @param kd The derivative gain
         */
        Asservissement (double kp, double ki, double kd);

        /**
         * @brief Construct a new Asservissement object
         */
        Asservissement () {};

        /**
         * @brief Computes the control signals for the robotic system based on the PID controllers
         * 
         * @param error The error to face
         * @param dt Time elapsed since the last control signal was computed
         * @return The input that has to be given to the motor
         */
        double compute (double error, unsigned long dt);
    
    private:
        double kp;
        double ki;
        double kd;

        double previousError;
        double integralError;
        double derivativeError;

};

#endif  // ASSERVISSEMENT_HPP