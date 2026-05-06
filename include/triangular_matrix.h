#ifndef LABORATORYWORK3_TRIANGULAR_MATRIX_H
#define LABORATORYWORK3_TRIANGULAR_MATRIX_H

#include "matrix.h"

template <class T>
class TriangularMatrix : public Matrix<T> {
private:
  T* elements;
  int size;
  T zero;

  void check_size(int value) const;
  void check_index(int row, int column) const;
  int get_storage_size() const;
  int get_storage_index(int row, int column) const;

  void initialize_from_array(const T* source_elements, int count);
  void initialize_from_sequence(const Sequence<T>& sequence);

  using Matrix<T>::swap_rows;
  using Matrix<T>::swap_columns;
  using Matrix<T>::scale_row;
  using Matrix<T>::scale_column;
  using Matrix<T>::sum_row_to_row;
  using Matrix<T>::sum_column_to_column;

protected:
  Matrix<T>* create_empty(int rows_count, int columns_count) const override;
  void set_item(int row, int column, const T& value) override;

public:
  TriangularMatrix(int size);
  TriangularMatrix(const T* source_elements, int size);
  TriangularMatrix(const T* source_elements, int count, int size);
  TriangularMatrix(Sequence<T>* sequence, int size);
  TriangularMatrix(const TriangularMatrix<T>& other);

  // void swap_rows(int first_row, int second_row) = delete;

  using Matrix<T>::operator+=;
  using Matrix<T>::operator*=;

  TriangularMatrix<T>& operator=(const TriangularMatrix<T>& other);
  TriangularMatrix<T> operator+(const TriangularMatrix<T>& other) const;
  TriangularMatrix<T> operator*(const T& scalar) const;

  TriangularMatrix<T> sum(const TriangularMatrix<T>& other) const;
  TriangularMatrix<T> multiply_by_scalar(const T& scalar) const;

  int get_size() const;
  int get_row_count() const override;
  int get_column_count() const override;
  const T& get(int row, int column) const override;

  ~TriangularMatrix() override;
};

#include "triangular_matrix.tpp"

#endif // LABORATORYWORK3_TRIANGULAR_MATRIX_H
