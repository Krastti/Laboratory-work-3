#include "complex_io.h"

std::ostream& operator<<(std::ostream& out, const Complex& value) {
  out << value.get_real();
  if (value.get_imag() < 0.0) {
    out << " - " << -value.get_imag() << 'i';
  } else {
    out << " + " << value.get_imag() << 'i';
  }

  return out;
}
