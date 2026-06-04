#ifndef LABORATORYWORK3_SOLVER_INTERFACE_H
#define LABORATORYWORK3_SOLVER_INTERFACE_H

#include "../Matrix/square_matrix.h"
#include "../vector.h"

class SolverInterface {
private:
  /**
   * Показывает главное меню.
   */
  static void print_menu();

  /**
   * Запускает сценарий ручного ввода и решения системы.
   */
  static void solve_manual_system();

  /**
   * Запускает сценарий генерации случайной СЛАУ с известным точным решением.
   */
  static void solve_random_system();

  /**
   * Считывает квадратную матрицу коэффициентов.
   */
  static SquareMatrix<double> read_matrix(int size);

  /**
   * Считывает вектор свободных членов.
   */
  static Vector<double> read_vector(int size);

  /**
   * Выбирает солвер и решает систему.
   */
  static Vector<double> solve_system(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms, int solver_type);

  /**
   * Считывает целое число из консоли.
   */
  static int read_int(const char* prompt);

  /**
   * Считывает вещественное число из консоли.
   */
  static double read_double(const char* prompt);

  /**
   * Очищает некорректный ввод.
   */
  static void clear_input();

public:
  /**
   * Запускает простое консольное окно для ввода СЛАУ и выбора солвера.
   */
  static void run();
};

#endif // LABORATORYWORK3_SOLVER_INTERFACE_H
