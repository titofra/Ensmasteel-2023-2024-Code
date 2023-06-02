#include "vector_oriented.hpp"

VectorOriented::VectorOriented(float x, float y,float th) :
    Vector (x, y)
{
    theta = th;
}

VectorOriented::VectorOriented (const VectorOriented& vo) :
    Vector (vo.getX (), vo.getY ())
{
    theta = vo.getTheta ();
}

bool VectorOriented::operator==(VectorOriented const &other){
    return Vector::operator==(other) && abs(theta - other.theta) <= 1e-6;
}

VectorOriented VectorOriented::operator-(VectorOriented const &other){
    Vector vect = Vector::operator- (other);
    return VectorOriented(vect.getX(),vect.getY(), theta - other.theta); 
}

VectorOriented VectorOriented::operator+(VectorOriented const &other){
    Vector vect = Vector::operator+ (other);
    return VectorOriented(vect.getX(),vect.getY(), theta + other.theta); 
}

VectorOriented& VectorOriented::operator=(const VectorOriented& other) {
    x = other.x;
    y = other.y;
    theta = other.theta;
    return *this;
}

void VectorOriented::operator+=(const VectorOriented &other){
    Vector::operator+= (other);
    theta += other.getTheta ();
}

VectorOriented VectorOriented::operator/(float const &other){
    Vector vect = Vector::operator/ (other);
    return VectorOriented(vect.getX(),vect.getY(), theta / other); 
}

VectorOriented VectorOriented::operator*(float const &other){
    Vector vect = Vector::operator* (other);
    return VectorOriented(vect.getX(),vect.getY(), theta * other); 
}

float VectorOriented::getTheta() const {
    return theta;
}

void VectorOriented::setTheta(float value) {
    theta = value;
}

void VectorOriented::normalizeTheta() {
    theta = normalizeAngle (theta);
}

/*
void VectorOriented::printDebug(const char *prefix, Stream *serial) const {
    char buf [8];   // 6 digits, take care of '.' and '\0'!

    serial->print(prefix);

    serial->print(" x ");
    dtostrf (getX (), 1, 3, buf);
    serial->print(buf);

    serial->print("   y ");
    dtostrf (getY (), 1, 3, buf);
    serial->print(buf);

    serial->print("   theta ");
    dtostrf (theta, 1, 3, buf);
    serial->println(buf);
}
*/

void VectorOriented::printDebug(const char *prefix) const {
    std::cout << prefix << " x " << getX () << "   y " << getY () << "   theta " << theta << std::endl;
}