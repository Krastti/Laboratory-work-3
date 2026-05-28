#include "diagonal_matrix.h"
#include <stdexcept>

template <class T>
void DiagonalMatrix<T>::check_count(int count) const {
  if (count < 0) throw std::out_of_range("Element count cannot be negative");
  if (count > this->get_size()) {
    throw std::invalid_argument("Element count cannot be greater than matrix capacity");
  }
}

template <class T>
void DiagonalMatrix<T>::initialize_from_array(const T* source_elements, int count) {
  for (int index = 0; index < count; index++) {
    TriangularMatrix<T>::set_item(index, index, source_elements[index]);
  }
}

template <class T>
void DiagonalMatrix<T>::initialize_from_sequence(const Sequence<T>& sequence) {
  int count = sequence.get_length();

  for (int index = 0; index < count; index++) {
    TriangularMatrix<T>::set_item(index, index, sequence.get(index));
  }
}

template <class T>
Matrix<T>* DiagonalMatrix<T>::create_empty(int rows_count, int columns_count) const {
  if (rows_count < 0) throw std::out_of_range("Matrix row count cannot be negative");
  if (columns_count < 0) throw std::out_of_range("Matrix column count cannot be negative");
  if (rows_count != columns_count) throw std::invalid_argument("Diagonal matrix must have equal row and column counts");

  return new DiagonalMatrix<T>(rows_count);
}

template <class T>
void DiagonalMatrix<T>::set_item(int row, int column, const T& value) {
  if (row != column) {
    if (value != T()) {
      throw std::invalid_argument("Cannot set non-zero value outside diagonal matrix diagonal");
    }

    TriangularMatrix<T>::set_item(row, column, T());
    return;
  }

  TriangularMatrix<T>::set_item(row, column, value);
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int size) : TriangularMatrix<T>(size) {}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const T* source_elements, int size) : TriangularMatrix<T>(size) {
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");

  initialize_from_array(source_elements, size);
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const T* source_elements, int count, int size) : TriangularMatrix<T>(size) {
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");
  check_count(count);

  initialize_from_array(source_elements, count);
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(Sequence<T>* sequence, int size) : TriangularMatrix<T>(size) {
  if (sequence == nullptr) throw std::invalid_argument("Cannot create matrix from null sequence");
  check_count(sequence->get_length());

  initialize_from_sequence(*sequence);
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T>& other) : TriangularMatrix<T>(other) {}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator=(const DiagonalMatrix<T>& other) {
  if (this == &other) return *this;

  TriangularMatrix<T>::operator=(other);

  return *this;
}

template <class T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator+(const DiagonalMatrix<T>& other) const {
  DiagonalMatrix<T> result(*this);
  result += other;

  return result;
}

template <class T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator*(const T& scalar) const {
  DiagonalMatrix<T> result(*this);
  result *= scalar;

  return result;
}

template <class T>
DiagonalMatrix<T> DiagonalMatrix<T>::sum(const DiagonalMatrix<T>& other) const {
  return *this + other;
}

template <class T>
DiagonalMatrix<T> DiagonalMatrix<T>::multiply_by_scalar(const T& scalar) const {
  return *this * scalar;
}

template <class T>
DiagonalMatrix<T>::~DiagonalMatrix() {}
