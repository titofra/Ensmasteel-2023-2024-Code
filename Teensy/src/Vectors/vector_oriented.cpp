#include <Vectors/vector_oriented.hpp>

float normalizeAngle(float angle) {
    float out;
    out = angle - (2 * PI) * ((int)(angle / (2 * PI)));
    if (out > PI)
        return (out - 2 * PI);
    else if (out <= -PI)
        return (out + 2 * PI);

    return out;
}

VectorOriented::VectorOriented(float x, float y,float theta) :
    Vector (x,y),
    theta (theta) {
}

bool VectorOriented::operator==(VectorOriented const &other){
    return Vector::operator==(other) && abs(theta - other.theta) <= 1e-6;
}

VectorOriented VectorOriented::operator-(VectorOriented const &other){
    Vector vect = Vector::operator- (other);
    return VectorOriented(vect.getX(),vect.getY(), theta - other.theta); 
}

float VectorOriented::getTheta(){
    return theta;
}

void VectorOriented::setTheta(float theta) :
    theta (theta) {
}

void VectorOriented::normalizeTheta() {
    theta = normalizeAngle (theta);
}

void VectorOriented::printDebug(const String& prefix) {
    Serial.println(">" + prefix+" x :" + String(getX(),3));
    Serial.println(">" + prefix+" y :" + String(getY(), 3));
    Serial.println(">" + prefix+" Th :" + String(getTheta(), 3));
    Serial.println(">" + prefix + " xy :" + String(getX(),3) + ":" + String(getY(),3) + "|xy");
}