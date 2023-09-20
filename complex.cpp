#include "complex.h"
#include <cmath>

Complex::Complex(double r, double im) : r(r), im(im) {}

double Complex::abs() const {
    return std::sqrt(r * r + im * im);
}

Complex Complex::operator+(const Complex& rhs) const {
    return Complex(r + rhs.r, im + rhs.im);
}

Complex Complex::operator-(const Complex& rhs) const {
    return Complex(r - rhs.r, im - rhs.im);
}

Complex Complex::operator*(double rhs) const {
    return Complex(r * rhs, im * rhs);
}
