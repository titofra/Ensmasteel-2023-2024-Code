#include "vector.hpp"

const float PI = 3.14159274101257324219;

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

Vector Vector::operator/(float scalaire){
    return Vector(x / scalaire, y / scalaire);
}

void Vector::operator+=(const Vector &other){
    x+=other.x;
    y+=other.y;
}

bool Vector::operator==(Vector const &other){
    return ((x - other.x) * (x - other.x) <= 1e-6) && ((y - other.y) * (y - other.y) <= 1e-6);
}

Vector& Vector::operator=(const Vector& other) {
    x = other.x;
    y = other.y;
    return *this;
}

float Vector::norm(){
    return std::sqrt(x * x + y * y);
}

float Vector::angle(){
    // as atan () return a value in (- PI/2, PI/2) we have to descrimine the cases
    if (x > 0) {
        return (float) std::atan ((double) y / x);
    } else {
        if (x < 0) {
            return normalizeAngle ((float) std::atan ((double) y / x) + PI);
        } else {    // both on the same y axis
            if (y > 0) {
                return PI / 2.0f;
            } else {
                if (y < 0) {
                    return - PI / 2.0f;
                } else {
                    return 0.0f;    // convention: origine point => theta = 0.0f
                }
            }
        }
    };
}

float Vector::distanceWith(Vector &other){
    return (float) std::sqrt( std::pow(x - other.x , 2) + std::pow(y - other.y , 2) );
}

float Vector::angleWith(const Vector &other) const {
    // as atan () return a value in (- PI/2, PI/2) we have to descrimine the cases
    if (other.x - x > 0) {
        return (float) std::atan ((double) (other.y - y) / (other.x - x));
    } else {
        if (other.x - x < 0) {
            return normalizeAngle ((float) std::atan ((double) (other.y - y) / (other.x - x)) + PI);
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


float Vector::getX() const{
    return x;
}

float Vector::getY() const{
    return y;
}

void Vector::setX(float value){
    x = value;
}

void Vector::setY(float value){
    y = value;
}

/*
void Vector::printDebug(const char *prefix, Stream *serial) const {
    char buf [8];   // 6 digits, take care of '.' and '\0'!

    serial->print(prefix);

    serial->print(" x ");
    dtostrf (x, 1, 3, buf);
    serial->print(buf);

    serial->print("   y ");
    dtostrf (y, 1, 3, buf);
    serial->println(buf);
}
*/

void Vector::printDebug(const char *prefix) const {
    std::cout << prefix << " x " << x << "   y " << y << std::endl;
}