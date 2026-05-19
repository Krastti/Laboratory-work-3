#ifndef LABORATORYWORK3_VECTOR_IO_H
#define LABORATORYWORK3_VECTOR_IO_H

#include <ostream>
#include "vector.h"

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vector) {
  out << '[';

  for (int i = 0; i < vector.get_dimension(); i++) {
    if (i > 0) {
      out << ", ";
    }

    out << vector[i];
  }

  out << ']';

  return out;
}

#endif // LABORATORYWORK3_VECTOR_IO_H
