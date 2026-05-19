#ifndef LABORATORYWORK3_MATRIX_IO_H
#define LABORATORYWORK3_MATRIX_IO_H

#include <ostream>
#include "matrix.h"
#include "vector_io.h"

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

#endif // LABORATORYWORK3_MATRIX_IO_H
