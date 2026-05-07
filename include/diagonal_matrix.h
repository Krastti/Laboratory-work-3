#ifndef LABORATORYWORK3_DIAGONAL_MATRIX_H
#define LABORATORYWORK3_DIAGONAL_MATRIX_H

#include "triangular_matrix.h"

template <class T>
class DiagonalMatrix : public TriangularMatrix<T> {
private:
  void check_count(int count) const;
  void initialize_from_array(const T* source_elements, int count);
  void initialize_from_sequence(const Sequence<T>& sequence);

protected:
  Matrix<T>* create_empty(int rows_count, int columns_count) const override;
  void set_item(int row, int column, const T& value) override;

public:
  DiagonalMatrix(int size);
  DiagonalMatrix(const T* source_elements, int size);
  DiagonalMatrix(const T* source_elements, int count, int size);
  DiagonalMatrix(Sequence<T>* sequence, int size);
  DiagonalMatrix(const DiagonalMatrix<T>& other);

  using Matrix<T>::operator+=;
  using Matrix<T>::operator*=;

  DiagonalMatrix<T>& operator=(const DiagonalMatrix<T>& other);
  DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& other) const;
  DiagonalMatrix<T> operator*(const T& scalar) const;

  DiagonalMatrix<T> sum(const DiagonalMatrix<T>& other) const;
  DiagonalMatrix<T> multiply_by_scalar(const T& scalar) const;

  ~DiagonalMatrix() override;
};

#include "diagonal_matrix.tpp"

#endif // LABORATORYWORK3_DIAGONAL_MATRIX_H
