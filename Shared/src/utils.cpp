#include "utils.hpp"

bool AreEqual (double a, double b, double epsilon) {
    return a > b - epsilon && a < b + epsilon;
}