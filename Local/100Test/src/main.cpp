#include <kinetic.hpp>
#include <iostream>

#include <cmath>

int main () {
    for (float theta = 0.0f; theta < 7.0f; theta += 0.1f) {
        Kinetic a = Kinetic (10.0f, 10.0f, 0.0f, 0.0f, 0.0f);
        Kinetic b = Kinetic (10.0f + 150.0f * cos (theta), 10.0f + 150.0f * sin (theta), 0.0f, 0.0f, 0.0f);

        std::cout << theta << "   " << normalizeAngle (theta) << "   " << a.angleWith (b) << std::endl;
    }

    return 0;
}