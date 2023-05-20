#include <odometry.hpp>

Odometry::Odometry(Codeuse *codeuseLeft, Codeuse *codeuseRight, float codeusesSpacing):
    codeuseLeft (codeuseLeft),
    codeuseRight (codeuseRight),
    codeusesSpacing (codeusesSpacing) {
}

void Odometry::updateOdometry(float dt, Kinetic *kinetics){
    codeuseLeft->actuate(dt);
    codeuseRight->actuate(dt);

    float translationSpeedCodeuses = (codeuseLeft->getTranslationSpeedCodeuse() + codeuseRight->getTranslationSpeedCodeuse()) / 2;
    float rotationSpeedCodeuses = (codeuseRight->getTranslationSpeedCodeuse() - codeuseLeft->getTranslationSpeedCodeuse()) / this->codeusesSpacing;
    float thetaCodeuses = (codeuseRight->getDeltaAvance() - codeuseLeft->getDeltaAvance()) / this->codeusesSpacing; 
    
    kinetics->setTranslationSpeed(translationSpeedCodeuses);
    kinetics->setRotationSpeed(rotationSpeedCodeuses);
    kinetics->setTheta(thetaCodeuses+kinetics->getTheta());
    kinetics->normalizeTheta();
    
    float moyenneAvanceCodeuses = (codeuseRight->getDeltaAvance() + codeuseLeft->getDeltaAvance()) / 2;
    
    kinetics->setX( kinetics->getX() + moyenneAvanceCodeuses*(cos(kinetics->getTheta())));
    kinetics->setY( kinetics->getY() + moyenneAvanceCodeuses*(sin(kinetics->getTheta())));
}


