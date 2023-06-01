#include "kinetic.hpp"

Kinetic::Kinetic (float x, float y, float theta, float v, float w) :
    VectorOriented(x, y, theta),
    v (v),
    w (w) {
}

Kinetic::Kinetic (const Kinetic& kinetic) :
    VectorOriented (kinetic.getX (), kinetic.getY (), kinetic.getTheta ())
{
    v = kinetic.getTranslationSpeed ();
    w = kinetic.getTranslationSpeed ();
}

Kinetic& Kinetic::operator=(const Kinetic& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        theta = other.theta;
        v = other.v;
        w = other.w;
    }
    return *this;
}

bool Kinetic::operator== (Kinetic const &other){
    return VectorOriented::operator== (other) && abs(v-other.v) < 1e-6 && abs(w-other.w) < 1e-6;
}

Kinetic Kinetic::operator-(Kinetic const &other){
    VectorOriented vect = VectorOriented::operator- (other);
    return Kinetic (vect.getX (),vect.getY (), vect.getTheta (), v - other.v, w - other.w); 
}

Kinetic Kinetic::operator+(Kinetic const &other){
    VectorOriented vect = VectorOriented::operator- (other);
    return Kinetic (vect.getX (),vect.getY (), vect.getTheta (), v + other.v, w + other.w); 
}

Kinetic Kinetic::operator/(float const &other){
    VectorOriented vect = VectorOriented::operator/ (other);
    return Kinetic (vect.getX (),vect.getY (), vect.getTheta (), v / other, w / other); 
}

Kinetic Kinetic::operator*(float const &other){
    VectorOriented vect = VectorOriented::operator* (other);
    return Kinetic (vect.getX (),vect.getY (), vect.getTheta (), v * other, w * other); 
}

float Kinetic::getTranslationSpeed () const {
    return v;
}

void Kinetic::setTranslationSpeed (float value) {
    v = value;
}

float Kinetic::getRotationSpeed ()const {
    return w;
}

void Kinetic::setRotationSpeed(float value) {
    w = value;
}

/*
void Kinetic::printDebug(const char *prefix, Stream *serial) const {
    char buf [8];   // 6 digits, take care of '.' and '\0'!

    serial->print(prefix);

    serial->print(" x ");
    dtostrf (getX (), 1, 3, buf);
    serial->print(buf);

    serial->print("   y ");
    dtostrf (getY (), 1, 3, buf);
    serial->print(buf);

    serial->print("   theta ");
    dtostrf (getTheta (), 1, 3, buf);
    serial->print(buf);

    serial->print("   v ");
    dtostrf (v, 1, 3, buf);
    serial->print(buf);

    serial->print("   w ");
    dtostrf (w, 1, 3, buf);
    serial->println(buf);
}
*/

void Kinetic::printDebug(const char *prefix) const {
    std::cout << prefix << " x " << getX () << "   y " << getY () << "   theta " << getTheta () << "   v " << v << "   w " << w << std::endl;
}