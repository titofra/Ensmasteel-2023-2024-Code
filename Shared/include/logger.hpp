#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <Arduino.h>
#include <Print.h>

/**
 * @brief Classe definissant les messages renvoyes par les cartes a l'utilisateur
 */
class Logger {
    public :
        /**
         * @brief Permet de parametrer le Logger avec la carte et les differents ports
         * @brief Est static car permet de ne pas avoir de constructeurs donc de pouvoir l'utiliser "sans creer un objet" et le passer an parametres de fonctions des qu'on en a besoin
         * @param infoSerial : Serial sur lequel les donnees informatives sont transmises
         * @param debugSerial : Serial sur lequel les donnes de debugage sont transmises (a utiliser pour chercher des erreurs de code)
         * @param info : Booleen indiquant si le canal info est active
         * @param debug : Booleen indiquant si le canal debug est active
         */
        static void setup(Print* info_Serial, Print* debug_Serial, bool info = true, bool debug = true);

        /**
         * @brief Permet d'ecrire sur le canal info
         * @param message : String, Message a ecrire sur le canal info
         */
        static void infoln(const String &message);

        /**
         * @brief Permet d'ecrire sur le canal debug
         * @param message : String, Message a ecrire sur le canal debug
         */
        static void debugln(const String &message);

    private :
        static Print* infoSerial; //Serial ou les donnees d'information sont transmises
        static Print* debugSerial; //Serial ou les donnees servant au debug sont transmises
        static bool infoOpened; //Canal info ouvert ?
        static bool debugOpened; //Canal debug info ?

};

#endif  // LOGGER_HPP