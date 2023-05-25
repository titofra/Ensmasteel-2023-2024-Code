#ifndef VECTOR_ORIENTED_HPP
#define VECTOR_ORIENTED_HPP

#include <string>
#include <Arduino.h>
#include <Stream.h>
#include "vector.hpp"

/**
 *Classe etendu de la classe Vector : Rajout d'un angle d'orientation du robot
*/
class VectorOriented : public Vector {
    public :
        /**
         * Constructeur d'un vecteur oriente
         * @param x : float, x-coordonnee
         * @param y : float, y-coordonnee
         * @param theta : float, orientation du robot
         */
        VectorOriented (float x = 0.0f, float y = 0.0f, float th = 0.0f);
        VectorOriented (VectorOriented& vo);

        bool operator== (VectorOriented const &other);
        VectorOriented operator- (VectorOriented const &other);
        VectorOriented operator+ (VectorOriented const &other);
        VectorOriented operator/ (float const &other);
        VectorOriented operator* (float const &other);

        VectorOriented& operator=(const VectorOriented& other);

        /**
         * @return Angle d'orientation theta
         */
        float getTheta ();

        /**
         * @param theta : Nouvel angle theta
         */
        void setTheta (float value);

        /**
         * Normalisation de l'angle theta (mise en radian entre 0 et 2PI)
         * @return Angle theta normalise
         */
        void normalizeTheta ();

        void printDebug (const char *prefix, Stream *serial);

    protected :
        float theta;
};

#endif  // VECTOR_ORIENTED