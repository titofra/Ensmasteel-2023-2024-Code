#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

#include <Arduino.h>
#include <codeuse.hpp>
#include <Vector.h>

class Odometry{
    public :
        /**
         * @brief Constructeur de la classe Odometry : 
         * @param CodeuseL : la codeuse gauche
         * @param CodeuseR : la codeuse droite
         * @param cSpacing : float, parametre fixe d'eloignement des codeuses
         */
        Odometry(Codeuse *codeuseL, Codeuse *codeuseR, float cSpacing, Kinetic *kinetic);
        Odometry(){};

        /**
         * @brief Fonction d'update de l'odometrie en fonction du temps qui s'est deroule
         * @param dt : float, temps d'update, depend de la frequence du robot$
         * @param kinetics : Kinetic*, la cinetique
         */
        void updateOdometry(float dt, Kinetic *kinetics);

    private :
        Codeuse *codeuseLeft;
        Codeuse *codeuseRight;
        float codeusesSpacing;
        Kinetic *kinetics;

};

#endif