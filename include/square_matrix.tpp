#include <stdexcept>
#include "square_matrix.h"
#include "baseADT/array_sequence.h"

template <class T>
void SquareMatrix<T>::check_size(int value) const {
  if (value < 0) throw std::out_of_range("Matrix size cannot be negative");
  if (value == 0) throw std::invalid_argument("Matrix size must be positive");
}

template <class T>
void SquareMatrix<T>::check_index(int row, int column) const {
  if (row < 0) throw std::out_of_range("Row index is out of range");
  if (row >= size) throw std::out_of_range("Row index is out of range");
  if (column < 0) throw std::out_of_range("Column index is out of range");
  if (column >= size) throw std::out_of_range("Column index is out of range");
}

template <class T>
Vector<T>* SquareMatrix<T>::create_row_from_array(const T* source_elements, int count, int row) const {
  Sequence<T>* sequence = new MutableArraySequence<T>();
  int first_index = row * size;

  for (int column = 0; column < size; column++) {
    int source_index = first_index + column;
    sequence->append(source_index < count ? source_elements[source_index] : T());
  }

  Vector<T>* result = nullptr;

  try {
    result = new Vector<T>(sequence);
  } catch (...) {
    delete sequence;
    throw;
  }

  delete sequence;

  return result;
}

template <class T>
Vector<T>* SquareMatrix<T>::create_row_from_sequence(const Sequence<T>& sequence, int row) const {
  Sequence<T>* row_sequence = new MutableArraySequence<T>();
  int first_index = row * size;
  int count = sequence.get_length();

  for (int column = 0; column < size; column++) {
    int source_index = first_index + column;
    row_sequence->append(source_index < count ? sequence.get(source_index) : T());
  }

  Vector<T>* result = nullptr;

  try {
    result = new Vector<T>(row_sequence);
  } catch (...) {
    delete row_sequence;
    throw;
  }

  delete row_sequence;

  return result;
}

template <class T>
void SquareMatrix<T>::initialize_rows_from_array(const T* source_elements, int count) {
  rows = new Vector<T>*[size];

  for (int row = 0; row < size; row++) {
    rows[row] = nullptr;
  }

  try {
    for (int row = 0; row < size; row++) {
      rows[row] = create_row_from_array(source_elements, count, row);
    }
  } catch (...) {
    release_rows();
    throw;
  }
}

template <class T>
void SquareMatrix<T>::initialize_rows_from_sequence(const Sequence<T>& sequence) {
  rows = new Vector<T>*[size];

  for (int row = 0; row < size; row++) {
    rows[row] = nullptr;
  }

  try {
    for (int row = 0; row < size; row++) {
      rows[row] = create_row_from_sequence(sequence, row);
    }
  } catch (...) {
    release_rows();
    throw;
  }
}

template <class T>
Vector<T>** SquareMatrix<T>::clone_rows(const SquareMatrix<T>& other) const {
  Vector<T>** new_rows = new Vector<T>*[other.size];

  for (int row = 0; row < other.size; row++) {
    new_rows[row] = nullptr;
  }

  try {
    for (int row = 0; row < other.size; row++) {
      new_rows[row] = new Vector<T>(*other.rows[row]);
    }
  } catch (...) {
    for (int row = 0; row < other.size; row++) {
      delete new_rows[row];
    }

    delete[] new_rows;
    throw;
  }

  return new_rows;
}

template <class T>
void SquareMatrix<T>::release_rows() {
  if (rows == nullptr) return;

  for (int row = 0; row < size; row++) {
    delete rows[row];
  }

  delete[] rows;
  rows = nullptr;
}

template <class T>
Matrix<T>* SquareMatrix<T>::create_empty(int rows_count, int columns_count) const {
  if (rows_count < 0) throw std::out_of_range("Matrix row count cannot be negative");
  if (columns_count < 0) throw std::out_of_range("Matrix column count cannot be negative");
  if (rows_count != columns_count) throw std::invalid_argument("Square matrix must have equal row and column counts");

  return new SquareMatrix<T>(rows_count);
}

template <class T>
void SquareMatrix<T>::set_item(int row, int column, const T& value) {
  check_index(row, column);

  rows[row]->set(column, value);
}

template <class T>
SquareMatrix<T>::SquareMatrix(int size) : rows(nullptr), size(size) {
  check_size(size);
  initialize_rows_from_array(nullptr, 0);
}

template <class T>
SquareMatrix<T>::SquareMatrix(const T* source_elements, int size) : rows(nullptr), size(size) {
  check_size(size);
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");

  initialize_rows_from_array(source_elements, size * size);
}

template <class T>
SquareMatrix<T>::SquareMatrix(const T* source_elements, int count, int size) : rows(nullptr), size(size) {
  check_size(size);
  if (source_elements == nullptr) throw std::invalid_argument("Cannot create matrix from null array");
  if (count < 0) throw std::out_of_range("Element count cannot be negative");
  if (count > size * size) throw std::invalid_argument("Element count cannot be greater than matrix capacity");

  initialize_rows_from_array(source_elements, count);
}

template <class T>
SquareMatrix<T>::SquareMatrix(Sequence<T>* sequence, int size) : rows(nullptr), size(size) {
  check_size(size);
  if (sequence == nullptr) throw std::invalid_argument("Cannot create matrix from null sequence");
  if (sequence->get_length() > size * size) {
    throw std::invalid_argument("Sequence length cannot be greater than matrix capacity");
  }

  initialize_rows_from_sequence(*sequence);
}

template <class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other) : rows(nullptr), size(other.size) {
  rows = clone_rows(other);
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& other) {
  if (this == &other) return *this;

  Vector<T>** new_rows = clone_rows(other);
  release_rows();
  rows = new_rows;
  size = other.size;

  return *this;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T>& other) const {
  SquareMatrix<T> result(*this);
  result += other;

  return result;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T& scalar) const {
  SquareMatrix<T> result(*this);
  result *= scalar;

  return result;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::sum(const SquareMatrix<T>& other) const {
  return *this + other;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::multiply_by_scalar(const T& scalar) const {
  return *this * scalar;
}

template <class T>
int SquareMatrix<T>::get_size() const {
  return size;
}

template <class T>
int SquareMatrix<T>::get_row_count() const {
  return size;
}

template <class T>
int SquareMatrix<T>::get_column_count() const {
  return size;
}

template <class T>
const T& SquareMatrix<T>::get(int row, int column) const {
  check_index(row, column);

  return rows[row]->get(column);
}

template <class T>
SquareMatrix<T>::~SquareMatrix() {
  release_rows();
}
