#ifndef LABORATORYWORK3_RECTANGULAR_MATRIX_H
#define LABORATORYWORK3_RECTANGULAR_MATRIX_H

#include "matrix.h"
#include "baseADT/array_sequence.h"

template <class T>
class RectangularMatrix : public Matrix<T> {
private:
  MutableArraySequence<Vector<T>> rows;
  int row_count;
  int column_count;

  void check_size(int rows_count, int columns_count) const;
  void check_index(int row, int column) const;

  Vector<T> create_row_from_array(const T* source_elements, int count, int row) const;
  Vector<T> create_row_from_sequence(const Sequence<T>& sequence, int row) const;

  void initialize_rows_from_array(const T* source_elements, int count);
  void initialize_rows_from_sequence(const Sequence<T>& sequence);

protected:
  Matrix<T>* create_empty(int rows_count, int columns_count) const override;
  void set_item(int row, int column, const T& value) override;

public:
  RectangularMatrix(int rows_count, int columns_count);
  RectangularMatrix(const T* source_elements, int rows_count, int columns_count);
  RectangularMatrix(const T* source_elements, int count, int rows_count, int columns_count);
  RectangularMatrix(Sequence<T>* sequence, int rows_count, int columns_count);
  RectangularMatrix(const RectangularMatrix<T>& other);

  using Matrix<T>::operator+=;
  using Matrix<T>::operator*=;

  RectangularMatrix<T>& operator=(const RectangularMatrix<T>& other);
  RectangularMatrix<T> operator+(const RectangularMatrix<T>& other) const;
  RectangularMatrix<T> operator*(const T& scalar) const;

  RectangularMatrix<T> sum(const RectangularMatrix<T>& other) const;
  RectangularMatrix<T> multiply_by_scalar(const T& scalar) const;

  int get_row_count() const override;
  int get_column_count() const override;
  const T& get(int row, int column) const override;

  ~RectangularMatrix() override;
};

#include "rectangular_matrix.tpp"

#endif // LABORATORYWORK3_RECTANGULAR_MATRIX_H
