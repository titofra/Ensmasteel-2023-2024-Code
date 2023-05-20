#include <kinetic.hpp>

//----------Kinetic Class----------//

Kinetic::Kinetic(float x, float y, float th, float v, float w):VectorOriented(x,y,th){
    this->v=v;
    this->w=w;
}

bool Kinetic::operator==(Kinetic const &other){
    return VectorOriented::operator==(other) && abs(v-other.v)<1e-6 && abs(w-other.w)<1e-6;
}

float Kinetic::getTranslationSpeed(){
    return v;
}

void Kinetic::setTranslationSpeed(float ts){
    v=ts;
}

float Kinetic::getRotationSpeed(){
    return w;
}

void Kinetic::setRotationSpeed(float rs){
    w=rs;
}

void Kinetic::printDebug(const String& prefix)
{
    Serial.println(">" + prefix+" x :" + String(getX(),3));
    Serial.println(">" + prefix+" y :" + String(getY(), 3));
    Serial.println(">" + prefix + " xy :" + String(getX(),3) + ":" + String(getY(),3) + "|xy");
    Serial.println(">" + prefix+" Th :" + String(getTheta(), 3));
    Serial.println(">" + prefix+" v :" + String(getTranslationSpeed(), 3));
    Serial.println(">" + prefix+" w :" + String(getRotationSpeed(), 3));
}



//----------End Kinetic Class----------//