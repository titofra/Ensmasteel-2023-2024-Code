#include "utils.hpp"

const double PI = 3.14159274101257324219;

bool AreEqual (double a, double b, double epsilon) {
    return std::fabs (a - b) < epsilon;
}

double normalizeAngle(double angle) {
    double out;
    out = angle - (2 * PI) * ((int)(angle / (2 * PI)));
    if (out > PI)
        return (out - 2 * PI);
    else if (out <= -PI)
        return (out + 2 * PI);

    return out;
}

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}