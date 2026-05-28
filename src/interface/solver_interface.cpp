#include "solver_interface.h"

#include "../../include/GaussSolver/lu_solver.h"
#include "../../include/GaussSolver/solver.h"
#include "../../include/Matrix/matrix_io.h"
#include "../../include/baseADT/array_sequence.h"
#include "../../include/vector_io.h"

#include <iostream>
#include <limits>
#include <stdexcept>

void SolverInterface::run() {
  bool is_running = true;

  while (is_running) {
    print_menu();

    switch (const int choice = read_int("Выберите действие: ")) {
      case 1:
        solve_manual_system();
        break;
      case 0:
        is_running = false;
        break;
      default:
        std::cout << "Неизвестная команда.\n";
        break;
    }

    if (is_running) {
      std::cout << "\nНажмите Enter, чтобы продолжить...";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.get();
    }
  }
}

void SolverInterface::print_menu() {
  std::cout << "1. Ввести матрицу и решить СЛАУ\n";
  std::cout << "0. Выход\n\n";
}

void SolverInterface::solve_manual_system() {
  try {
    const int size = read_int("Введите размер квадратной матрицы: ");
    if (size <= 0) {
      std::cout << "Размер матрицы должен быть положительным.\n";
      return;
    }

    SquareMatrix<double> coefficients = read_matrix(size);
    Vector<double> free_terms = read_vector(size);

    std::cout << "\nДоступные солверы:\n";
    std::cout << "1. Классический метод Гаусса\n";
    std::cout << "2. Метод Гаусса с выбором ведущей строки\n";
    std::cout << "3. LU-разложение\n";

    const int solver_type = read_int("Выберите солвер: ");
    Vector<double> solution = solve_system(coefficients, free_terms, solver_type);

    std::cout << "\nМатрица коэффициентов:\n" << coefficients;
    std::cout << "Вектор свободных членов: " << free_terms << '\n';
    std::cout << "Решение: " << solution << '\n';
    std::cout << "Невязка: " << Solver::residual(coefficients, free_terms, solution) << '\n';
  } catch (const std::exception& error) {
    std::cout << "Ошибка: " << error.what() << '\n';
  }
}

SquareMatrix<double> SolverInterface::read_matrix(int size) {
  MutableArraySequence<double> items;

  std::cout << "\nВведите элементы матрицы построчно.\n";
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      std::cout << "A[" << row + 1 << "][" << column + 1 << "] = ";
      items.append(read_double(""));
    }
  }

  return SquareMatrix<double>(&items, size);
}

Vector<double> SolverInterface::read_vector(int size) {
  MutableArraySequence<double> items;

  std::cout << "\nВведите элементы вектора свободных членов.\n";
  for (int index = 0; index < size; index++) {
    std::cout << "b[" << index + 1 << "] = ";
    items.append(read_double(""));
  }

  return Vector<double>(&items);
}

Vector<double> SolverInterface::solve_system(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms, int solver_type) {
  switch (solver_type) {
    case 1:
      return Solver::solve_classic(coefficients, free_terms);
    case 2:
      return Solver::solve_with_pivot(coefficients, free_terms);
    case 3:
      return LUSolver::decompose_and_solve(coefficients, free_terms);
    default:
      throw std::invalid_argument("Unknown solver type");
  }
}

int SolverInterface::read_int(const char* prompt) {
  int value = 0;

  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      return value;
    }

    clear_input();
    std::cout << "Введите целое число.\n";
  }
}

double SolverInterface::read_double(const char* prompt) {
  double value = 0.0;

  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      return value;
    }

    clear_input();
    std::cout << "Введите число.\n";
  }
}

void SolverInterface::clear_input() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
