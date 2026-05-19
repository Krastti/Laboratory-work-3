#include "square_matrix.h"
#include <stdexcept>

template <class T>
Matrix<T>* SquareMatrix<T>::create_empty(int rows_count, int columns_count) const {
  if (rows_count < 0) throw std::out_of_range("Matrix row count cannot be negative");
  if (columns_count < 0) throw std::out_of_range("Matrix column count cannot be negative");
  if (rows_count != columns_count) throw std::invalid_argument("Square matrix must have equal row and column counts");

  return new SquareMatrix<T>(rows_count);
}

template <class T>
SquareMatrix<T>::SquareMatrix(int size) : RectangularMatrix<T>(size, size) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const T* source_elements, int size) : RectangularMatrix<T>(source_elements, size, size) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const T* source_elements, int count, int size) : RectangularMatrix<T>(source_elements, count, size, size) {}

template <class T>
SquareMatrix<T>::SquareMatrix(Sequence<T>* sequence, int size) : RectangularMatrix<T>(sequence, size, size) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other) : RectangularMatrix<T>(other) {}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& other) {
  if (this == &other) return *this;

  RectangularMatrix<T>::operator=(other);

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
  return this->get_row_count();
}
