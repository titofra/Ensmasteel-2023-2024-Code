#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>
#include <Arduino.h>
#include <Stream.h>
#include <math.h>

/**
 * Normalisation d'un angle.
 * @param angle : float, angle en radian.
 * @return : float, angle en radian entre -PI et PI.
 */
float normalizeAngle (float angle);

/**
 * Classe definissant un vecteur-coordonnee de base (x,y)
*/
class Vector {
    public :
        /**
          * Constructeur d'un vecteur-coordonnee
          * @param x : float, x-coordonnee
          * @param y : float, y-coordonnee
          */
        Vector (float x = 0.0f, float y = 0.0f);
        Vector (Vector& vect);

        //Surcharges des operateurs +, +=, -, *, ==
        Vector operator+ (const Vector &other);
        Vector operator- (const Vector &other);
        Vector operator* (const float scalaire);
        void operator+= (const Vector &other);
        bool operator== (const Vector &other);

        Vector& operator=(const Vector& other);

        /**
          * @return Norme du vecteur-coordonnee
          */
        float norm();

        /**
          * @return Angle par rapport au vecteur normalise du vecteur-coordonnee
          */
        float angle();

        /**
          * @return Distance entre deux vecteurs-coordonnees
          * @param other : Vector, le deuxieme vecteur
          */
        float distanceWith(Vector &other);

        /**
          * @return Angle entre deux vecteurs-coordonnees
          * @param other : Vector, le deuxieme vecteur
          */
        float angleWith(Vector &other);

        /**
          * @return Coordonnee x
          */
        float getX();  

        /**
          * @return Coordonnee y
          */
        float getY();

            /**
          * @param x : Nouvelle coordonnee x
          */
        void setX(float value);  

        /**
          * @param y : Nouvelle coordonnee y
          */
        void setY(float value);

        void printDebug(const char *prefix, Stream *serial);

    protected :
        float x, y;
};

#endif  // VECTOR_HPP