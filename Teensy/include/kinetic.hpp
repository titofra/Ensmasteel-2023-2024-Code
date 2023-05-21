#ifndef KINETIC_HPP
#define KINETIC_HPP

#include <logger.hpp>
#include <vectors.hpp>

/**
 * Classe definissant la cinetique du robot c'est a dire sa situation en positionnement et en vitesse
*/
class Kinetic : public VectorOriented{
    public :
        /**
         * Constructeur de la classe Kinetic 
         * @param x : float, Position en x
         * @param y : float, Position en y
         * @param th : float : Angle d'orientation
         * @param v : float, Vitesse de translation du robot
         * @param w : float, Vitesse de rotation du robot 
         */
        Kinetic(float x=0.0, float y=0.0, float th=0.0, float v=0.0, float w=0.0);

        bool operator==(Kinetic const &other);

        /**
         * @return Vitesse de translation du robot
         */
        float getTranslationSpeed();

        /**
         * @param ts : Nouvelle vitesse de translation
         */
        void setTranslationSpeed(float ts);

            /**
         * @return Vitesse de rotation du robot
         */
        float getRotationSpeed();

        /**
         * @param rs : Nouvelle vitesse de rotation
         */
        void setRotationSpeed(float rs);

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