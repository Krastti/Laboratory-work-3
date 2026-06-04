#ifndef LABORATORYWORK3_QUATERNON_ROTATE_H
#define LABORATORYWORK3_QUATERNON_ROTATE_H

#include "Matrix/square_matrix.h"
#include "quaternion.h"

class QuaternionRotate {
public:
  /**
   * Создает единичный кватернион вращения по оси и углу в радианах.
   */
  static Quaternion from_axis_angle(double axis_x, double axis_y, double axis_z, double angle_radians);

  /**
   * Возвращает обратный кватернион.
   */
  static Quaternion inverse(const Quaternion& quaternion);

  /**
   * Вращает кватернион как трехмерный вектор.
   */
  static Quaternion rotate_vector(const Quaternion& vector, const Quaternion& rotation);

  /**
   * Вращает каждый элемент матрицы кватернионов.
   */
  static SquareMatrix<Quaternion> rotate_matrix(const SquareMatrix<Quaternion>& matrix, const Quaternion& rotation);
};

#endif // LABORATORYWORK3_QUATERNON_ROTATE_H
