#ifndef LABORATORYWORK3_SQUARE_MATRIX_H
#define LABORATORYWORK3_SQUARE_MATRIX_H

#include "matrix.h"

template <class T>
class SquareMatrix : public Matrix<T> {
private:
  Vector<T>** rows;
  int size;

  void check_size(int value) const;
  void check_index(int row, int column) const;

  Vector<T>* create_row_from_array(const T* source_elements, int count, int row) const;
  Vector<T>* create_row_from_sequence(const Sequence<T>& sequence, int row) const;

  void initialize_rows_from_array(const T* source_elements, int count);
  void initialize_rows_from_sequence(const Sequence<T>& sequence);

  Vector<T>** clone_rows(const SquareMatrix<T>& other) const;
  void release_rows();

protected:
  Matrix<T>* create_empty(int rows_count, int columns_count) const override;
  void set_item(int row, int column, const T& value) override;

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
  int get_row_count() const override;
  int get_column_count() const override;
  const T& get(int row, int column) const override;

  ~SquareMatrix() override;
};

#include "square_matrix.tpp"

#endif // LABORATORYWORK3_SQUARE_MATRIX_H
