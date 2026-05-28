#ifndef LABORATORYWORK3_GAUSS_MATGEN_H
#define LABORATORYWORK3_GAUSS_MATGEN_H

#include "../Matrix/square_matrix.h"
#include "../vector.h"

class Matgen {
private:
  /**
   * Генерирует псевдослучайное число от нуля до единицы.
   */
  static double random_0_1(unsigned int& seed);

  /**
   * Проверяет корректность размера для создаваемой матрицы или вектора.
   */
  static void check_size(int size);

  /**
   * Проверяет корректность диапазона случайных значений.
   */
  static void check_range(double low, double high);

public:
  /**
   * Создает квадратную матрицу со случайными значениями из заданного диапазона.
   */
  static SquareMatrix<double> random_matrix(int size, double low, double high, unsigned int seed);

  /**
   * Создает вектор со случайными значениями из заданного диапазона.
   */
  static Vector<double> random_vector(int size, double low, double high, unsigned int seed);

  /**
   * Создает матрицу Гильберта заданного размера.
   */
  static SquareMatrix<double> hilbert_matrix(int size);

  /**
   * Создает вектор свободных членов по матрице и известному точному решению.
   */
  static Vector<double> rhs_from_exact(const SquareMatrix<double>& coefficients, const Vector<double>& exact_solution);

  /**
   * Вычисляет относительную ошибку между приближенным и точным решениями.
   */
  static double relative_error(const Vector<double>& approximate_solution, const Vector<double>& exact_solution);
};

#endif // LABORATORYWORK3_GAUSS_MATGEN_H
