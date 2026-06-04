#include <cmath>
#include <iostream>
#include <limits>

#include "include/Matrix/matrix_io.h"
#include "include/GaussSolver/lu_solver.h"
#include "include/GaussSolver/matgen.h"
#include "include/GaussSolver/solver.h"
#include "include/quaternon_rotate.h"
#include "include/quaternion.h"
#include "include/quaternion_io.h"
#include "include/Matrix/rectangular_matrix.h"
#include "include/Matrix/square_matrix.h"
#include "include/vector_io.h"

#ifdef _WIN32
#include <windows.h>
#endif

void create_quaternion_matrices(SquareMatrix<Quaternion>& first_matrix, SquareMatrix<Quaternion>& second_matrix) {
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

  first_matrix = SquareMatrix<Quaternion>(first_items, 2);
  second_matrix = SquareMatrix<Quaternion>(second_items, 2);
}

void print_menu() {
  std::cout << "Выберите пример:\n";
  std::cout << "1. Операции с матрицами кватернионов\n";
  std::cout << "2. Вращение на кватернионах\n";
  std::cout << "3. Элементарные преобразования прямоугольной матрицы\n";
  std::cout << "4. Решение СЛАУ и LU-разложение\n";
  std::cout << "5. LU для матрицы Гильберта\n";
  std::cout << "0. Выход\n\n";
}

int read_choice() {
  int choice = 0;

  while (true) {
    std::cout << "Ваш выбор: ";
    if (std::cin >> choice) {
      return choice;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите целое число.\n";
  }
}

void wait_for_enter() {
  std::cout << "\nНажмите Enter, чтобы продолжить...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void show_quaternion_matrix_example() {
  SquareMatrix<Quaternion> first_matrix(2);
  SquareMatrix<Quaternion> second_matrix(2);
  create_quaternion_matrices(first_matrix, second_matrix);

  SquareMatrix<Quaternion> sum = first_matrix + second_matrix;
  SquareMatrix<Quaternion> scaled = first_matrix * Quaternion(2.0, 0.0, 0.0, 0.0);

  std::cout << "Первая матрица кватернионов:\n" << first_matrix << '\n';
  std::cout << "Вторая матрица кватернионов:\n" << second_matrix << '\n';
  std::cout << "Сумма матриц:\n" << sum << '\n';
  std::cout << "Умножаем первую матрицу на скаляр (2, 0, 0, 0):\n" << scaled << '\n';
  std::cout << "Норма первой матрицы: " << first_matrix.norm() << "\n\n";
}

void show_quaternion_rotation_example() {
  SquareMatrix<Quaternion> first_matrix(2);
  SquareMatrix<Quaternion> second_matrix(2);
  create_quaternion_matrices(first_matrix, second_matrix);

  const double pi = std::acos(-1.0);
  Quaternion rotation = QuaternionRotate::from_axis_angle(0.0, 0.0, 1.0, pi / 2.0);
  Quaternion vector(0.0, 1.0, 0.0, 0.0);
  Quaternion rotated_vector = QuaternionRotate::rotate_vector(vector, rotation);
  SquareMatrix<Quaternion> rotated_matrix = QuaternionRotate::rotate_matrix(first_matrix, rotation);

  std::cout << "Поворот вектора (1, 0, 0) вокруг оси Z на 90 градусов:\n" << rotated_vector << "\n\n";
  std::cout << "Первая матрица после поэлементного вращения вокруг оси Z на 90 градусов:\n" << rotated_matrix << '\n';
}

void show_rectangular_matrix_example() {
  Quaternion first_items[] = {
      Quaternion(1.0, 0.0, 1.0, 0.0),
      Quaternion(2.0, 1.0, 0.0, 0.0),
      Quaternion(0.0, 1.0, 0.0, 1.0),
      Quaternion(3.0, 0.0, 0.0, 1.0)
  };
  RectangularMatrix<Quaternion> rectangular(first_items, 2, 2);
  rectangular.swap_rows(0, 1);
  rectangular.scale_column(0, Quaternion::identity());

  std::cout << "Прямоугольная матрица после перемещения строк:\n" << rectangular << '\n';
}

void show_linear_system_example() {
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
}

void show_hilbert_lu_example() {
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
}

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  bool is_running = true;

  while (is_running) {
    print_menu();

    switch (read_choice()) {
      case 1:
        show_quaternion_matrix_example();
        break;
      case 2:
        show_quaternion_rotation_example();
        break;
      case 3:
        show_rectangular_matrix_example();
        break;
      case 4:
        show_linear_system_example();
        break;
      case 5:
        show_hilbert_lu_example();
        break;
      case 0:
        is_running = false;
        break;
      default:
        std::cout << "Неизвестная команда.\n";
        break;
    }

    if (is_running) {
      wait_for_enter();
    }
  }

  return 0;
}
