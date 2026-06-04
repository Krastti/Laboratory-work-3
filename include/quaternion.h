#ifndef LABORATORYWORK3_QUATERNION_H
#define LABORATORYWORK3_QUATERNION_H

class Quaternion {
private:
  double w;
  double x;
  double y;
  double z;

public:
  Quaternion();
  Quaternion(double w, double x, double y, double z);

  static Quaternion zero();
  static Quaternion identity();

  double get_w() const;
  double get_x() const;
  double get_y() const;
  double get_z() const;

  void set_w(double value);
  void set_x(double value);
  void set_y(double value);
  void set_z(double value);

  Quaternion conjugate() const;
  double norm_squared() const;
  double norm() const;
  Quaternion normalize() const;

  Quaternion operator+() const;
  Quaternion operator-() const;

  Quaternion& operator+=(const Quaternion& other);
  Quaternion& operator-=(const Quaternion& other);
  Quaternion& operator*=(const Quaternion& other);
  Quaternion& operator*=(double scalar);

  friend bool operator==(const Quaternion& left, const Quaternion& right);
};

Quaternion operator+(Quaternion left, const Quaternion& right);
Quaternion operator-(Quaternion left, const Quaternion& right);
Quaternion operator*(Quaternion left, const Quaternion& right);
Quaternion operator*(Quaternion quaternion, double scalar);
Quaternion operator*(double scalar, Quaternion quaternion);
bool operator==(const Quaternion& left, const Quaternion& right);
bool operator!=(const Quaternion& left, const Quaternion& right);

#endif // LABORATORYWORK3_QUATERNION_H
