#ifndef ACTION_FUNCTIONS_HPP
#define ACTION_FUNCTIONS_HPP

#include <Vectors/kinetic.hpp>


/* TRAJECTORY */
using trajectory_fn = Kinetic(*)(float);

trajectory_fn linear (Kinetic beginKinetic, Kinetic endKinetic, float beginTime, float endTime) {
    return (
        [](float t) { return (endKinetic - beginKinetic) * (t - beginTime) / (endTime - beginTime) + beginKinetic; }
    );
}


/* TIME DISTORTION */
using time_distortion_fn = float(*)(float);

time_distortion_fn linear (float beginTime, float endTime) {
    return (
        [](float t) { return t; }
    );
}

time_distortion_fn trapeze (float t0, float t1, float t2, float t3, float dt01, float dt23) {   // dt < 1 stands for space deceleration, dt > 1 stands for space acceleration // dt cannot be negative as it is a we cannot go backward in time!
    return (
        [](float t) {
            if (t < t1) {   // pente = dt01
                return t0
                    + (t - t0) * dt01;
            }
            if (t < t2) {   // pente = ((t3 - (t3 - t2) * dt03) - (t0 + (t1 - t0) * dt01)) / (t2 - t1)
                return t0
                    + (t1 - t0) * dt01
                    + (t - t1) * ((t3 - (t3 - t2) * dt03) - (t0 + (t1 - t0) * dt01)) / (t2 - t1);
            }
            return t2   // pente = dt23
                + (t - t2) * dt23;
        }
    );
}


#endif  // ACTION_FUNCTIONS_HPP