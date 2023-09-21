#include "vector.hpp"

const double PI = 3.14159274101257324219;

double normalizeAngle(double angle) {
    double out;
    out = angle - (2 * PI) * ((int)(angle / (2 * PI)));
    if (out > PI)
        return (out - 2 * PI);
    else if (out <= -PI)
        return (out + 2 * PI);

    return out;
}

Vector::Vector(double xValue, double yValue) : x(xValue), y(yValue) {}

Vector::Vector(const Vector& other) : x(other.x), y(other.y) {};


// Getter methods
double Vector::getX() const {
    return x;
}

double Vector::getY() const {
    return y;
}

// Setter methods
void Vector::setX(double xValue) {
    x = xValue;
}

void Vector::setY(double yValue) {
    y = yValue;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

// Vector operations
Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(double scalar) const {
    return Vector(x * scalar, y * scalar);
}

Vector Vector::operator/(double scalar) const {
    return Vector(x / scalar, y / scalar);
}

Vector& Vector::operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector& Vector::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector& Vector::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

// Comparison operators
bool Vector::operator==(const Vector& other) const {
    return x == other.x && y == other.y;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

bool Vector::operator<(const Vector& other) const {
    return norm() < other.norm();
}

bool Vector::operator>(const Vector& other) const {
    return norm() > other.norm();
}

bool Vector::operator<=(const Vector& other) const {
    return norm() <= other.norm();
}

bool Vector::operator>=(const Vector& other) const {
    return norm() >= other.norm();
}

double Vector::dotProduct(const Vector& other) const {
    return x * other.x + y * other.y;
}

double Vector::norm() const {
    return std::sqrt(x * x + y * y);
}

double Vector::angle() const {
    // as atan () return a value in (- PI/2, PI/2) we have to descrimine the cases
    if (x > 0) {
        return (double) std::atan ((double) y / x);
    } else {
        if (x < 0) {
            return normalizeAngle ((double) std::atan ((double) y / x) + PI);
        } else {    // both on the same y axis
            if (y > 0) {
                return PI / 2.0;
            } else {
                if (y < 0) {
                    return - PI / 2.0;
                } else {
                    return 0.0;    // convention: origine point => theta = 0.0f
                }
            }
        }
    };
}

// Additional methods
void Vector::normalize() {
    double mag = norm();
    if (mag != 0.0) {
        x /= mag;
        y /= mag;
    }
}

Vector Vector::perpendicular() const {
    return Vector(-y, x);
}

double Vector::distanceWith(Vector &other) const {
    return (double) std::sqrt( std::pow(x - other.x , 2) + std::pow(y - other.y , 2));
}

double Vector::angleWith(const Vector &other) const {
    // as atan () return a value in (- PI/2, PI/2) we have to descrimine the cases
    if (other.x - x > 0) {
        return (double) std::atan ((other.y - y) / (other.x - x));
    } else {
        if (other.x - x < 0) {
            return normalizeAngle ((double) std::atan ((other.y - y) / (other.x - x)) + PI);
        } else {    // both on the same y axis
            if (other.y - y > 0) {
                return PI / 2.0;
            } else {
                if (other.y - y < 0) {
                    return - PI / 2.0;
                } else {
                    return 0.0;    // convention: same point => theta = 0.0f
                }
            }
        }
    }
    return 18.0;
}

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