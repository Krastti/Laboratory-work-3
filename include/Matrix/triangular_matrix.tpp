#include "triangular_matrix.h"
#include <stdexcept>

template <class T>
void TriangularMatrix<T>::check_size(int value) const {
  if (value < 0) throw std::out_of_range("Matrix size cannot be negative");
  if (value == 0) throw std::invalid_argument("Matrix size must be positive");
}

template <class T>
void TriangularMatrix<T>::check_index(int row, int column) const {
  if (row < 0) throw std::out_of_range("Row index is out of range");
  if (row >= size) throw std::out_of_range("Row index is out of range");
  if (column < 0) throw std::out_of_range("Column index is out of range");
  if (column >= size) throw std::out_of_range("Column index is out of range");
}

template <class T>
int TriangularMatrix<T>::get_storage_size() const {
  return size * (size + 1) / 2;
}

template <class T>
int TriangularMatrix<T>::get_storage_index(int row, int column) const {
  return row * size - row * (row - 1) / 2 + column - row;
}

template <class T>
void TriangularMatrix<T>::initialize_from_array(const T* source_elements, int count) {
  int storage_size = get_storage_size();

  for (int index = 0; index < storage_size; index++) {
    elements.append(index < count ? source_elements[index] : T());
  }
}

template <class T>
void TriangularMatrix<T>::initialize_from_sequence(const Sequence<T>& sequence) {
  int storage_size = get_storage_size();
  int count = sequence.get_length();

  for (int index = 0; index < storage_size; index++) {
    elements.append(index < count ? sequence.get(index) : T());
  }
}

template <class T>
Matrix<T>* TriangularMatrix<T>::create_empty(int rows_count, int columns_count) const {
  if (rows_count < 0) throw std::out_of_range("Matrix row count cannot be negative");
  if (columns_count < 0) throw std::out_of_range("Matrix column count cannot be negative");
  if (rows_count != columns_count) throw std::invalid_argument("Triangular matrix must have equal row and column counts");

  return new TriangularMatrix<T>(rows_count);
}

template <class T>
void TriangularMatrix<T>::set_item(int row, int column, const T& value) {
  check_index(row, column);

  if (column < row) {
    if (value != T()) {
      throw std::invalid_argument("Cannot set non-zero value below triangular matrix diagonal");
    }

    return;
  }

  elements[get_storage_index(row, column)] = value;
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(int size) : elements(), size(size), zero(T()) {
  check_size(size);

  initialize_from_array(nullptr, 0);
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(const T* source_elements, int size) : elements(), size(size), zero(T()) {
  check_size(size);
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");

  initialize_from_array(source_elements, get_storage_size());
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(const T* source_elements, int count, int size) : elements(), size(size), zero(T()) {
  check_size(size);
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");
  if (count < 0) throw std::out_of_range("Element count cannot be negative");
  if (count > get_storage_size()) {
    throw std::invalid_argument("Element count cannot be greater than matrix capacity");
  }

  initialize_from_array(source_elements, count);
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(Sequence<T>* sequence, int size) : elements(), size(size), zero(T()) {
  check_size(size);
  if (sequence == nullptr) throw std::invalid_argument("Cannot create matrix from null sequence");
  if (sequence->get_length() > get_storage_size()) {
    throw std::invalid_argument("Sequence length cannot be greater than matrix capacity");
  }

  initialize_from_sequence(*sequence);
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(const TriangularMatrix<T>& other)
  : elements(other.elements), size(other.size), zero(T()) {}

template <class T>
TriangularMatrix<T>& TriangularMatrix<T>::operator=(const TriangularMatrix<T>& other) {
  if (this == &other) return *this;

  elements = other.elements;
  size = other.size;
  zero = T();

  return *this;
}

template <class T>
TriangularMatrix<T> TriangularMatrix<T>::operator+(const TriangularMatrix<T>& other) const {
  TriangularMatrix<T> result(*this);
  result += other;

  return result;
}

template <class T>
TriangularMatrix<T> TriangularMatrix<T>::operator*(const T& scalar) const {
  TriangularMatrix<T> result(*this);
  result *= scalar;

  return result;
}

template <class T>
TriangularMatrix<T> TriangularMatrix<T>::sum(const TriangularMatrix<T>& other) const {
  return *this + other;
}

template <class T>
TriangularMatrix<T> TriangularMatrix<T>::multiply_by_scalar(const T& scalar) const {
  return *this * scalar;
}

template <class T>
int TriangularMatrix<T>::get_size() const {
  return size;
}

template <class T>
int TriangularMatrix<T>::get_row_count() const {
  return size;
}

template <class T>
int TriangularMatrix<T>::get_column_count() const {
  return size;
}

template <class T>
const T& TriangularMatrix<T>::get(int row, int column) const {
  check_index(row, column);

  if (column < row) {
    return zero;
  }

  return elements[get_storage_index(row, column)];
}

template <class T>
TriangularMatrix<T>::~TriangularMatrix() {
}
