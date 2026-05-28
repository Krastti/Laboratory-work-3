#include "complex.h"

#include <stdexcept>

Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex(double real) : real(real), imag(0.0) {}

Complex::Complex(double real, double imag) : real(real), imag(imag) {}

double Complex::get_real() const {
  return real;
}

double Complex::get_imag() const {
  return imag;
}

void Complex::set_real(double value) {
  real = value;
}

void Complex::set_imag(double value) {
  imag = value;
}

Complex Complex::conjugate() const {
  return Complex(real, -imag);
}

Complex Complex::operator+() const {
  return *this;
}

Complex Complex::operator-() const {
  return Complex(-real, -imag);
}

Complex& Complex::operator+=(const Complex& other) {
  real += other.real;
  imag += other.imag;
  return *this;
}

Complex& Complex::operator-=(const Complex& other) {
  real -= other.real;
  imag -= other.imag;
  return *this;
}

Complex& Complex::operator*=(const Complex& other) {
  const double new_real = real * other.real - imag * other.imag;
  const double new_imag = real * other.imag + imag * other.real;

  real = new_real;
  imag = new_imag;
  return *this;
}

Complex& Complex::operator/=(const Complex& other) {
  const double denominator = other.real * other.real + other.imag * other.imag;
  if (denominator == 0.0) {
    throw std::invalid_argument("division by zero complex number");
  }

  const double new_real = (real * other.real + imag * other.imag) / denominator;
  const double new_imag = (imag * other.real - real * other.imag) / denominator;

  real = new_real;
  imag = new_imag;
  return *this;
}

Complex operator+(Complex left, const Complex& right) {
  left += right;
  return left;
}

Complex operator-(Complex left, const Complex& right) {
  left -= right;
  return left;
}

Complex operator*(Complex left, const Complex& right) {
  left *= right;
  return left;
}

Complex operator/(Complex left, const Complex& right) {
  left /= right;
  return left;
}

bool operator==(const Complex& left, const Complex& right) {
  return left.real == right.real && left.imag == right.imag;
}

bool operator!=(const Complex& left, const Complex& right) {
  return !(left == right);
}
