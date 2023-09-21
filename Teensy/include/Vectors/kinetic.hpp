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
         * @param x : double, Position en x
         * @param y : double, Position en y
         * @param theta : double : Angle d'orientation
         * @param v : double, Vitesse de translation du robot
         * @param w : double, Vitesse de rotation du robot
         */
        Kinetic (double x = 0.0, double y = 0.0, double theta = 0.0, double v = 0.0, double w = 0.0);
        Kinetic (const Kinetic& kinetic);

        Kinetic& operator=(const Kinetic& other);

        bool operator== (Kinetic const &other);
        Kinetic operator- (Kinetic const &other);
        Kinetic operator+ (Kinetic const &other);
        Kinetic operator/ (double const &other);
        Kinetic operator* (double const &other);

        /**
         * @return Vitesse de translation du robot
         */
        double getTranslationSpeed () const ;

        /**
         * @param v : Nouvelle vitesse de translation
         */
        void setTranslationSpeed(double value);

            /**
         * @return Vitesse de rotation du robot
         */
        double getRotationSpeed() const ;

        /**
         * @param w : Nouvelle vitesse de rotation
         */
        void setRotationSpeed(double value);

        /**
         * Prints in Serial consol kinetic parameters :
         * x, y, Theta, v, w
         * @param prefix : string being printed in serial monitor
         */
        void printDebug(const char *prefix, Stream *serial) const;

    private :
        double v; //Vitesse de translation du robot
        double w; //Vitesse de rotation du robot
};

#endif  // KINETIC_HPP