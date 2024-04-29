#include "vector_oriented.hpp"

const double PI = 3.14159274101257324219;

VectorOriented::VectorOriented(double xValue, double yValue, double thetaValue)
    : Vector(xValue, yValue), theta(thetaValue) {}

VectorOriented::VectorOriented(const VectorOriented& other)
    : Vector(other), theta(other.theta) {}

double VectorOriented::getTheta() const {
    return theta;
}

void VectorOriented::setTheta(double thetaValue) {
    theta = thetaValue;
}

VectorOriented VectorOriented::perpendicular() const {
    return VectorOriented(x, y, normalizeAngle (theta + PI / 2.0));
}

VectorOriented& VectorOriented::operator=(const VectorOriented& other) {
    if (this != &other) {
        Vector::operator=(other);
        theta = other.theta;
    }
    return *this;
}

VectorOriented VectorOriented::operator+(const VectorOriented& other) const {
    return VectorOriented(x + other.x, y + other.y, normalizeAngle (theta + other.theta));
}

VectorOriented VectorOriented::operator-(const VectorOriented& other) const {
    return VectorOriented(x - other.x, y - other.y, normalizeAngle (theta - other.theta));
}

VectorOriented VectorOriented::operator*(double scalar) const {
    return VectorOriented(x * scalar, y * scalar, normalizeAngle (theta * scalar));
}

VectorOriented VectorOriented::operator/(double scalar) const {
    return VectorOriented(x / scalar, y / scalar, normalizeAngle (theta / scalar));
}

VectorOriented& VectorOriented::operator+=(const VectorOriented& other) {
    x += other.x;
    y += other.y;
    theta += other.theta;
    return *this;
}

VectorOriented& VectorOriented::operator-=(const VectorOriented& other) {
    x -= other.x;
    y -= other.y;
    theta -= other.theta;
    return *this;
}

VectorOriented& VectorOriented::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    theta *= scalar;
    return *this;
}

VectorOriented& VectorOriented::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    theta /= scalar;
    return *this;
}

bool VectorOriented::operator==(const VectorOriented& other) const {
    return (x == other.x) && (y == other.y) && (theta == other.theta);
}

bool VectorOriented::operator!=(const VectorOriented& other) const {
    return !(*this == other);
}

void VectorOriented::normalizeTheta() {
    theta = normalizeAngle (theta);
}

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