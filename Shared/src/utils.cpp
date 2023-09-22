#include "utils.hpp"

bool AreEqual (double a, double b, double epsilon) {
    return std::fabs (a - b) < epsilon;
}