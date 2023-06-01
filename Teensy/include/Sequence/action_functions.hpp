#ifndef ACTION_FUNCTIONS_HPP
#define ACTION_FUNCTIONS_HPP

#include "vector.hpp"
#include "kinetic.hpp"
#include <functional>
#include <math.h>

/* TRAJECTORY */

// Note that a 2-order (with starting and ending points) bezier will do the same. However this function is useful for rotation.
trajectory_fn linear (const unsigned long beginTime, const unsigned long endTime, std::vector<VectorOriented> vectors) {
    return [=] (const unsigned long t) -> Kinetic {
        Kinetic ret = Kinetic (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        ret += (VectorOriented (vectors [1]) - vectors [0]) * ((float) (t - beginTime) / (float) (endTime - beginTime)) + vectors [0];
        return ret;
    };
}

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

// Notations come from https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Polynomial_form, check here for more
trajectory_fn bezier (const unsigned long beginTime, const unsigned long endTime, std::vector<VectorOriented> points) {
    return [=] (const unsigned long t) -> Kinetic {
        Kinetic ret = Kinetic (0.0f, 0.0f, 0.0f, 0.0f);
        const int n = (int) points.size () - 1;
        int partial_permutation;    // https://en.wikipedia.org/wiki/Partial_permutation
        VectorOriented sum;

        for (int j = 0; j <= n; j++) {
            // update partial permutation
            if (j <= 0) {
                partial_permutation = 1;
            } else {
                partial_permutation *= n - (j - 1);
            }

            // process the sum
            sum = VectorOriented (0.0f, 0.0f, 0.0f);
            for (int i = 0; i <= j; i++) {
                sum += VectorOriented (points [i]) * ((float) std::pow (-1.0, (double) (i + j)) / (float) factorial (i) / (float) factorial (j - i));
            }

            ret += sum * (float) std::pow ((double) (t - beginTime) / (double) (endTime - beginTime), (double) j) * (float) partial_permutation;
        }

        return ret;
    };
}


/* TIME DISTORTION */

time_distortion_fn linear () {
    return (
        [](unsigned long t) { return t; }
    );
}

time_distortion_fn trapeze (const unsigned long t0, const unsigned long t1, const unsigned long t2, const unsigned long t3, const float dt01, const float dt23) {   // dt < 1 stands for space deceleration, dt > 1 stands for space acceleration // dt cannot be negative as it is a we cannot go backward in time!
    const float dt12 = (((float) t3 - (float) (t3 - t2) * dt23) - ((float) t0 + (float) (t1 - t0) * dt01)) / (float) (t2 - t1);
    
    return (
        [=](unsigned long t) -> unsigned long {
            if (t < t1) {   // pente = dt01
                return t0
                    + (unsigned long) ((float) (t - t0) * dt01);
            }
            if (t < t2) {   // pente = dt12
                return t0
                    + (unsigned long) ((float) (t1 - t0) * dt01)
                    + (unsigned long) ((float) (t - t1) * dt12);
            }
            return t0      // pente = dt23
                + (unsigned long) ((float) (t1 - t0) * dt01)
                + (unsigned long) ((float) (t2 - t1) * dt12)
                + (unsigned long) ((float) (t - t2) * dt23);
        }
    );
}

#endif  // ACTION_FUNCTIONS_HPP