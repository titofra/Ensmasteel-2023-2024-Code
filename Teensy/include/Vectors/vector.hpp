#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>
#include <Stream.h>
#include "utils.hpp"

class Vector {
  public:
      /**
       * @brief Parameterized constructor for Vector
       * @param xValue The x-coordinate value
       * @param yValue The y-coordinate value
       */
      Vector(double xValue = 0.0, double yValue = 0.0);

      /**
       * @brief Construct a Vector from another Vector
       * @param other The Vector object to construct from
       */
      Vector(const Vector& other);

      /**
       * @brief Get the x-coordinate
       * @return The x-coordinate value
       */
      double getX() const;

      /**
       * @brief Get the y-coordinate
       * @return The y-coordinate value
       */
      double getY() const;

      /**
       * @brief Set the x-coordinate
       * @param xValue The x-coordinate value to be set
       */
      void setX(double xValue);

      /**
       * @brief Set the y-coordinate
       * @param yValue The y-coordinate value to be set
       */
      void setY(double yValue);

      /**
       * @brief Assignment operator Assigns the values of another Vector object to this object
       * @param other The Vector object to be assigned
       * @return A reference to the updated Vector object
       */
      Vector& operator=(const Vector& other);

      /**
       * @brief Addition of two vectors
       * @param other The vector to be added
       * @return The resulting vector after addition
       */
      Vector operator+(const Vector& other) const;

      /**
       * @brief Subtraction of two vectors
       * @param other The vector to be subtracted
       * @return The resulting vector after subtraction
       */
      Vector operator-(const Vector& other) const;

      /**
       * @brief Scalar multiplication of a vector
       * @param scalar The scalar value to multiply the vector
       * @return The resulting vector after scalar multiplication
       */
      Vector operator*(double scalar) const;

      /**
       * @brief Scalar division of a vector
       * @param scalar The scalar value to divide the vector
       * @return The resulting vector after scalar division
       */
      Vector operator/(double scalar) const;

      /**
       * @brief Compound addition of two vectors
       * @param other The vector to be added
       * @return Reference to the resulting vector after addition
       */
      Vector& operator+=(const Vector& other);

      /**
       * @brief Compound subtraction of two vectors
       * @param other The vector to be subtracted
       * @return Reference to the resulting vector after subtraction
       */
      Vector& operator-=(const Vector& other);

      /**
       * @brief Compound scalar multiplication of a vector
       * @param scalar The scalar value to multiply the vector
       * @return Reference to the resulting vector after scalar multiplication
       */
      Vector& operator*=(double scalar);

      /**
       * @brief Compound scalar division of a vector
       * @param scalar The scalar value to divide the vector
       * @return Reference to the resulting vector after scalar division
       */
      Vector& operator/=(double scalar);

      // Comparison operators

      /**
       * @brief Check if two vectors are equal
       * @param other The vector to compare with
       * @return True if the vectors are equal, false otherwise
       */
      bool operator==(const Vector& other) const;

      /**
       * @brief Check if two vectors are not equal
       * @param other The vector to compare with
       * @return True if the vectors are not equal, false otherwise
       */
      bool operator!=(const Vector& other) const;

      /**
       * @brief Compare the norm of two vectors
       * @param other The vector to compare with
       * @return True if the norm of this vector is less than the norm of the other vector, false otherwise
       */
      bool operator<(const Vector& other) const;

      /**
       * @brief Compare the norm of two vectors
       * @param other The vector to compare with
       * @return True if the norm of this vector is greater than the norm of the other vector, false otherwise
       */
      bool operator>(const Vector& other) const;

      /**
       * @brief Compare the norm of two vectors
       * @param other The vector to compare with
       * @return True if the norm of this vector is less than or equal to the norm of the other vector, false otherwise
       */
      bool operator<=(const Vector& other) const;

      /**
       * @brief Compare the norm of two vectors
       * @param other The vector to compare with
       * @return True if the norm of this vector is greater than or equal to the norm of the other vector, false otherwise
       */
      bool operator>=(const Vector& other) const;

      /**
       * @brief Dot product of two vectors
       * @param other The other vector
       * @return The dot product of the two vectors
       */
      double dotProduct(const Vector& other) const;

      /**
       * @brief Norm of the vector
       * @return The norm of the vector
       */
      double norm() const;

      /**
       * @brief Angle of the vector
       * @return The angle of the vector
       */
      double angle() const;

      /**
       * @brief Normalize the vector
       */
      void normalize();

      /**
       * @brief Calculate the perpendicular vector
       * @return The perpendicular vector
       */
      Vector perpendicular() const;

      /**
       * @return Distance between two vectors
       * @param other The second vector
       * @return The distance
       */
      double distanceWith(Vector &other) const;

      /**
       * @return Angle between two vectors
       * @param other The second vector
       * @return The normalized angle
       */
      double angleWith(const Vector &other) const;

      /**
       * @brief Print vector's coordinates on the serial
       * @param prefix A prefix to print on the same line before vector's coordinates
       * @param serial The stream where to print on
       */
      void printDebug(const char *prefix, Stream *serial) const;

  protected:
      double x;
      double y;

};

#endif  // VECTOR_HPP