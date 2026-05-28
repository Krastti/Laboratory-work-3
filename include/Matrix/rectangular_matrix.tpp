#include "../baseADT/array_sequence.h"
#include "rectangular_matrix.h"
#include <stdexcept>

template <class T>
void RectangularMatrix<T>::check_size(int rows_count, int columns_count) const {
  if (rows_count < 0) throw std::out_of_range("Matrix row count cannot be negative");
  if (columns_count < 0) throw std::out_of_range("Matrix column count cannot be negative");
  if (rows_count == 0) throw std::invalid_argument("Matrix row count must be positive");
  if (columns_count == 0) throw std::invalid_argument("Matrix column count must be positive");
}

template <class T>
void RectangularMatrix<T>::check_index(int row, int column) const {
  if (row < 0) throw std::out_of_range("Row index is out of range");
  if (row >= row_count) throw std::out_of_range("Row index is out of range");
  if (column < 0) throw std::out_of_range("Column index is out of range");
  if (column >= column_count) throw std::out_of_range("Column index is out of range");
}

template <class T>
Vector<T> RectangularMatrix<T>::create_row_from_array(const T* source_elements, int count, int row) const {
  Sequence<T>* sequence = new MutableArraySequence<T>();
  int first_index = row * column_count;

  for (int column = 0; column < column_count; column++) {
    int source_index = first_index + column;
    sequence->append(source_index < count ? source_elements[source_index] : T());
  }

  try {
    Vector<T> result(sequence);
    delete sequence;
    return result;
  } catch (...) {
    delete sequence;
    throw;
  }
}

template <class T>
Vector<T> RectangularMatrix<T>::create_row_from_sequence(const Sequence<T>& sequence, int row) const {
  Sequence<T>* row_sequence = new MutableArraySequence<T>();
  int first_index = row * column_count;
  int count = sequence.get_length();

  for (int column = 0; column < column_count; column++) {
    int source_index = first_index + column;
    row_sequence->append(source_index < count ? sequence.get(source_index) : T());
  }

  try {
    Vector<T> result(row_sequence);
    delete row_sequence;
    return result;
  } catch (...) {
    delete row_sequence;
    throw;
  }
}

template <class T>
void RectangularMatrix<T>::initialize_rows_from_array(const T* source_elements, int count) {
  for (int row = 0; row < row_count; row++) {
    rows.append(create_row_from_array(source_elements, count, row));
  }
}

template <class T>
void RectangularMatrix<T>::initialize_rows_from_sequence(const Sequence<T>& sequence) {
  for (int row = 0; row < row_count; row++) {
    rows.append(create_row_from_sequence(sequence, row));
  }
}

template <class T>
Matrix<T>* RectangularMatrix<T>::create_empty(int rows_count, int columns_count) const {
  return new RectangularMatrix<T>(rows_count, columns_count);
}

template <class T>
void RectangularMatrix<T>::set_item(int row, int column, const T& value) {
  check_index(row, column);

  rows[row].set(column, value);
}

template <class T>
RectangularMatrix<T>::RectangularMatrix(int rows_count, int columns_count) : rows(), row_count(rows_count), column_count(columns_count) {
  check_size(rows_count, columns_count);
  initialize_rows_from_array(nullptr, 0);
}

template <class T>
RectangularMatrix<T>::RectangularMatrix(const T* source_elements, int rows_count, int columns_count) : rows(), row_count(rows_count), column_count(columns_count) {
  check_size(rows_count, columns_count);
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");

  initialize_rows_from_array(source_elements, rows_count * columns_count);
}

template <class T>
RectangularMatrix<T>::RectangularMatrix(const T* source_elements, int count, int rows_count, int columns_count) : rows(), row_count(rows_count), column_count(columns_count) {
  check_size(rows_count, columns_count);
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");
  if (count < 0) throw std::out_of_range("Element count cannot be negative");
  if (count > rows_count * columns_count) {
    throw std::invalid_argument("Element count cannot be greater than matrix capacity");
  }

  initialize_rows_from_array(source_elements, count);
}

template <class T>
RectangularMatrix<T>::RectangularMatrix(Sequence<T>* sequence, int rows_count, int columns_count) : rows(), row_count(rows_count), column_count(columns_count) {
  check_size(rows_count, columns_count);
  if (sequence == nullptr) throw std::invalid_argument("Cannot create matrix from null sequence");
  if (sequence->get_length() > rows_count * columns_count) {
    throw std::invalid_argument("Sequence length cannot be greater than matrix capacity");
  }

  initialize_rows_from_sequence(*sequence);
}

template <class T>
RectangularMatrix<T>::RectangularMatrix(const RectangularMatrix<T>& other) : rows(other.rows), row_count(other.row_count), column_count(other.column_count) {}

template <class T>
RectangularMatrix<T>& RectangularMatrix<T>::operator=(const RectangularMatrix<T>& other) {
  if (this == &other) return *this;

  rows = other.rows;
  row_count = other.row_count;
  column_count = other.column_count;

  return *this;
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::operator+(const RectangularMatrix<T>& other) const {
  RectangularMatrix<T> result(*this);
  result += other;

  return result;
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::operator*(const T& scalar) const {
  RectangularMatrix<T> result(*this);
  result *= scalar;

  return result;
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::sum(const RectangularMatrix<T>& other) const {
  return *this + other;
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::multiply_by_scalar(const T& scalar) const {
  return *this * scalar;
}

template <class T>
int RectangularMatrix<T>::get_row_count() const {
  return row_count;
}

template <class T>
int RectangularMatrix<T>::get_column_count() const {
  return column_count;
}

template <class T>
const T& RectangularMatrix<T>::get(int row, int column) const {
  check_index(row, column);

  return rows[row].get(column);
}

template <class T>
RectangularMatrix<T>::~RectangularMatrix() {}
