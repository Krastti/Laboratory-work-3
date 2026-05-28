#include "../../include/GaussSolver/lu_solver.h"
#include "../../include/GaussSolver/solver.h"
#include "../../include/baseADT/array_sequence.h"

#include <cmath>
#include <stdexcept>

LUDecomposition LUSolver::decompose(const SquareMatrix<double>& coefficients) {
  check_square_matrix(coefficients);

  const int size = coefficients.get_size();
  MutableArraySequence<double> lower_items;
  MutableArraySequence<double> upper_items;

  for (int i = 0; i < size * size; i++) {
    lower_items.append(0.0);
    upper_items.append(0.0);
  }

  for (int i = 0; i < size; i++) {
    lower_items[i * size + i] = 1.0;
  }

  for (int i = 0; i < size; i++) {
    for (int k = i; k < size; k++) {
      double sum = 0.0;

      for (int j = 0; j < i; j++) {
        sum += lower_items[i * size + j] * upper_items[j * size + k];
      }

      upper_items[i * size + k] = coefficients.get(i, k) - sum;
    }

    if (std::abs(upper_items[i * size + i]) < EPSILON) {
      throw std::invalid_argument("Zero diagonal element in LU decomposition");
    }

    for (int k = i + 1; k < size; k++) {
      double sum = 0.0;

      for (int j = 0; j < i; j++) {
        sum += lower_items[k * size + j] * upper_items[j * size + i];
      }

      lower_items[k * size + i] = (coefficients.get(k, i) - sum) / upper_items[i * size + i];
    }
  }

  return {
      RectangularMatrix<double>(&lower_items, size, size),
      RectangularMatrix<double>(&upper_items, size, size)
  };
}

Vector<double> LUSolver::solve(const RectangularMatrix<double>& lower, const RectangularMatrix<double>& upper, const Vector<double>& free_terms) {
  check_lu_system(lower, upper, free_terms);

  Vector<double> intermediate = Solver::forward_substitution(lower, free_terms);
  return Solver::back_substitution(upper, intermediate);
}

Vector<double> LUSolver::decompose_and_solve(const SquareMatrix<double>& coefficients, const Vector<double>& free_terms) {
  if (coefficients.get_size() != free_terms.get_dimension()) {
    throw std::invalid_argument("Matrix size and vector dimension do not match");
  }

  LUDecomposition decomposition = decompose(coefficients);
  return solve(decomposition.lower, decomposition.upper, free_terms);
}

void LUSolver::check_square_matrix(const SquareMatrix<double>& matrix) {
  if (matrix.get_row_count() != matrix.get_column_count()) {
    throw std::invalid_argument("Matrix must be square");
  }
}

void LUSolver::check_lu_system(const RectangularMatrix<double>& lower, const RectangularMatrix<double>& upper, const Vector<double>& free_terms) {
  if (lower.get_row_count() != lower.get_column_count()) {
    throw std::invalid_argument("Lower matrix must be square");
  }

  if (upper.get_row_count() != upper.get_column_count()) {
    throw std::invalid_argument("Upper matrix must be square");
  }

  if (lower.get_row_count() != upper.get_row_count()) {
    throw std::invalid_argument("LU matrix sizes do not match");
  }

  if (lower.get_row_count() != free_terms.get_dimension()) {
    throw std::invalid_argument("LU matrix size and vector dimension do not match");
  }
}
