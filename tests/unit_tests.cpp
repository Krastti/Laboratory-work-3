#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "../include/vector.h"
#include "../include/complex.h"
#include "../include/quaternion.h"
#include "../include/diagonal_matrix.h"
#include "../include/rectangular_matrix.h"
#include "../include/square_matrix.h"
#include "../include/triangular_matrix.h"

const double EPSILON = 1e-9;

void assert_close(double actual, double expected) {
  assert(std::abs(actual - expected) < EPSILON);
}

void assert_complex_equal(const Complex& actual, const Complex& expected) {
  assert_close(actual.get_real(), expected.get_real());
  assert_close(actual.get_imag(), expected.get_imag());
}

void assert_quaternion_equal(const Quaternion& actual, const Quaternion& expected) {
  assert_close(actual.get_w(), expected.get_w());
  assert_close(actual.get_x(), expected.get_x());
  assert_close(actual.get_y(), expected.get_y());
  assert_close(actual.get_z(), expected.get_z());
}

void assert_should_have_thrown() {
  assert(false && "should have thrown");
}

void test_vector_asserts() {
  int items[] = {1, 2, 3};
  Vector<int> vector(items, 3);

  assert(vector.get_dimension() == 3);
  assert(vector.get(0) == 1);
  assert(vector[1] == 2);

  vector.set(1, 5);
  assert(vector.get(1) == 5);
  assert(vector[1] == 5);

  Vector<int>* sum = vector.sum(Vector<int>(items, 3));
  assert(sum->get(0) == 2);
  assert(sum->get(1) == 7);
  assert(sum->get(2) == 6);
  delete sum;

  Vector<int> operator_sum = vector + Vector<int>(items, 3);
  assert(operator_sum.get(0) == 2);
  assert(operator_sum.get(1) == 7);
  assert(operator_sum.get(2) == 6);

  int compound_items[] = {1, 2, 3};
  int compound_other_items[] = {4, 5, 6};
  Vector<int> compound_vector(compound_items, 3);
  Vector<int> compound_other(compound_other_items, 3);
  Vector<int>& sum_reference = compound_vector += compound_other;
  assert(&sum_reference == &compound_vector);
  assert(compound_vector.get(0) == 5);
  assert(compound_vector.get(1) == 7);
  assert(compound_vector.get(2) == 9);

  Vector<int>* multiplied_pointer = vector.multiply_by_scalar(2);
  assert(multiplied_pointer->get(0) == 2);
  assert(multiplied_pointer->get(1) == 10);
  assert(multiplied_pointer->get(2) == 6);
  delete multiplied_pointer;

  Vector<int> multiplied = vector * 2;
  assert(multiplied.get(0) == 2);
  assert(multiplied.get(1) == 10);
  assert(multiplied.get(2) == 6);

  Vector<int>& multiply_reference = compound_vector *= 2;
  assert(&multiply_reference == &compound_vector);
  assert(compound_vector.get(0) == 10);
  assert(compound_vector.get(1) == 14);
  assert(compound_vector.get(2) == 18);

  assert(vector.dot_product(Vector<int>(items, 3)) == 20);
  assert_close(vector.norm(), std::sqrt(35.0));

  double double_items[] = {3.0, 4.0};
  Vector<double> double_vector(double_items, 2);
  Vector<double> double_multiplied = double_vector * 0.5;
  assert_close(double_multiplied.get(0), 1.5);
  assert_close(double_multiplied.get(1), 2.0);
  assert_close(double_vector.dot_product(double_vector), 25.0);
  assert_close(double_vector.norm(), 5.0);

  Complex complex_items[] = {Complex(1.0, 2.0), Complex(3.0, -1.0)};
  Vector<Complex> complex_vector(complex_items, 2);
  Vector<Complex> complex_multiplied = complex_vector * Complex(2.0);
  assert_complex_equal(complex_multiplied.get(0), Complex(2.0, 4.0));
  assert_complex_equal(complex_multiplied.get(1), Complex(6.0, -2.0));
  assert_complex_equal(complex_vector.dot_product(complex_vector), Complex(5.0, -2.0));
  assert_close(complex_vector.norm(), std::sqrt(15.0));

  try {
    Vector<int> null_vector(nullptr, 3);
    (void)null_vector;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    Vector<int> empty(items, 0);
    (void)empty;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    vector.get(-1);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    vector.get(vector.get_dimension());
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    int other_items[] = {1, 2};
    Vector<int> other(other_items, 2);
    Vector<int>* bad_sum = vector.sum(other);
    delete bad_sum;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    int other_items[] = {1, 2};
    Vector<int> other(other_items, 2);
    vector += other;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    int other_items[] = {1, 2};
    Vector<int> other(other_items, 2);
    int bad_product = vector.dot_product(other);
    (void)bad_product;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }
}

void test_square_matrix_asserts() {
  int items[] = {1, 2, 3, 4};
  SquareMatrix<int> zero_matrix(2);
  SquareMatrix<int> matrix(items, 2);

  assert(zero_matrix.get_size() == 2);
  assert(zero_matrix.get(0, 0) == 0);
  assert(zero_matrix.get(1, 1) == 0);
  assert(matrix.get_size() == 2);
  assert(matrix.get_row_count() == 2);
  assert(matrix.get_column_count() == 2);
  assert(matrix.get(0, 0) == 1);
  assert(matrix(1, 1) == 4);

  SquareMatrix<int> sum = matrix.sum(matrix);
  assert(sum.get(0, 0) == 2);
  assert(sum.get(0, 1) == 4);
  assert(sum.get(1, 0) == 6);
  assert(sum.get(1, 1) == 8);

  SquareMatrix<int> operator_sum = matrix + matrix;
  assert(operator_sum.get(0, 0) == 2);
  assert(operator_sum.get(1, 1) == 8);

  SquareMatrix<int> multiplied = matrix.multiply_by_scalar(3);
  assert(multiplied.get(0, 0) == 3);
  assert(multiplied.get(0, 1) == 6);
  assert(multiplied.get(1, 0) == 9);
  assert(multiplied.get(1, 1) == 12);

  SquareMatrix<int> operator_multiplied = matrix * 2;
  assert(operator_multiplied.get(0, 0) == 2);
  assert(operator_multiplied.get(1, 1) == 8);
  assert_close(matrix.norm(), std::sqrt(30.0));

  Vector<int>* row = matrix.get_row(1);
  assert(row->get_dimension() == 2);
  assert(row->get(0) == 3);
  assert(row->get(1) == 4);
  delete row;

  Vector<int>* column = matrix.get_column(0);
  assert(column->get_dimension() == 2);
  assert(column->get(0) == 1);
  assert(column->get(1) == 3);
  delete column;

  SquareMatrix<int> transformed(items, 2);
  transformed.swap_rows(0, 1);
  assert(transformed.get(0, 0) == 3);
  assert(transformed.get(0, 1) == 4);
  assert(transformed.get(1, 0) == 1);
  assert(transformed.get(1, 1) == 2);

  transformed.swap_columns(0, 1);
  assert(transformed.get(0, 0) == 4);
  assert(transformed.get(0, 1) == 3);
  assert(transformed.get(1, 0) == 2);
  assert(transformed.get(1, 1) == 1);

  transformed.scale_row(0, 2);
  assert(transformed.get(0, 0) == 8);
  assert(transformed.get(0, 1) == 6);

  transformed.scale_column(1, 3);
  assert(transformed.get(0, 1) == 18);
  assert(transformed.get(1, 1) == 3);

  transformed.sum_row_to_row(0, 1, 1);
  assert(transformed.get(1, 0) == 10);
  assert(transformed.get(1, 1) == 21);

  transformed.sum_column_to_column(0, 1, -1);
  assert(transformed.get(0, 1) == 10);
  assert(transformed.get(1, 1) == 11);

  try {
    SquareMatrix<int> empty(0);
    (void)empty;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    SquareMatrix<int> negative(-1);
    (void)negative;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    SquareMatrix<int> null_matrix(static_cast<const int*>(nullptr), 2);
    (void)null_matrix;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  int short_items[] = {1, 2, 3};
  SquareMatrix<int> short_matrix(short_items, 3, 2);
  assert(short_matrix.get(0, 0) == 1);
  assert(short_matrix.get(0, 1) == 2);
  assert(short_matrix.get(1, 0) == 3);
  assert(short_matrix.get(1, 1) == 0);

  try {
    matrix.get(-1, 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, -1);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(matrix.get_size(), 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, matrix.get_size());
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    SquareMatrix<int> other(3);
    SquareMatrix<int> bad_sum = matrix + other;
    (void)bad_sum;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }
}

void test_rectangular_matrix_asserts() {
  int items[] = {1, 2, 3, 4, 5, 6};
  RectangularMatrix<int> zero_matrix(2, 3);
  RectangularMatrix<int> matrix(items, 2, 3);

  assert(zero_matrix.get_row_count() == 2);
  assert(zero_matrix.get_column_count() == 3);
  assert(zero_matrix.get(0, 0) == 0);
  assert(zero_matrix.get(1, 2) == 0);
  assert(matrix.get_row_count() == 2);
  assert(matrix.get_column_count() == 3);
  assert(matrix.get(0, 0) == 1);
  assert(matrix(1, 2) == 6);

  RectangularMatrix<int> sum = matrix.sum(matrix);
  assert(sum.get(0, 0) == 2);
  assert(sum.get(0, 1) == 4);
  assert(sum.get(0, 2) == 6);
  assert(sum.get(1, 0) == 8);
  assert(sum.get(1, 1) == 10);
  assert(sum.get(1, 2) == 12);

  RectangularMatrix<int> operator_sum = matrix + matrix;
  assert(operator_sum.get(0, 0) == 2);
  assert(operator_sum.get(1, 2) == 12);

  RectangularMatrix<int> multiplied = matrix.multiply_by_scalar(2);
  assert(multiplied.get(0, 0) == 2);
  assert(multiplied.get(0, 1) == 4);
  assert(multiplied.get(0, 2) == 6);
  assert(multiplied.get(1, 0) == 8);
  assert(multiplied.get(1, 1) == 10);
  assert(multiplied.get(1, 2) == 12);

  RectangularMatrix<int> operator_multiplied = matrix * 3;
  assert(operator_multiplied.get(0, 0) == 3);
  assert(operator_multiplied.get(1, 2) == 18);
  assert_close(matrix.norm(), std::sqrt(91.0));

  Vector<int>* row = matrix.get_row(1);
  assert(row->get_dimension() == 3);
  assert(row->get(0) == 4);
  assert(row->get(1) == 5);
  assert(row->get(2) == 6);
  delete row;

  Vector<int>* column = matrix.get_column(2);
  assert(column->get_dimension() == 2);
  assert(column->get(0) == 3);
  assert(column->get(1) == 6);
  delete column;

  RectangularMatrix<int> transformed(items, 2, 3);
  transformed.swap_rows(0, 1);
  assert(transformed.get(0, 0) == 4);
  assert(transformed.get(0, 1) == 5);
  assert(transformed.get(0, 2) == 6);
  assert(transformed.get(1, 0) == 1);
  assert(transformed.get(1, 1) == 2);
  assert(transformed.get(1, 2) == 3);

  transformed.swap_columns(0, 2);
  assert(transformed.get(0, 0) == 6);
  assert(transformed.get(0, 2) == 4);
  assert(transformed.get(1, 0) == 3);
  assert(transformed.get(1, 2) == 1);

  transformed.scale_row(0, 2);
  assert(transformed.get(0, 0) == 12);
  assert(transformed.get(0, 1) == 10);
  assert(transformed.get(0, 2) == 8);

  transformed.scale_column(1, 3);
  assert(transformed.get(0, 1) == 30);
  assert(transformed.get(1, 1) == 6);

  transformed.sum_row_to_row(0, 1, 1);
  assert(transformed.get(1, 0) == 15);
  assert(transformed.get(1, 1) == 36);
  assert(transformed.get(1, 2) == 9);

  transformed.sum_column_to_column(0, 2, -1);
  assert(transformed.get(0, 2) == -4);
  assert(transformed.get(1, 2) == -6);

  try {
    RectangularMatrix<int> empty_rows(0, 3);
    (void)empty_rows;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    RectangularMatrix<int> empty_columns(2, 0);
    (void)empty_columns;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    RectangularMatrix<int> negative_rows(-1, 3);
    (void)negative_rows;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    RectangularMatrix<int> negative_columns(2, -1);
    (void)negative_columns;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    RectangularMatrix<int> null_matrix(static_cast<const int*>(nullptr), 2, 3);
    (void)null_matrix;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  int short_items[] = {1, 2, 3, 4, 5};
  RectangularMatrix<int> short_matrix(short_items, 5, 2, 3);
  assert(short_matrix.get(0, 0) == 1);
  assert(short_matrix.get(0, 1) == 2);
  assert(short_matrix.get(0, 2) == 3);
  assert(short_matrix.get(1, 0) == 4);
  assert(short_matrix.get(1, 1) == 5);
  assert(short_matrix.get(1, 2) == 0);

  try {
    RectangularMatrix<int> negative_count(items, -1, 2, 3);
    (void)negative_count;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    RectangularMatrix<int> too_many_items(items, 7, 2, 3);
    (void)too_many_items;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    matrix.get(-1, 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, -1);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(matrix.get_row_count(), 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, matrix.get_column_count());
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    RectangularMatrix<int> other(3, 2);
    RectangularMatrix<int> bad_sum = matrix + other;
    (void)bad_sum;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }
}

void test_triangular_matrix_asserts() {
  int items[] = {1, 2, 3, 4, 5, 6};
  TriangularMatrix<int> zero_matrix(3);
  TriangularMatrix<int> matrix(items, 3);

  assert(zero_matrix.get_size() == 3);
  assert(zero_matrix.get(0, 0) == 0);
  assert(zero_matrix.get(2, 0) == 0);
  assert(matrix.get_size() == 3);
  assert(matrix.get_row_count() == 3);
  assert(matrix.get_column_count() == 3);
  assert(matrix.get(0, 0) == 1);
  assert(matrix.get(0, 1) == 2);
  assert(matrix.get(0, 2) == 3);
  assert(matrix.get(1, 0) == 0);
  assert(matrix.get(1, 1) == 4);
  assert(matrix.get(1, 2) == 5);
  assert(matrix.get(2, 0) == 0);
  assert(matrix.get(2, 1) == 0);
  assert(matrix.get(2, 2) == 6);
  assert(matrix(2, 2) == 6);

  TriangularMatrix<int> sum = matrix.sum(matrix);
  assert(sum.get(0, 0) == 2);
  assert(sum.get(0, 1) == 4);
  assert(sum.get(0, 2) == 6);
  assert(sum.get(1, 0) == 0);
  assert(sum.get(1, 1) == 8);
  assert(sum.get(1, 2) == 10);
  assert(sum.get(2, 2) == 12);

  TriangularMatrix<int> operator_sum = matrix + matrix;
  assert(operator_sum.get(0, 2) == 6);
  assert(operator_sum.get(2, 2) == 12);

  TriangularMatrix<int> multiplied = matrix.multiply_by_scalar(2);
  assert(multiplied.get(0, 0) == 2);
  assert(multiplied.get(0, 1) == 4);
  assert(multiplied.get(1, 0) == 0);
  assert(multiplied.get(1, 1) == 8);
  assert(multiplied.get(2, 2) == 12);

  TriangularMatrix<int> operator_multiplied = matrix * 3;
  assert(operator_multiplied.get(0, 2) == 9);
  assert(operator_multiplied.get(2, 2) == 18);
  assert_close(matrix.norm(), std::sqrt(91.0));

  Vector<int>* row = matrix.get_row(1);
  assert(row->get_dimension() == 3);
  assert(row->get(0) == 0);
  assert(row->get(1) == 4);
  assert(row->get(2) == 5);
  delete row;

  Vector<int>* column = matrix.get_column(2);
  assert(column->get_dimension() == 3);
  assert(column->get(0) == 3);
  assert(column->get(1) == 5);
  assert(column->get(2) == 6);
  delete column;

  try {
    TriangularMatrix<int> empty(0);
    (void)empty;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    TriangularMatrix<int> negative(-1);
    (void)negative;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    TriangularMatrix<int> null_matrix(static_cast<const int*>(nullptr), 3);
    (void)null_matrix;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    TriangularMatrix<int> negative_count(items, -1, 3);
    (void)negative_count;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    TriangularMatrix<int> too_many_items(items, 7, 3);
    (void)too_many_items;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    matrix.get(-1, 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, -1);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(matrix.get_size(), 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, matrix.get_size());
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    TriangularMatrix<int> other(4);
    TriangularMatrix<int> bad_sum = matrix + other;
    (void)bad_sum;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }
}

void test_diagonal_matrix_asserts() {
  int items[] = {1, 2, 3};
  DiagonalMatrix<int> zero_matrix(3);
  DiagonalMatrix<int> matrix(items, 3);

  assert(zero_matrix.get_size() == 3);
  assert(zero_matrix.get(0, 0) == 0);
  assert(zero_matrix.get(1, 2) == 0);
  assert(matrix.get_size() == 3);
  assert(matrix.get_row_count() == 3);
  assert(matrix.get_column_count() == 3);
  assert(matrix.get(0, 0) == 1);
  assert(matrix.get(0, 1) == 0);
  assert(matrix.get(0, 2) == 0);
  assert(matrix.get(1, 0) == 0);
  assert(matrix.get(1, 1) == 2);
  assert(matrix.get(1, 2) == 0);
  assert(matrix.get(2, 0) == 0);
  assert(matrix.get(2, 1) == 0);
  assert(matrix.get(2, 2) == 3);
  assert(matrix(2, 2) == 3);

  DiagonalMatrix<int> sum = matrix.sum(matrix);
  assert(sum.get(0, 0) == 2);
  assert(sum.get(0, 1) == 0);
  assert(sum.get(1, 1) == 4);
  assert(sum.get(2, 2) == 6);

  DiagonalMatrix<int> operator_sum = matrix + matrix;
  assert(operator_sum.get(0, 0) == 2);
  assert(operator_sum.get(2, 2) == 6);

  DiagonalMatrix<int> multiplied = matrix.multiply_by_scalar(2);
  assert(multiplied.get(0, 0) == 2);
  assert(multiplied.get(0, 1) == 0);
  assert(multiplied.get(1, 1) == 4);
  assert(multiplied.get(2, 2) == 6);

  DiagonalMatrix<int> operator_multiplied = matrix * 3;
  assert(operator_multiplied.get(0, 0) == 3);
  assert(operator_multiplied.get(2, 2) == 9);
  assert_close(matrix.norm(), std::sqrt(14.0));

  Vector<int>* row = matrix.get_row(1);
  assert(row->get_dimension() == 3);
  assert(row->get(0) == 0);
  assert(row->get(1) == 2);
  assert(row->get(2) == 0);
  delete row;

  Vector<int>* column = matrix.get_column(2);
  assert(column->get_dimension() == 3);
  assert(column->get(0) == 0);
  assert(column->get(1) == 0);
  assert(column->get(2) == 3);
  delete column;

  try {
    DiagonalMatrix<int> empty(0);
    (void)empty;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    DiagonalMatrix<int> negative(-1);
    (void)negative;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    DiagonalMatrix<int> null_matrix(static_cast<const int*>(nullptr), 3);
    (void)null_matrix;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    DiagonalMatrix<int> negative_count(items, -1, 3);
    (void)negative_count;
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    DiagonalMatrix<int> too_many_items(items, 4, 3);
    (void)too_many_items;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }

  try {
    matrix.get(-1, 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, -1);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(matrix.get_size(), 0);
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    matrix.get(0, matrix.get_size());
    assert_should_have_thrown();
  } catch (const std::out_of_range&) {
  }

  try {
    DiagonalMatrix<int> other(4);
    DiagonalMatrix<int> bad_sum = matrix + other;
    (void)bad_sum;
    assert_should_have_thrown();
  } catch (const std::invalid_argument&) {
  }
}

void test_quaternion_asserts() {
  Quaternion first(1.0, 2.0, 3.0, 4.0);
  Quaternion second(5.0, 6.0, 7.0, 8.0);

  assert_quaternion_equal(Quaternion::zero(), Quaternion(0.0, 0.0, 0.0, 0.0));
  assert_quaternion_equal(Quaternion::identity(), Quaternion(1.0, 0.0, 0.0, 0.0));
  assert_quaternion_equal(first + second, Quaternion(6.0, 8.0, 10.0, 12.0));
  assert_quaternion_equal(second - first, Quaternion(4.0, 4.0, 4.0, 4.0));
  assert_quaternion_equal(first * second, Quaternion(-60.0, 12.0, 30.0, 24.0));
  assert_quaternion_equal(first * 2.0, Quaternion(2.0, 4.0, 6.0, 8.0));
  assert_quaternion_equal(2.0 * first, Quaternion(2.0, 4.0, 6.0, 8.0));
  assert_quaternion_equal(first.conjugate(), Quaternion(1.0, -2.0, -3.0, -4.0));
  assert_close(first.norm_squared(), 30.0);
  assert_close(first.norm(), std::sqrt(30.0));

  Quaternion inverse = first.inverse();
  assert_quaternion_equal(inverse, Quaternion(1.0 / 30.0, -2.0 / 30.0, -3.0 / 30.0, -4.0 / 30.0));
  assert_quaternion_equal(first * inverse, Quaternion::identity());
  assert_close(first.normalize().norm(), 1.0);
  assert_quaternion_equal(Quaternion::zero().inverse(), Quaternion::zero());
  assert_quaternion_equal(Quaternion::zero().normalize(), Quaternion::zero());
}

void test_quaternion_matrix_asserts() {
  Quaternion items[] = {
      Quaternion(1.0, 0.0, 1.0, 0.0),
      Quaternion(2.0, 1.0, 0.0, 0.0),
      Quaternion(0.0, 1.0, 0.0, 1.0),
      Quaternion(3.0, 0.0, 0.0, 1.0)
  };

  SquareMatrix<Quaternion> matrix(items, 2);
  SquareMatrix<Quaternion> sum = matrix + matrix;
  SquareMatrix<Quaternion> multiplied = matrix * Quaternion::identity();

  assert_quaternion_equal(sum.get(0, 0), Quaternion(2.0, 0.0, 2.0, 0.0));
  assert_quaternion_equal(sum.get(1, 1), Quaternion(6.0, 0.0, 0.0, 2.0));
  assert_quaternion_equal(multiplied.get(0, 1), items[1]);
  assert_quaternion_equal(multiplied.get(1, 0), items[2]);
  assert_close(matrix.norm(), std::sqrt(18.0));
}

void run_all_tests() {
  test_vector_asserts();
  test_square_matrix_asserts();
  test_rectangular_matrix_asserts();
  test_triangular_matrix_asserts();
  test_diagonal_matrix_asserts();
  test_quaternion_asserts();
  test_quaternion_matrix_asserts();
}

void print_test_menu() {
  std::cout << "1. Vector Tests\n";
  std::cout << "2. Square Matrix Tests\n";
  std::cout << "3. Rectangular Matrix Tests\n";
  std::cout << "4. Triangular Matrix Tests\n";
  std::cout << "5. Diagonal Matrix Tests\n";
  std::cout << "6. Quaternion Tests\n";
  std::cout << "7. Quaternion Matrix Tests\n";
  std::cout << "8. All Tests\n";
  std::cout << "0. Exit\n";
}

int read_choice() {
  int choice = 0;

  if (!(std::cin >> choice)) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return -1;
  }

  return choice;
}

int main() {
  print_test_menu();

  int choice = read_choice();

  switch (choice) {
    case 1:
      test_vector_asserts();
      break;
    case 2:
      test_square_matrix_asserts();
      break;
    case 3:
      test_rectangular_matrix_asserts();
      break;
    case 4:
      test_triangular_matrix_asserts();
      break;
    case 5:
      test_diagonal_matrix_asserts();
      break;
    case 6:
      test_quaternion_asserts();
      break;
    case 7:
      test_quaternion_matrix_asserts();
      break;
    case 8:
      run_all_tests();
      break;
    case 0:
      return 0;
    default:
      std::cout << "Invalid choice\n";
      return 1;
  }

  std::cout << "Tests passed\n";
  return 0;
}
