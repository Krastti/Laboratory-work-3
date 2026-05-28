#include "../../include/GaussSolver/matgen.h"

#include "../../include/baseADT/array_sequence.h"

#include <cmath>
#include <limits>
#include <stdexcept>

SquareMatrix<double> Matgen::random_matrix(int size, double low, double high, unsigned int seed) {
  check_size(size);
  check_range(low, high);

  MutableArraySequence<double> items;

  for (int i = 0; i < size * size; i++) {
    items.append(low + (high - low) * random_0_1(seed));
  }

  return SquareMatrix<double>(&items, size);
}

Vector<double> Matgen::random_vector(int size, double low, double high, unsigned int seed) {
  check_size(size);
  check_range(low, high);

  MutableArraySequence<double> items;

  for (int i = 0; i < size; i++) {
    items.append(low + (high - low) * random_0_1(seed));
  }

  return Vector<double>(&items);
}

SquareMatrix<double> Matgen::hilbert_matrix(int size) {
  check_size(size);

  MutableArraySequence<double> items;

  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      items.append(1.0 / static_cast<double>(row + column + 1));
    }
  }

  return SquareMatrix<double>(&items, size);
}

Vector<double> Matgen::rhs_from_exact(const SquareMatrix<double>& coefficients, const Vector<double>& exact_solution) {
  const int size = coefficients.get_size();
  if (exact_solution.get_dimension() != size) {
    throw std::invalid_argument("Matrix size and exact solution dimension do not match");
  }

  MutableArraySequence<double> items;

  for (int row = 0; row < size; row++) {
    double value = 0.0;
    for (int column = 0; column < size; column++) {
      value += coefficients.get(row, column) * exact_solution.get(column);
    }
    items.append(value);
  }

  return Vector<double>(&items);
}

double Matgen::relative_error(const Vector<double>& approximate_solution, const Vector<double>& exact_solution) {
  if (approximate_solution.get_dimension() != exact_solution.get_dimension()) {
    throw std::invalid_argument("Solution dimensions do not match");
  }

  double diff_norm = 0.0;
  double exact_norm = 0.0;

  for (int i = 0; i < exact_solution.get_dimension(); i++) {
    const double difference = approximate_solution.get(i) - exact_solution.get(i);
    diff_norm += difference * difference;
    exact_norm += exact_solution.get(i) * exact_solution.get(i);
  }

  if (exact_norm == 0.0) {
    throw std::invalid_argument("Exact solution norm cannot be zero");
  }

  return std::sqrt(diff_norm) / std::sqrt(exact_norm);
}

double Matgen::random_0_1(unsigned int& seed) {
  seed = 1664525u * seed + 1013904223u;
  return static_cast<double>(seed) / static_cast<double>(std::numeric_limits<unsigned int>::max());
}

void Matgen::check_size(int size) {
  if (size <= 0) {
    throw std::invalid_argument("Size must be positive");
  }
}

void Matgen::check_range(double low, double high) {
  if (low >= high) {
    throw std::invalid_argument("Random range is invalid");
  }
}
