#ifndef ACTION_FUNCTIONS_HPP
#define ACTION_FUNCTIONS_HPP

#include "vector.hpp"
#include "kinetic.hpp"
#include <functional>
#include <math.h>

/* TRAJECTORY */
// NOTE: For all the trajectory fucntions, double variable "a" stands for a percentage of trajectory in [0.0, 1.0]

// Note that a 1-order (with starting and ending points) bezier will do the same. However this function is useful for rotation.
trajectory_fn linear (std::vector<VectorOriented> extremums) {
    return [=] (const double a) -> Kinetic {
        Kinetic ret = Kinetic (0.0, 0.0, 0.0, 0.0, 0.0);
        ret += (VectorOriented (extremums [1]) - extremums [0]) * a + extremums [0];
        return ret;
    };
}

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

// WARNINGS: Bezier curves are not linear over time (there is a time ditortion).
// WARNINGS: Bezier curves don't care of theta
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
        C.push_back (VectorOriented (0.0, 0.0, 0.0));
        for (int i = 0; i <= j; i++) {
            C.back () += control_points [i] * ((double) std::pow (-1.0, (double) (i + j)) / (double) factorial (i) / (double) factorial (j - i));
        }

        C.back () = C.back () * (double) partial_permutation;
    }
    
    return [=] (const double a) -> Kinetic {
        // process the new Vector
        Kinetic ret = Kinetic (0.0, 0.0, 0.0, 0.0, 0.0);
        for (int j = 0; j <= n; j++) {
            ret += VectorOriented (C [j]) * (double) std::pow ((double) a, (double) j);
        }

        // process the orientation (this is the derivative of the trajectory)
        Kinetic tan = Kinetic (0.0, 0.0, 0.0, 0.0, 0.0);
        for (int j = 1; j <= n; j++) {
            tan += VectorOriented (C [j]) * ((double) j * (double) std::pow ((double) a, (double) (j - 1)));
        }

        // set the theta
        ret.setTheta (Vector (0.0, 0.0).angleWith (tan));

        return ret;
    };
}

trajectory_fn bezier_auto (std::vector<VectorOriented> extremums, const double delta_curve) {
    std::vector<VectorOriented> control_points;
    control_points.push_back (extremums [0]);
    control_points.push_back (extremums [0] + VectorOriented (std::cos (extremums [0].getTheta ()), std::sin (extremums [0].getTheta ()), 0.0) * delta_curve);
    control_points.push_back (extremums [1] - VectorOriented (std::cos (extremums [1].getTheta ()), std::sin (extremums [1].getTheta ()), 0.0) * delta_curve);
    control_points.push_back (extremums [1]);

    return bezier (control_points);
}


trajectory_fn combine (trajectory_fn f1, trajectory_fn f2, const double comb_a) {
    return (
        [=](const double a) -> Kinetic {
            if (a <= comb_a) {
                return f1 (a / comb_a);
            }
            return f2 ((a - comb_a) / (1.0 - comb_a));
        }
    );
}


/* TIME DISTORTION */

time_distortion_fn linear (const unsigned long beginTime, const unsigned long endTime) {
    return (
        [=](const unsigned long t) -> double { return (double) (t - beginTime) / (double) (endTime - beginTime); }
    );
}

time_distortion_fn trapeze (const unsigned long t0, const unsigned long t1, const unsigned long t2, const unsigned long t3, const double dt01, const double dt23) {   // dt < 1 stands for space deceleration, dt > 1 stands for space acceleration // dt cannot be negative as it is a we cannot go backward in time!
    const double dt12 = (((double) t3 - (double) (t3 - t2) * dt23) - ((double) t0 + (double) (t1 - t0) * dt01)) / (double) (t2 - t1);
    
    return (
        [=](const unsigned long t) -> double {
            if (t < t1) {   // pente = dt01
                return (double) (
                    (unsigned long) ((double) (t - t0) * dt01)
                    ) / (double) (t3 - t0);
            }
            if (t < t2) {   // pente = dt12
                return (double) (
                    (unsigned long) ((double) (t1 - t0) * dt01)
                    + (unsigned long) ((double) (t - t1) * dt12)
                    ) / (double) (t3 - t0);
            }
            return (double) (// pente = dt23
                (unsigned long) ((double) (t1 - t0) * dt01)
                + (unsigned long) ((double) (t2 - t1) * dt12)
                + (unsigned long) ((double) (t - t2) * dt23)
                    ) / (double) (t3 - t0);
        }
    );
}

time_distortion_fn combine (time_distortion_fn f1, time_distortion_fn f2, const unsigned long beginTime, const unsigned long combTime, const unsigned long endTime) {
    return (
        [=](const unsigned long t) -> double {
            if (t <= combTime) {
                return f1 (t) * (double) (combTime - beginTime) / (double) (endTime - beginTime);
            }
            return f2 (t) * (double) (endTime - combTime) / (double) (endTime - beginTime) + (double) (combTime - beginTime) / (double) (endTime - beginTime);
        }
    );
}

#endif  // ACTION_FUNCTIONS_HPP