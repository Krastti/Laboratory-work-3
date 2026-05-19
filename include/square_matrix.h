#ifndef LABORATORYWORK3_SQUARE_MATRIX_H
#define LABORATORYWORK3_SQUARE_MATRIX_H

#include "rectangular_matrix.h"

template <class T>
class SquareMatrix : public RectangularMatrix<T> {
protected:
  Matrix<T>* create_empty(int rows_count, int columns_count) const override;

public:
  SquareMatrix(int size);
  SquareMatrix(const T* source_elements, int size);
  SquareMatrix(const T* source_elements, int count, int size);
  SquareMatrix(Sequence<T>* sequence, int size);
  SquareMatrix(const SquareMatrix<T>& other);

  using Matrix<T>::operator+=;
  using Matrix<T>::operator*=;

  SquareMatrix<T>& operator=(const SquareMatrix<T>& other);
  SquareMatrix<T> operator+(const SquareMatrix<T>& other) const;
  SquareMatrix<T> operator*(const T& scalar) const;

  SquareMatrix<T> sum(const SquareMatrix<T>& other) const;
  SquareMatrix<T> multiply_by_scalar(const T& scalar) const;

  int get_size() const;
  ~SquareMatrix() override = default;
};

#include "square_matrix.tpp"

#endif // LABORATORYWORK3_SQUARE_MATRIX_H
