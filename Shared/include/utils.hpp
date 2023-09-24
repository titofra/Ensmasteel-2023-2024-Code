#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>
#include <cmath>

/**
 * @brief Compare two double values relatively to a threshold
 *
 * @param a The first value
 * @param b The second value
 * @param epsilon The treshold (default is the standard double epsilon which is given by `std::numeric_limits<double>::epsilon ()`)
 * @return true if they are equal, else false
 */
bool AreEqual (double a, double b, double epsilon = std::numeric_limits<double>::epsilon ());

/**
 * @brief Normalize an angle to fit in (-PI, PI]
 * 
 * @param angle Angle in radian
 * @return Normalized angle in (-PI, PI]
 */
double normalizeAngle (double angle);

/**
 * @brief Factorial function
 * 
 * @param n The input
 * @return The factorial of n
 */
int factorial(int n);

#endif  // UTILS_HPP