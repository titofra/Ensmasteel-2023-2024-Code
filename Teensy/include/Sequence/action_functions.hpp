#ifndef ACTION_FUNCTIONS_HPP
#define ACTION_FUNCTIONS_HPP

#include "vector.hpp"
#include "kinetic.hpp"
#include <functional>
#include <math.h>

/* TRAJECTORY */
// NOTE: For all the trajectory fucntions, float variable "a" stands for a percentage of trajectory in [0.0f, 1.0f]

// Note that a 1-order (with starting and ending points) bezier will do the same. However this function is useful for rotation.
trajectory_fn linear (std::vector<VectorOriented> vectors) {
    return [=] (const float a) -> Kinetic {
        Kinetic ret = Kinetic (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        ret += (VectorOriented (vectors [1]) - vectors [0]) * (1 - a) + vectors [0];
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
trajectory_fn bezier (std::vector<VectorOriented> control_points) {
    // we process the Cj before the calls
    std::vector<VectorOriented> C;

    const int n = (int) control_points.size () - 1;
    int partial_permutation;    // https://en.wikipedia.org/wiki/Partial_permutation

    for (int j = 0; j <= n; j++) {
        // update partial permutation
        if (j <= 0) {
            partial_permutation = 1;
        } else {
            partial_permutation *= n - (j - 1);
        }

        // process the sum
        C.push_back (VectorOriented (0.0f, 0.0f, 0.0f));
        for (int i = 0; i <= j; i++) {
            C.back () += control_points [i] * ((float) std::pow (-1.0, (double) (i + j)) / (float) factorial (i) / (float) factorial (j - i));
        }

        C.back () = C.back () * (float) partial_permutation;
    }
    
    return [=] (const float a) -> Kinetic {
        // process the new Vector
        Kinetic ret = Kinetic (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        for (int j = 0; j <= n; j++) {
            ret += VectorOriented (C [j]) * (float) std::pow ((double) a, (double) j);
        }

        // process the orientation (this is the derivative of the trajectory)
        Kinetic tan = Kinetic (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        for (int j = 1; j <= n; j++) {
            tan += VectorOriented (C [j]) * ((float) j * (float) std::pow ((double) a, (double) (j - 1)));
        }

        // set the theta
        ret.setTheta (Vector (0.0f, 0.0f).angleWith (tan));

        return ret;
    };
}

trajectory_fn combine (trajectory_fn f1, trajectory_fn f2, const float comb_a) {
    return (
        [=](const float a) -> Kinetic {
            if (a <= comb_a) {
                return f1 (a / comb_a);
            }
            return f2 ((a - comb_a) / (1.0f - comb_a));
        }
    );
}


/* TIME DISTORTION */

time_distortion_fn linear (const unsigned long beginTime, const unsigned long endTime) {
    return (
        [=](const unsigned long t) -> float { return (float) (t - beginTime) / (float) (endTime - beginTime); }
    );
}

time_distortion_fn trapeze (const unsigned long t0, const unsigned long t1, const unsigned long t2, const unsigned long t3, const float dt01, const float dt23) {   // dt < 1 stands for space deceleration, dt > 1 stands for space acceleration // dt cannot be negative as it is a we cannot go backward in time!
    const float dt12 = (((float) t3 - (float) (t3 - t2) * dt23) - ((float) t0 + (float) (t1 - t0) * dt01)) / (float) (t2 - t1);
    
    return (
        [=](const unsigned long t) -> float {
            if (t < t1) {   // pente = dt01
                return (float) (
                    (unsigned long) ((float) (t - t0) * dt01)
                    ) / (float) (t3 - t0);
            }
            if (t < t2) {   // pente = dt12
                return (float) (
                    (unsigned long) ((float) (t1 - t0) * dt01)
                    + (unsigned long) ((float) (t - t1) * dt12)
                    ) / (float) (t3 - t0);
            }
            return (float) (// pente = dt23
                (unsigned long) ((float) (t1 - t0) * dt01)
                + (unsigned long) ((float) (t2 - t1) * dt12)
                + (unsigned long) ((float) (t - t2) * dt23)
                    ) / (float) (t3 - t0);
        }
    );
}

time_distortion_fn combine (time_distortion_fn f1, time_distortion_fn f2, const unsigned long beginTime, const unsigned long combTime, const unsigned long endTime) {
    return (
        [=](const unsigned long t) -> float {
            if (t <= combTime) {
                return f1 (t) * (float) (combTime - beginTime) / (float) (endTime - beginTime);
            }
            return f2 (t) * (float) (endTime - combTime) / (float) (endTime - beginTime) + (float) (combTime - beginTime) / (float) (endTime - beginTime);
        }
    );
}

#endif  // ACTION_FUNCTIONS_HPP