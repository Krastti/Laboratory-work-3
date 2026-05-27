#include "quaternion.h"

#include <cmath>

Quaternion::Quaternion() : w(0.0), x(0.0), y(0.0), z(0.0) {}

Quaternion::Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}

Quaternion Quaternion::zero() {
  return Quaternion();
}

Quaternion Quaternion::identity() {
  return Quaternion(1.0, 0.0, 0.0, 0.0);
}

double Quaternion::get_w() const {
  return w;
}

double Quaternion::get_x() const {
  return x;
}

double Quaternion::get_y() const {
  return y;
}

double Quaternion::get_z() const {
  return z;
}

void Quaternion::set_w(double value) {
  w = value;
}

void Quaternion::set_x(double value) {
  x = value;
}

void Quaternion::set_y(double value) {
  y = value;
}

void Quaternion::set_z(double value) {
  z = value;
}

Quaternion Quaternion::conjugate() const {
  return Quaternion(w, -x, -y, -z);
}

double Quaternion::norm_squared() const {
  return w * w + x * x + y * y + z * z;
}

double Quaternion::norm() const {
  return std::sqrt(norm_squared());
}

Quaternion Quaternion::inverse() const {
  const double denominator = norm_squared();
  if (denominator == 0.0) {
    return zero();
  }

  return conjugate() * (1.0 / denominator);
}

Quaternion Quaternion::normalize() const {
  const double length = norm();
  if (length == 0.0) {
    return zero();
  }

  return *this * (1.0 / length);
}

Quaternion Quaternion::operator+() const {
  return *this;
}

Quaternion Quaternion::operator-() const {
  return Quaternion(-w, -x, -y, -z);
}

Quaternion& Quaternion::operator+=(const Quaternion& other) {
  w += other.w;
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other) {
  w -= other.w;
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& other) {
  const double new_w = w * other.w - x * other.x - y * other.y - z * other.z;
  const double new_x = w * other.x + x * other.w + y * other.z - z * other.y;
  const double new_y = w * other.y - x * other.z + y * other.w + z * other.x;
  const double new_z = w * other.z + x * other.y - y * other.x + z * other.w;

  w = new_w;
  x = new_x;
  y = new_y;
  z = new_z;
  return *this;
}

Quaternion& Quaternion::operator*=(double scalar) {
  w *= scalar;
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Quaternion operator+(Quaternion left, const Quaternion& right) {
  left += right;
  return left;
}

Quaternion operator-(Quaternion left, const Quaternion& right) {
  left -= right;
  return left;
}

Quaternion operator*(Quaternion left, const Quaternion& right) {
  left *= right;
  return left;
}

Quaternion operator*(Quaternion quaternion, double scalar) {
  quaternion *= scalar;
  return quaternion;
}

Quaternion operator*(double scalar, Quaternion quaternion) {
  quaternion *= scalar;
  return quaternion;
}

bool operator==(const Quaternion& left, const Quaternion& right) {
  return left.w == right.w && left.x == right.x && left.y == right.y && left.z == right.z;
}

bool operator!=(const Quaternion& left, const Quaternion& right) {
  return !(left == right);
}
