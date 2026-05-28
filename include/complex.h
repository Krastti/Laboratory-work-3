#ifndef LABORATORYWORK3_COMPLEX_H
#define LABORATORYWORK3_COMPLEX_H

class Complex {
private:
  double real;
  double imag;

public:
  Complex();
  Complex(double real);
  Complex(double real, double imag);

  double get_real() const;
  double get_imag() const;

  void set_real(double value);
  void set_imag(double value);

  Complex conjugate() const;

  Complex operator+() const;
  Complex operator-() const;

  Complex& operator+=(const Complex& other);
  Complex& operator-=(const Complex& other);
  Complex& operator*=(const Complex& other);
  Complex& operator/=(const Complex& other);

  friend bool operator==(const Complex& left, const Complex& right);
};

Complex operator+(Complex left, const Complex& right);
Complex operator-(Complex left, const Complex& right);
Complex operator*(Complex left, const Complex& right);
Complex operator/(Complex left, const Complex& right);
bool operator==(const Complex& left, const Complex& right);
bool operator!=(const Complex& left, const Complex& right);

#endif // LABORATORYWORK3_COMPLEX_H
