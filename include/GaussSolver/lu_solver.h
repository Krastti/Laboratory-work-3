#ifndef LABORATORYWORK3_LU_SOLVER_H
#define LABORATORYWORK3_LU_SOLVER_H

#include "../Matrix/rectangular_matrix.h"
#include "../Matrix/square_matrix.h"
#include "../vector.h"

struct LUDecomposition {
  RectangularMatrix<double> lower;
  RectangularMatrix<double> upper;
};

class LUSolver {
private:
  /**
   * Проверяет, что матрица является квадратной.
   */
  static void check_square_matrix(const SquareMatrix<double>& matrix);

  /**
   * Проверяет совместимость матриц L, U и вектора свободных членов.
   */
  static void check_lu_system(const RectangularMatrix<double>& lower, const RectangularMatrix<double>& upper, const Vector<double>& free_terms);

public:
  /**
   * Минимальное значение, которое считается ненулевым диагональным элементом.
   */
  static constexpr double EPSILON = 1e-16;

  /**
   * Строит LU-разложение квадратной матрицы без выбора ведущего элемента.
   */
  static LUDecomposition decompose(const SquareMatrix<double>& coefficients);

  /**
   * Решает систему по уже построенным матрицам L и U.
   */
  static Vector<double> solve(const RectangularMatrix<double>& lower, const RectangularMatrix<double>& upper, const Vector<double>& free_terms);

  /**
   * Строит LU-разложение и сразу решает систему линейных уравнений.
   */
  static Vector<double> decompose_and_solve(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms);
};

#endif // LABORATORYWORK3_LU_SOLVER_H
