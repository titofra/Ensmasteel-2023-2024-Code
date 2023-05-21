#ifndef KINETIC_HPP
#define KINETIC_HPP

#include <Vectors/vector_oriented.hpp>

/**
 * Classe definissant la cinetique du robot c'est a dire sa situation en positionnement et en vitesse
*/
class Kinetic : public VectorOriented{
    public :
        /**
         * Constructeur de la classe Kinetic 
         * @param x : float, Position en x
         * @param y : float, Position en y
         * @param theta : float : Angle d'orientation
         * @param v : float, Vitesse de translation du robot
         * @param w : float, Vitesse de rotation du robot 
         */
        Kinetic (float x = 0.0f, float y = 0.0f, float theta = 0.0f, float v = 0.0f, float w = 0.0f);

        bool operator== (Kinetic const &other);

        /**
         * @return Vitesse de translation du robot
         */
        float getTranslationSpeed ();

        /**
         * @param v : Nouvelle vitesse de translation
         */
        void setTranslationSpeed(float v);

            /**
         * @return Vitesse de rotation du robot
         */
        float getRotationSpeed();

        /**
         * @param w : Nouvelle vitesse de rotation
         */
        void setRotationSpeed(float w);

        /**
         * Prints in Serial consol kinetic parameters :
         * x, y, Theta, v, w
         * @param prefix : string being printed in serial monitor
         */
        void printDebug(const String& prefix);

    private :
        float v; //Vitesse de translation du robot
        float w; //Vitesse de rotation du robot
};

#endif  // KINETIC_HPP