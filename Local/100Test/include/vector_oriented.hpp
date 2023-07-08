#ifndef VECTOR_ORIENTED_HPP
#define VECTOR_ORIENTED_HPP

#include <string>
//#include <Stream.h>
#include "vector.hpp"

#include <iostream>

class VectorOriented : public Vector {
    public:
        /**
         * @brief Default constructor. Initializes the VectorOriented with zero values.
         */
        VectorOriented(float xValue = 0.0f, float yValue = 0.0f, float thetaValue = 0.0f);

        /**
         * @brief Copy constructor. Creates a new VectorOriented object by copying the values from another VectorOriented object.
         * @param other The VectorOriented object to be copied.
         */
        VectorOriented(const VectorOriented& other);

        /**
         * @brief Get the theta value of the VectorOriented.
         * @return The theta value in radians.
         */
        float getTheta() const;

        /**
         * @brief Set the theta value of the VectorOriented.
         * @param thetaValue The theta value in radians.
         */
        void setTheta(float thetaValue);

        /**
         * @brief Calculate the perpendicular vector.
         * @return The perpendicular vector as a new VectorOriented object.
         */
        VectorOriented perpendicular() const;

        /**
         * @brief Assignment operator. Assigns the values of another VectorOriented object to this object.
         * @param other The VectorOriented object to be assigned.
         * @return A reference to the updated VectorOriented object.
         */
        VectorOriented& operator=(const VectorOriented& other);

        /**
         * @brief Perform vector addition between two VectorOriented objects.
         * @param other The VectorOriented object to be added.
         * @return The resulting VectorOriented object after addition.
         */
        VectorOriented operator+(const VectorOriented& other) const;

        /**
         * @brief Perform vector subtraction between two VectorOriented objects.
         * @param other The VectorOriented object to be subtracted.
         * @return The resulting VectorOriented object after subtraction.
         */
        VectorOriented operator-(const VectorOriented& other) const;

        /**
         * @brief Perform scalar multiplication of the VectorOriented object.
         * @param scalar The scalar value to multiply the vector with.
         * @return The resulting VectorOriented object after scalar multiplication.
         */
        VectorOriented operator*(float scalar) const;

        /**
         * @brief Perform scalar division of the VectorOriented object.
         * @param scalar The scalar value to divide the vector by.
         * @return The resulting VectorOriented object after scalar division.
         */
        VectorOriented operator/(float scalar) const;

        /**
         * @brief Perform compound addition of two VectorOriented objects.
         * @param other The VectorOriented object to be added.
         * @return The resulting VectorOriented object after compound addition.
         */
        VectorOriented& operator+=(const VectorOriented& other);

        /**
         * @brief Perform compound subtraction of two VectorOriented objects.
         * @param other The VectorOriented object to be subtracted.
         * @return The resulting VectorOriented object after compound subtraction.
         */
        VectorOriented& operator-=(const VectorOriented& other);

        /**
         * @brief Perform compound scalar multiplication of the VectorOriented object.
         * @param scalar The scalar value to multiply the vector with.
         * @return The resulting VectorOriented object after compound scalar multiplication.
         */
        VectorOriented& operator*=(float scalar);

        /**
         * @brief Perform compound scalar division of the VectorOriented object.
         * @param scalar The scalar value to divide the vector by.
         * @return The resulting VectorOriented object after compound scalar division.
         */
        VectorOriented& operator/=(float scalar);

        /**
         * @brief Check if the VectorOriented object is equal to another VectorOriented object.
         * @param other The VectorOriented object to compare with.
         * @return True if the VectorOriented objects are equal, false otherwise.
         */
        bool operator==(const VectorOriented& other) const;

        /**
         * @brief Check if the VectorOriented object is not equal to another VectorOriented object.
         * @param other The VectorOriented object to compare with.
         * @return True if the VectorOriented objects are not equal, false otherwise.
         */
        bool operator!=(const VectorOriented& other) const;

        /**
          * @brief Normalize theta to fit in (-PI, PI]
          */
        void normalizeTheta ();

        //void printDebug (const char *prefix, Stream *serial) const;

        void printDebug (const char *prefix) const;

    protected:
        float theta;
};

#endif  // VECTOR_ORIENTED