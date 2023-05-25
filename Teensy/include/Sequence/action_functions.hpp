#ifndef ACTION_FUNCTIONS_HPP
#define ACTION_FUNCTIONS_HPP

#include "kinetic.hpp"

#include <functional>

/* TRAJECTORY */
using trajectory_fn = std::function<Kinetic (unsigned long)>;

trajectory_fn linear (Kinetic beginKinetic, Kinetic endKinetic, unsigned long beginTime, unsigned long endTime, unsigned long dt) {
    const float theta_toface = beginKinetic.angleWith (endKinetic);
    return (
        [&beginKinetic, &endKinetic, &beginTime, &endTime, &dt, &theta_toface] (unsigned long t) {
            Kinetic ret = Kinetic (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

            if (t - dt < beginTime) {
                // this is the first call, the first dt
                // we rotate the robot in order to face the goal
                ret = Kinetic (beginKinetic);
                ret.setTheta (theta_toface);
            } else {
                if (t + dt > endTime) {
                    // this is the last call, the last dt
                    // we rotate the robot in order to reach the goals's theta
                    ret = Kinetic (endKinetic);
                } else {
                    ret = (endKinetic - beginKinetic) * (t - beginTime) / (endTime - beginTime) + beginKinetic;
                    ret.setTheta (theta_toface);    // we still have to face the end didn't reach the end
                }
            }

            return ret;
        }
    );
}


/* TIME DISTORTION */
using time_distortion_fn = std::function<unsigned long (unsigned long)>;

time_distortion_fn linear () {
    return (
        [](unsigned long t) { return t; }
    );
}

time_distortion_fn trapeze (unsigned long t0, unsigned long t1, unsigned long t2, unsigned long t3, float dt01, float dt23) {   // dt < 1 stands for space deceleration, dt > 1 stands for space acceleration // dt cannot be negative as it is a we cannot go backward in time!
    const unsigned long dt12 = ((t3 - (t3 - t2) * dt23) - (t0 + (t1 - t0) * dt01)) / (t2 - t1);
    
    return (
        [&t0, &t1, &t2, &dt01, &dt12, &dt23](unsigned long t) {
            if (t < t1) {   // pente = dt01
                return t0
                    + (unsigned long) (t - t0) * dt01;
            }
            if (t < t2) {   // pente = dt12
                return t0
                    + (unsigned long) (t1 - t0) * dt01
                    + (unsigned long) (t - t1) * dt12;
            }
            return t2   // pente = dt23
                + (unsigned long) (t - t2) * dt23;
        }
    );
}

#endif  // ACTION_FUNCTIONS_HPP