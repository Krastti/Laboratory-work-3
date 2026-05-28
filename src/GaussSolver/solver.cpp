#include "../../include/GaussSolver/solver.h"

#include <cmath>
#include <stdexcept>

Vector<double> Solver::solve(const SquareMatrix<double>& coefficients,
                             const Vector<double>& free_terms,
                             Method method) {
  check_system(coefficients, free_terms);

  SquareMatrix<double> work_coefficients(coefficients);
  Vector<double> work_free_terms(free_terms);

  if (method == Method::Classic) {
    forward_classic(work_coefficients, work_free_terms);
  } else {
    forward_with_pivot(work_coefficients, work_free_terms);
  }

  return back_substitution(work_coefficients, work_free_terms);
}

Vector<double> Solver::solve_classic(const SquareMatrix<double>& coefficients,
                                     const Vector<double>& free_terms) {
  return solve(coefficients, free_terms, Method::Classic);
}

Vector<double> Solver::solve_with_pivot(const SquareMatrix<double>& coefficients,
                                        const Vector<double>& free_terms) {
  return solve(coefficients, free_terms, Method::Pivot);
}

Vector<double> Solver::forward_substitution(const Matrix<double>& lower,
                                            const Vector<double>& free_terms) {
  check_system(lower, free_terms);

  Vector<double> result(free_terms);

  for (int row = 0; row < lower.get_row_count(); row++) {
    const double pivot = lower.get(row, row);
    if (std::abs(pivot) < EPSILON) {
      throw std::invalid_argument("Zero diagonal element in forward substitution");
    }

    double value = free_terms.get(row);
    for (int column = 0; column < row; column++) {
      value -= lower.get(row, column) * result.get(column);
    }
    result.set(row, value / pivot);
  }

  return result;
}

Vector<double> Solver::back_substitution(const Matrix<double>& upper,
                                         const Vector<double>& free_terms) {
  check_system(upper, free_terms);

  Vector<double> result(free_terms);

  for (int row = upper.get_row_count() - 1; row >= 0; row--) {
    const double pivot = upper.get(row, row);
    if (std::abs(pivot) < EPSILON) {
      throw std::invalid_argument("Zero diagonal element in back substitution");
    }

    double value = free_terms.get(row);
    for (int column = row + 1; column < upper.get_column_count(); column++) {
      value -= upper.get(row, column) * result.get(column);
    }
    result.set(row, value / pivot);
  }

  return result;
}

double Solver::residual(const Matrix<double>& coefficients,
                        const Vector<double>& free_terms,
                        const Vector<double>& solution) {
  check_solution_system(coefficients, free_terms, solution);

  double sum = 0.0;

  for (int row = 0; row < coefficients.get_row_count(); row++) {
    double row_value = 0.0;
    for (int column = 0; column < coefficients.get_column_count(); column++) {
      row_value += coefficients.get(row, column) * solution.get(column);
    }

    const double difference = row_value - free_terms.get(row);
    sum += difference * difference;
  }

  return std::sqrt(sum);
}

void Solver::check_square_matrix(const Matrix<double>& matrix) {
  if (matrix.get_row_count() != matrix.get_column_count()) {
    throw std::invalid_argument("Coefficient matrix must be square");
  }
}

void Solver::check_system(const Matrix<double>& coefficients,
                          const Vector<double>& free_terms) {
  check_square_matrix(coefficients);

  if (coefficients.get_row_count() != free_terms.get_dimension()) {
    throw std::invalid_argument("Matrix size and vector dimension do not match");
  }
}

void Solver::check_solution_system(const Matrix<double>& coefficients,
                                   const Vector<double>& free_terms,
                                   const Vector<double>& solution) {
  check_system(coefficients, free_terms);

  if (coefficients.get_column_count() != solution.get_dimension()) {
    throw std::invalid_argument("Matrix size and solution dimension do not match");
  }
}

void Solver::forward_classic(SquareMatrix<double>& coefficients,
                             Vector<double>& free_terms) {
  const int size = coefficients.get_size();

  for (int column = 0; column < size; column++) {
    const double pivot = coefficients.get(column, column);
    if (std::abs(pivot) < EPSILON) {
      throw std::invalid_argument("Zero pivot element in classic Gaussian elimination");
    }

    for (int row = column + 1; row < size; row++) {
      const double factor = coefficients.get(row, column) / pivot;
      free_terms.set(row, free_terms.get(row) - factor * free_terms.get(column));
      coefficients.sum_row_to_row(column, row, -factor);
    }
  }
}

void Solver::forward_with_pivot(SquareMatrix<double>& coefficients,
                                Vector<double>& free_terms) {
  const int size = coefficients.get_size();

  for (int column = 0; column < size; column++) {
    int pivot_row = column;
    double max_value = std::abs(coefficients.get(column, column));

    for (int row = column + 1; row < size; row++) {
      const double value = std::abs(coefficients.get(row, column));
      if (value > max_value) {
        max_value = value;
        pivot_row = row;
      }
    }

    if (max_value < EPSILON) {
      throw std::invalid_argument("Pivot element is too small");
    }

    if (pivot_row != column) {
      coefficients.swap_rows(column, pivot_row);

      const double temp = free_terms.get(column);
      free_terms.set(column, free_terms.get(pivot_row));
      free_terms.set(pivot_row, temp);
    }

    const double pivot = coefficients.get(column, column);
    for (int row = column + 1; row < size; row++) {
      const double factor = coefficients.get(row, column) / pivot;
      free_terms.set(row, free_terms.get(row) - factor * free_terms.get(column));
      coefficients.sum_row_to_row(column, row, -factor);
    }
  }
}
