#include <cmath>
#include <stdexcept>
#include <ostream>
#include "matrix.h"
#include "complex.h"
#include "baseADT/array_sequence.h"

template <class T>
void Matrix<T>::check_row_index(int row) const {
  if (row < 0) throw std::out_of_range("Row index is out of range");
  if (row >= get_row_count()) throw std::out_of_range("Row index is out of range");
}

template <class T>
void Matrix<T>::check_column_index(int column) const {
  if (column < 0) throw std::out_of_range("Column index is out of range");
  if (column >= get_column_count()) throw std::out_of_range("Column index is out of range");
}

template <class T>
void Matrix<T>::check_indexes(int row, int column) const {
  check_row_index(row);
  check_column_index(column);
}

template <class T>
void Matrix<T>::check_same_dimensions(const Matrix<T>& other) const {
  if (get_row_count() != other.get_row_count()) {
    throw std::invalid_argument("Matrix row counts do not match");
  }

  if (get_column_count() != other.get_column_count()) {
    throw std::invalid_argument("Matrix column counts do not match");
  }
}

template <class T>
const T& Matrix<T>::operator()(int row, int column) const {
  check_indexes(row, column);

  return get(row, column);
}

template <class T>
Vector<T>* Matrix<T>::get_row(int row) const {
  check_row_index(row);

  Sequence<T>* sequence = new MutableArraySequence<T>();

  for (int column = 0; column < get_column_count(); column++) {
    sequence->append(get(row, column));
  }

  Vector<T>* result = new Vector<T>(sequence);
  delete sequence;

  return result;
}

template <class T>
Vector<T>* Matrix<T>::get_column(int column) const {
  check_column_index(column);

  Sequence<T>* sequence = new MutableArraySequence<T>();

  for (int row = 0; row < get_row_count(); row++) {
    sequence->append(get(row, column));
  }

  Vector<T>* result = new Vector<T>(sequence);
  delete sequence;

  return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
  check_same_dimensions(other);

  for (int row = 0; row < get_row_count(); row++) {
    Vector<T>* this_row = get_row(row);
    Vector<T>* other_row = other.get_row(row);
    Vector<T>* result_row = this_row->sum(*other_row); // <- Реализация унарного оператора через фукнциональную зависимость

    for (int col = 0; col < get_column_count(); col++) {
      set_item(row, col, result_row->get(col));
    }

    delete this_row;
    delete other_row;
    delete result_row;
  }

  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
  for (int row = 0; row < get_row_count(); row++) {
    Vector<T>* this_row = get_row(row);
    Vector<T>* result_row = this_row->multiply_by_scalar(scalar); // <- Аналогично тому, что выше

    for (int col = 0; col < get_column_count(); col++) {
      set_item(row, col, result_row->get(col));
    }

    delete this_row;
    delete result_row;
  }

  return *this;
}

template <class T>
double matrix_norm_square(const T& value) {
  return static_cast<double>(value * value);
}

inline double matrix_norm_square(const Complex& value) {
  return value.get_real() * value.get_real() + value.get_imag() * value.get_imag();
}

template <class T>
double Matrix<T>::norm() const {
  double result = 0.0;

  for (int row = 0; row < get_row_count(); row++) {
    for (int column = 0; column < get_column_count(); column++) {
      result += matrix_norm_square(get(row, column));
    }
  }

  return std::sqrt(result);
}

template <class T>
void Matrix<T>::swap_rows(int first_row, int second_row) {
  check_row_index(first_row);
  check_row_index(second_row);

  for (int column = 0; column < get_column_count(); column++) {
    T temp = get(first_row, column);
    set_item(first_row, column, get(second_row, column));
    set_item(second_row, column, temp);
  }
}

template <class T>
void Matrix<T>::swap_columns(int first_column, int second_column) {
  check_column_index(first_column);
  check_column_index(second_column);

  for (int row = 0; row < get_row_count(); row++) {
    T temp = get(row, first_column);
    set_item(row, first_column, get(row, second_column));
    set_item(row, second_column, temp);
  }
}

template <class T>
void Matrix<T>::scale_row(int row, const T& scalar) {
  check_row_index(row);

  for (int column = 0; column < get_column_count(); column++) {
    set_item(row, column, get(row, column) * scalar);
  }
}

template <class T>
void Matrix<T>::scale_column(int column, const T& scalar) {
  check_column_index(column);

  for (int row = 0; row < get_row_count(); row++) {
    set_item(row, column, get(row, column) * scalar);
  }
}

template <class T>
void Matrix<T>::sum_row_to_row(int source_row, int target_row, const T& scalar) {
  check_row_index(source_row);
  check_row_index(target_row);

  for (int column = 0; column < get_column_count(); column++) {
    T value = get(target_row, column) + get(source_row, column) * scalar;
    set_item(target_row, column, value);
  }
}

template <class T>
void Matrix<T>::sum_column_to_column(int source_column, int target_column, const T& scalar) {
  check_column_index(source_column);
  check_column_index(target_column);

  for (int row = 0; row < get_row_count(); row++) {
    T value = get(row, target_column) + get(row, source_column) * scalar;
    set_item(row, target_column, value);
  }
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
  for (int row = 0; row < matrix.get_row_count(); row++) {
    if (row > 0) {
      out << '\n';
    }

    out << '|';

    for (int column = 0; column < matrix.get_column_count(); column++) {
      if (column > 0) {
        out << ", ";
      }

      out << matrix.get(row, column);
    }

    out << '|';
  }

  out << '\n';

  return out;
}
