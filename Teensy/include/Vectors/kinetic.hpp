#ifndef KINETIC_HPP
#define KINETIC_HPP

#include <string>
#include <Arduino.h>
#include <Stream.h>
#include "vector_oriented.hpp"

/**
 * Classe definissant la cinetique du robot c'est a dire sa situation en positionnement et en vitesse
*/
class Kinetic : public VectorOriented {
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
        Kinetic (const Kinetic& kinetic);

        Kinetic& operator=(const Kinetic& other);

        bool operator== (Kinetic const &other);
        Kinetic operator- (Kinetic const &other);
        Kinetic operator+ (Kinetic const &other);
        Kinetic operator/ (float const &other);
        Kinetic operator* (float const &other);

        /**
         * @return Vitesse de translation du robot
         */
        float getTranslationSpeed () const ;

        /**
         * @param v : Nouvelle vitesse de translation
         */
        void setTranslationSpeed(float value);

            /**
         * @return Vitesse de rotation du robot
         */
        float getRotationSpeed() const ;

        /**
         * @param w : Nouvelle vitesse de rotation
         */
        void setRotationSpeed(float value);

        /**
         * Prints in Serial consol kinetic parameters :
         * x, y, Theta, v, w
         * @param prefix : string being printed in serial monitor
         */
        void printDebug(const char *prefix, Stream *serial) const;

    private :
        float v; //Vitesse de translation du robot
        float w; //Vitesse de rotation du robot
};

#endif  // KINETIC_HPP