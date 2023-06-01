#ifndef ACTION_FUNCTIONS_HPP
#define ACTION_FUNCTIONS_HPP

#include "kinetic.hpp"
#include <functional>

/* TRAJECTORY */

trajectory_fn linear (const unsigned long beginTime, const unsigned long endTime, const unsigned long dt) {
    return [=] (const unsigned long t, const Kinetic beginKinetic, const Kinetic endKinetic) -> Kinetic
        {
            const float theta_toface = beginKinetic.angleWith (endKinetic);
            /*Serial.println ("## FULLTEST");
            beginKinetic.printDebug ("begKin ", &Serial);
            endKinetic.printDebug ("endKin ", &Serial);
            Serial.println (beginTime);
            Serial.println (endTime);
            Serial.println (theta_toface);
            Serial.println (t);
            Serial.println ("## DONE");*/
            if (t - dt < beginTime) {
                // this is the first call, the first dt
                // we rotate the robot in order to face the goal
                Kinetic ret = Kinetic (beginKinetic);
                ret.setTheta (theta_toface);
                return ret;
            } else {
                if (t + dt > endTime) {
                    // this is the last call, the last dt
                    // we rotate the robot in order to reach the goals's theta
                    return Kinetic (endKinetic);
                } else {
                    Kinetic ret = (Kinetic (endKinetic) - beginKinetic) * (t - beginTime) / (endTime - beginTime) + beginKinetic;
                    ret.setTheta (theta_toface);    // we still have to face the end didn't reach the end
                    return ret;
                }
            }
        };
}


/* TIME DISTORTION */

time_distortion_fn linear () {
    return (
        [](unsigned long t) { return t; }
    );
}

time_distortion_fn trapeze (const unsigned long t0, const unsigned long t1, const unsigned long t2, const unsigned long t3, const float dt01, const float dt23) {   // dt < 1 stands for space deceleration, dt > 1 stands for space acceleration // dt cannot be negative as it is a we cannot go backward in time!
    const unsigned long dt12 = ((t3 - (t3 - t2) * dt23) - (t0 + (t1 - t0) * dt01)) / (t2 - t1);
    
    return (
        [=](unsigned long t) {
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