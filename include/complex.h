#ifndef LABORATORYWORK3_COMPLEX_H
#define LABORATORYWORK3_COMPLEX_H

#include <ostream>
#include <stdexcept>

class Complex {
private:
  double real;
  double imag;

public:
  Complex() : real(0.0), imag(0.0) {}

  Complex(double real) : real(real), imag(0.0) {}

  Complex(double real, double imag) : real(real), imag(imag) {}

  double get_real() const {
    return real;
  }

  double get_imag() const {
    return imag;
  }

  void set_real(double value) {
    real = value;
  }

  void set_imag(double value) {
    imag = value;
  }

  Complex conjugate() const {
    return Complex(real, -imag);
  }

  Complex operator+() const {
    return *this;
  }

  Complex operator-() const {
    return Complex(-real, -imag);
  }

  Complex& operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
  }

  Complex& operator-=(const Complex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
  }

  Complex& operator*=(const Complex& other) {
    const double new_real = real * other.real - imag * other.imag;
    const double new_imag = real * other.imag + imag * other.real;

    real = new_real;
    imag = new_imag;
    return *this;
  }

  Complex& operator/=(const Complex& other) {
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

  friend Complex operator+(Complex left, const Complex& right) {
    left += right;
    return left;
  }

  friend Complex operator-(Complex left, const Complex& right) {
    left -= right;
    return left;
  }

  friend Complex operator*(Complex left, const Complex& right) {
    left *= right;
    return left;
  }

  friend Complex operator/(Complex left, const Complex& right) {
    left /= right;
    return left;
  }

  friend bool operator==(const Complex& left, const Complex& right) {
    return left.real == right.real && left.imag == right.imag;
  }

  friend bool operator!=(const Complex& left, const Complex& right) {
    return !(left == right);
  }

  friend std::ostream& operator<<(std::ostream& out, const Complex& value) {
    out << value.real;
    if (value.imag < 0.0) {
      out << " - " << -value.imag << 'i';
    } else {
      out << " + " << value.imag << 'i';
    }

    return out;
  }
};

#endif // LABORATORYWORK3_COMPLEX_H
