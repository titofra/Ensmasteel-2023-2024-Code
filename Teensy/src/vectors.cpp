#include <vectors.h>

//----------Vector Class----------//

Vector::Vector(float x, float y) :
    x (x),
    y (y) {
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

//----------End Vector Class----------//




//----------Vector Oriented Class----------//

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

//----------End Vector Oriented Class----------//