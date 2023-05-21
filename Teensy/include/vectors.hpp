#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <utils.hpp>

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

        //Surcharges des operateurs +, +=, -, *, ==
        Vector operator+ (const Vector &other);
        Vector operator- (const Vector &other);
        Vector operator* (const float scalaire);
        void operator+= (const Vector &other);
        bool operator== (const Vector &other);

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
        void setX(float x);  

        /**
          * @param y : Nouvelle coordonnee y
          */
        void setY(float y);

        void printDebug(const String& prefix);

    private :
        float x, y;
};

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
        VectorOriented(float x = 0.0f, float y = 0.0f, float theta = 0.0f);

        bool operator== (VectorOriented const &other);
        VectorOriented operator- (VectorOriented const &other);

        /**
         * @return Angle d'orientation theta
         */
        float getTheta ();

        /**
         * @param theta : Nouvel angle theta
         */
        void setTheta (float theta);

        /**
         * Normalisation de l'angle theta (mise en radian entre 0 et 2PI)
         * @return Angle theta normalise
         */
        void normalizeTheta ();

        void printDebug (const String& prefix);

    private :
        float theta;  

};

#endif  // VECTORS_HPP