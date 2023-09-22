#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>
#include <cmath>

bool AreEqual (double a, double b, double epsilon = std::numeric_limits<double>::epsilon ());

#endif  // UTILS_HPP