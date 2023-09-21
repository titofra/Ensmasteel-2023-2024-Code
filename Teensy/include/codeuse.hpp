#ifndef Coder_HPP
#define Coder_HPP

#include <Arduino.h>
#include <Encoder.h>

/**
 * @brief Classe définissant les codeuses
 */
class Codeuse{
    public :
        /**
         * @brief Constructeur de la classe Codeuse
         * @param pinCodA : pin A de la codeuse
         * @param pinCodB : pin B de la codeuse
         * @param ticksPerRound : nombre fixe de ticks par tour de roue (à voir en fonction de la codeuse peut être 2048-4096-8192)
         * @param wDiam : diametre de la roue de la codeuse (en m)
         * @param orient : booleen, orientation de la codeuse
         */
        Codeuse (uint8_t pinCodA, uint8_t pinCodB, int32_t ticksPerRound, double wheelDiameter, bool orientation);
        Codeuse () {};
        ~Codeuse ();

        /**
         * @brief Fonction d'actualisation des valeurs de vitesse du robot en fonction du nombre de ticks depuis la derniere actualisation)
         */
        void update ();

        /**
         * @brief Obtient l'avancement de la codeuse depuis la derniere actualisation
         * @return Avancement du robot d'après le codeuse
         */
        double getDeltaAvance();

    private :
        Encoder *encoder; //Encoder de la codeuse permet les interruptions (je crois)
        int32_t ticksPerRound; //Nombre de ticks en un tour de roue
        double wheelDiameter; //Diamètre de la roue sur laquelle la codeuse est
        int32_t prev_ticks; //sert à comparer combien de ticks on a effectué
        int32_t ticks;
        double deltaAvance;
        bool orientation; //true si codeuse montee a l'endroit, false sinon

};

#endif