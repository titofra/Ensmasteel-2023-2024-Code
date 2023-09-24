#ifndef KINETIC_HPP
#define KINETIC_HPP

#include <string>
#include <Arduino.h>
#include <Stream.h>
#include "vector_oriented.hpp"

/**
 * @brief Class representing a kinetic. Inheritted from VectorOriented 
 */
class Kinetic : public VectorOriented {
    public :
        /**
         * @brief Construct a new Kinetic object
         *
         * @param x Initial coordinate X (default is 0.0)
         * @param y Initial coordinate Y (default is 0.0)
         * @param theta Initial vector's rotation (default is 0.0) 
         * @param v Initial speed (default is 0.0)
         * @param w Initial rotation speed (default is 0.0)
         */
        Kinetic (double x = 0.0, double y = 0.0, double theta = 0.0, double v = 0.0, double w = 0.0);

        /**
         * @brief Construct a new Kinetic object from another one
         * 
         * @param kinetic The kinetic object to be copied
         */
        Kinetic (const Kinetic& kinetic);

        /**
         * @brief Operator=
         * 
         * @param other The Kinetic to be used as right value
         * @return A left value Kinetic
         */
        Kinetic& operator=(const Kinetic& other);

        /**
         * @brief Operator==
         * 
         * @param other The Kinetic to be compared
         * @return true if they are equal, else false
         */
        bool operator== (Kinetic const &other);

        /**
         * @brief Operator-
         * 
         * @param other The kinetic to substract
         * @return The result
         */
        Kinetic operator- (Kinetic const &other);

        /**
         * @brief Operator+
         * 
         * @param other The kinetic to add
         * @return The result
         */
        Kinetic operator+ (Kinetic const &other);

        /**
         * @brief Operator/
         * 
         * @param other The kinetic to divide
         * @return The result
         */
        Kinetic operator/ (double const &other);

        /**
         * @brief Operator*
         * 
         * @param other The kinetic to multiply
         * @return The result
         */
        Kinetic operator* (double const &other);

        /**
         * @brief Get the translation speed
         * 
         * @return The translation speed
         */
        double getTranslationSpeed () const ;

        /**
         * @brief Set the translation speed
         * 
         * @param value The new translation speed
         */
        void setTranslationSpeed(double value);

        /**
         * @brief Get the rotation speed
         * 
         * @return The rotation speed
         */
        double getRotationSpeed() const ;

        /**
         * @brief Set the rotation speed
         * 
         * @param value The new rotation speed
         */
        void setRotationSpeed(double value);

        /**
         * @brief Print vector's coordinates on the serial
         * @param prefix A prefix to print on the same line before vector's coordinates
         * @param serial The stream where to print on
         */
        void printDebug(const char *prefix, Stream *serial) const;

    private :
        double v;
        double w;
};

#endif  // KINETIC_HPP