#include <iostream>

#include "include/Matrix/matrix_io.h"
#include "include/GaussSolver/lu_solver.h"
#include "include/GaussSolver/matgen.h"
#include "include/GaussSolver/solver.h"
#include "include/quaternion.h"
#include "include/quaternion_io.h"
#include "include/Matrix/rectangular_matrix.h"
#include "include/Matrix/square_matrix.h"
#include "include/vector_io.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  Quaternion first_items[] = {
      Quaternion(1.0, 0.0, 1.0, 0.0),
      Quaternion(2.0, 1.0, 0.0, 0.0),
      Quaternion(0.0, 1.0, 0.0, 1.0),
      Quaternion(3.0, 0.0, 0.0, 1.0)
  };

  Quaternion second_items[] = {
      Quaternion::identity(),
      Quaternion(0.0, 1.0, 0.0, 0.0),
      Quaternion(0.0, 0.0, 1.0, 0.0),
      Quaternion(0.0, 0.0, 0.0, 1.0)
  };

  SquareMatrix<Quaternion> first_matrix(first_items, 2);
  SquareMatrix<Quaternion> second_matrix(second_items, 2);

  SquareMatrix<Quaternion> sum = first_matrix + second_matrix;
  SquareMatrix<Quaternion> scaled = first_matrix * Quaternion(2.0, 0.0, 0.0, 0.0);

  std::cout << "Первая матрица кватернионов:\n" << first_matrix << '\n';
  std::cout << "Вторая матрица кватернионов:\n" << second_matrix << '\n';
  std::cout << "Сумма матриц:\n" << sum << '\n';
  std::cout << "Умножаем первую матрицу на скаляр (2, 0, 0, 0):\n" << scaled << '\n';
  std::cout << "Норма первой матрицы: " << first_matrix.norm() << "\n\n";

  RectangularMatrix<Quaternion> rectangular(first_items, 2, 2);
  rectangular.swap_rows(0, 1);
  rectangular.scale_column(0, Quaternion::identity());

  std::cout << "Прямоугольная матрица после перемещения строк:\n" << rectangular << '\n';

  double system_items[] = {
      2.0, 1.0, -1.0,
      -3.0, -1.0, 2.0,
      -2.0, 1.0, 2.0
  };
  double free_items[] = {8.0, -11.0, -3.0};

  SquareMatrix<double> system_matrix(system_items, 3);
  Vector<double> free_terms(free_items, 3);
  Vector<double> gauss_solution = Solver::solve_with_pivot(system_matrix, free_terms);
  Vector<double> lu_solution = LUSolver::decompose_and_solve(system_matrix, free_terms);
  LUDecomposition decomposition = LUSolver::decompose(system_matrix);

  std::cout << "Пример решения СЛАУ методом Гаусса и LU:\n";
  std::cout << "Матрица коэффициентов:\n" << system_matrix;
  std::cout << "Вектор свободных членов: " << free_terms << '\n';
  std::cout << "Решение методом Гаусса: " << gauss_solution << '\n';
  std::cout << "Решение через LU: " << lu_solution << '\n';
  std::cout << "Невязка LU-решения: " << Solver::residual(system_matrix, free_terms, lu_solution) << "\n\n";
  std::cout << "Матрица L:\n" << decomposition.lower;
  std::cout << "Матрица U:\n" << decomposition.upper << '\n';

  Vector<double> exact_solution = Matgen::random_vector(3, 1.0, 3.0, 42u);
  SquareMatrix<double> hilbert_matrix = Matgen::hilbert_matrix(3);
  Vector<double> hilbert_free_terms = Matgen::rhs_from_exact(hilbert_matrix, exact_solution);
  Vector<double> hilbert_lu_solution = LUSolver::decompose_and_solve(hilbert_matrix, hilbert_free_terms);

  std::cout << "Пример LU для матрицы Гильберта:\n";
  std::cout << "Матрица Гильберта:\n" << hilbert_matrix;
  std::cout << "Точное решение: " << exact_solution << '\n';
  std::cout << "Вектор свободных членов: " << hilbert_free_terms << '\n';
  std::cout << "LU-решение: " << hilbert_lu_solution << '\n';
  std::cout << "Относительная ошибка: " << Matgen::relative_error(hilbert_lu_solution, exact_solution) << '\n';

  return 0;
}
