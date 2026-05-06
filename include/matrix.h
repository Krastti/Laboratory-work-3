#ifndef LABORATORYWORK3_MATRIX_H
#define LABORATORYWORK3_MATRIX_H

#include "vector.h"

template <class T>
class Matrix {
private:
  void check_row_index(int row) const;
  void check_column_index(int column) const;
  void check_indexes(int row, int column) const; // Проверка и строки и колонки
  void check_same_dimensions(const Matrix<T>& other) const;

protected:
  virtual Matrix<T>* create_empty(int rows_count, int columns_count) const = 0;
  virtual void set_item(int row, int column, const T& value) = 0;

public:
  virtual int get_row_count() const = 0;
  virtual int get_column_count() const = 0;
  virtual const T& get(int row, int column) const = 0;
  virtual const T& operator()(int row, int column) const;

  /*
   * Данные функции возвращают указатель, поэтому необходимо при вывода разыменовывать его
   * Пример: std::cout << *matrix.get_row(0) << std::endl;
   */
  Vector<T>* get_row(int row) const;
  Vector<T>* get_column(int column) const;

  Matrix<T>& operator+=(const Matrix<T>& other);
  Matrix<T>& operator*=(const T& scalar);

  virtual double norm() const;

  void swap_rows(int first_row, int second_row);
  void swap_columns(int first_column, int second_column);
  void scale_row(int row, const T& scalar);
  void scale_column(int column, const T& scalar);
  void sum_row_to_row(int source_row, int target_row, const T& scalar);
  void sum_column_to_column(int source_column, int target_column, const T& scalar);

  virtual ~Matrix() {}
};

template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

#include "matrix.tpp"

#endif // LABORATORYWORK3_MATRIX_H
