#include <iostream>
#include <cmath>

using namespace std;

class Complex {
public:
    Complex(double r = 0.0, double im = 0.0);
    double abs() const;
    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(double rhs) const;

private:
    double r;
    double im;
};
