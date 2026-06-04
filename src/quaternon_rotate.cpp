#include "quaternon_rotate.h"

#include "baseADT/array_sequence.h"

#include <cmath>
#include <stdexcept>

Quaternion QuaternionRotate::from_axis_angle(double axis_x, double axis_y, double axis_z, double angle_radians) {
  const double axis_length = std::sqrt(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
  if (axis_length == 0.0) {
    throw std::invalid_argument("Rotation axis cannot be zero");
  }

  const double half_angle = angle_radians / 2.0;
  const double sin_half = std::sin(half_angle);

  return Quaternion(
      std::cos(half_angle),
      axis_x / axis_length * sin_half,
      axis_y / axis_length * sin_half,
      axis_z / axis_length * sin_half
  );
}

Quaternion QuaternionRotate::inverse(const Quaternion& quaternion) {
  const double length_squared = quaternion.norm_squared();
  if (length_squared == 0.0) {
    throw std::invalid_argument("Zero quaternion has no inverse");
  }

  return quaternion.conjugate() * (1.0 / length_squared);
}

Quaternion QuaternionRotate::rotate_vector(const Quaternion& vector, const Quaternion& rotation) {
  const Quaternion normalized_rotation = rotation.normalize();
  if (normalized_rotation.norm_squared() == 0.0) {
    throw std::invalid_argument("Rotation quaternion cannot be zero");
  }

  return normalized_rotation * vector * normalized_rotation.conjugate();
}

SquareMatrix<Quaternion> QuaternionRotate::rotate_matrix(const SquareMatrix<Quaternion>& matrix, const Quaternion& rotation) {
  MutableArraySequence<Quaternion> items;

  for (int row = 0; row < matrix.get_size(); row++) {
    for (int column = 0; column < matrix.get_size(); column++) {
      items.append(rotate_vector(matrix.get(row, column), rotation));
    }
  }

  return SquareMatrix<Quaternion>(&items, matrix.get_size());
}
