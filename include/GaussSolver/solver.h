#ifndef LABORATORYWORK3_GAUSS_SOLVER_H
#define LABORATORYWORK3_GAUSS_SOLVER_H

#include "../Matrix/matrix.h"
#include "../Matrix/square_matrix.h"
#include "../vector.h"

class Solver {
private:
  /**
   * Проверяет, что матрица является квадратной.
   */
  static void check_square_matrix(const Matrix<double>& matrix);

  /**
   * Проверяет, что матрица коэффициентов и вектор свободных членов задают корректную систему.
   */
  static void check_system(const Matrix<double>& coefficients, const Vector<double>& free_terms);

  /**
   * Проверяет, что для переданного решения можно вычислить невязку системы.
   */
  static void check_solution_system(const Matrix<double>& coefficients, const Vector<double>& free_terms, const Vector<double>& solution);

  /**
   * Приводит систему к верхнетреугольному виду без выбора ведущей строки.
   */
  static void forward_classic(SquareMatrix<double>& coefficients, Vector<double>& free_terms);

  /**
   * Приводит систему к верхнетреугольному виду с выбором ведущей строки.
   */
  static void forward_with_pivot(SquareMatrix<double>& coefficients, Vector<double>& free_terms);

public:
  /**
   * Описывает способ решения системы методом Гаусса.
   */
  enum class Method {
    Classic,
    Pivot
  };

  /**
   * Минимальное значение, которое считается ненулевым ведущим элементом.
   */
  static constexpr double EPSILON = 1e-16;

  /**
   * Решает систему линейных уравнений выбранным вариантом метода Гаусса.
   * Исходные матрица и вектор не изменяются.
   */
  static Vector<double> solve(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms, Method method = Method::Pivot);

  /**
   * Решает систему линейных уравнений классическим методом Гаусса без выбора ведущей строки.
   */
  static Vector<double> solve_classic(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms);

  /**
   * Решает систему линейных уравнений методом Гаусса с выбором ведущей строки.
   */
  static Vector<double> solve_with_pivot(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms);

  /**
   * Решает систему с нижнетреугольной матрицей методом прямой подстановки.
   */
  static Vector<double> forward_substitution(const Matrix<double>& lower, const Vector<double>& free_terms);

  /**
   * Решает систему с верхнетреугольной матрицей методом обратной подстановки.
   */
  static Vector<double> back_substitution(const Matrix<double>& upper, const Vector<double>& free_terms);

  /**
   * Вычисляет евклидову норму невязки для найденного решения системы.
   */
  static double residual(const Matrix<double>& coefficients, const Vector<double>& free_terms, const Vector<double>& solution);
};

#endif // LABORATORYWORK3_GAUSS_SOLVER_H
