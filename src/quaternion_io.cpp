#include "quaternion_io.h"

std::ostream& operator<<(std::ostream& out, const Quaternion& value) {
  out << value.get_w() << " + " << value.get_x() << 'i'
      << " + " << value.get_y() << 'j'
      << " + " << value.get_z() << 'k';

  return out;
}
