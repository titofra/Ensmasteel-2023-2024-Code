#include "vector.hpp"

float normalizeAngle(float angle) {
    float out;
    out = angle - (2 * PI) * ((int)(angle / (2 * PI)));
    if (out > PI)
        return (out - 2 * PI);
    else if (out <= -PI)
        return (out + 2 * PI);

    return out;
}

Vector::Vector(float x, float y) :
    x (x),
    y (y) {
}

Vector::Vector (const Vector& vect) {
    x = vect.getX ();
    y = vect.getY ();
}


Vector Vector::operator+(const Vector &other){
    return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector &other){
    return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(float scalaire){
    return Vector(x * scalaire, y * scalaire);
}

void Vector::operator+=(const Vector &other){
    x+=other.x;
    y+=other.y;
}

bool Vector::operator==(Vector const &other){
    return (abs(x - other.x) <= 1e-6) && (abs(y - other.y) <= 1e-6);
}

float Vector::norm(){
    return sqrt(x * x + y * y);
}

float Vector::angle(){
    return atan2(y,x);
}

float Vector::distanceWith(Vector &other){
    return sqrt( pow(x - other.x , 2) + pow(y - other.y , 2) );
}

float Vector::angleWith(Vector &other) {
    // as atan2 () return a value in (- PI/2, PI/2) we have to descrimine the cases
    if (other.x - x > 0) {
        return atan2 ((other.y - y) / (other.x - x));
    } else {
        if (other.x - x < 0) {
            return normalizeAngle (atan2 ((other.y - y) / (other.x - x)) + PI);
        } else {    // both on the same y axis
            if (other.y - y > 0) {
                return PI / 2.0f;
            } else {
                if (other.y - y < 0) {
                    return - PI / 2.0f;
                } else {
                    return 0.0f;    // convention: same point => theta = 0.0f
                }
            }
        }
    }
}


float Vector::getX(){
    return x;
}

float Vector::getY(){
    return y;
}

void Vector::setX(float x){
    x=x;
}

void Vector::setY(float y){
    y=y;
}

void Vector::printDebug(const String& prefix)
{
    Serial.println(">" + prefix + " x :" + String(getX(),3));
    Serial.println(">" + prefix + " y :" + String(getY(), 3));
    Serial.println(">" + prefix + " xy :" + String(getX(),3) + ":" + String(getY(),3) + "|xy");
}