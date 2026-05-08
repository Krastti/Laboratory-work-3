#include <cmath>
#include <stdexcept>
#include <ostream>

#include "vector.h"
#include "complex.h"
#include "baseADT/array_sequence.h"

template <class T>
T vector_sum_pair(const Pair<T, T>& pair) {
  return pair.first() + pair.second();
}

template <class T>
T vector_multiply_item(const T& item, const T& scalar) {
  return item * scalar;
}

template <class T>
void Vector<T>::check_index(int index) const {
  if (index < 0) throw std::out_of_range("Индекс вне допустимого диапазона");
  if (index >= dimension) throw std::out_of_range("Индекс вне допустимого диапазона");
}

template <class T>
void Vector<T>::check_dimension(const Vector<T>& other) const {
  if (dimension != other.dimension) {
    throw std::invalid_argument("Размерности векторов не совпадают");
  }
}

template <class T>
Vector<T>* Vector<T>::create_from_sequence(Sequence<T>* sequence) const {
  return new Vector<T>(sequence);
}

template <class T>
Vector<T>::Vector() : coordinates(new MutableArraySequence<T>()), dimension(0) {}

template <class T>
Vector<T>::Vector(Sequence<T>* seq) : coordinates(nullptr), dimension(0) {
  if (seq == nullptr) throw std::invalid_argument("Нельзя создать вектор из нулевой последовательности");
  if (seq->get_length() == 0) throw std::invalid_argument("Нельзя создать вектор нулевой размерности");

  MutableArraySequence<T>* new_coordinates = new MutableArraySequence<T>();

  try {
    for (int index = 0; index < seq->get_length(); index++) {
      new_coordinates->append(seq->get(index));
    }
  } catch (...) {
    delete new_coordinates;
    throw;
  }

  coordinates = new_coordinates;
  dimension = seq->get_length();
}

template <class T>
Vector<T>::Vector(const T* items, int count) : coordinates(nullptr), dimension(0) {
  if (items == nullptr) throw std::invalid_argument("Нельзя создать вектор из нулевого массива");
  if (count <= 0) throw std::invalid_argument("Нельзя создать вектор нулевой размерности");

  coordinates = new MutableArraySequence<T>(items, count);
  dimension = count;
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : coordinates(new MutableArraySequence<T>(*other.coordinates)), dimension(other.dimension) {}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  if (this == &other) return *this;

  MutableArraySequence<T>* new_coordinates = new MutableArraySequence<T>(*other.coordinates);
  delete coordinates;
  coordinates = new_coordinates;
  dimension = other.dimension;

  return *this;
}

template <class T>
const T& Vector<T>::get(int index) const {
  check_index(index);

  return coordinates->get(index);
}

template <class T>
T& Vector<T>::get(int index) {
  check_index(index);

  return (*coordinates)[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const {
  return get(index);
}

template <class T>
T& Vector<T>::operator[](int index) {
  return get(index);
}

template <class T>
void Vector<T>::set(int index, const T& value) {
  check_index(index);

  (*coordinates)[index] = value;
}

template <class T>
int Vector<T>::get_dimension() const {
  return dimension;
}

template <class T>
Vector<T>* Vector<T>::sum(const Vector<T>& other) const {
  check_dimension(other);

  Sequence<Pair<T, T>>* zipped = zip(*coordinates, *other.coordinates);
  Sequence<T>* sequence = nullptr;
  Vector<T>* result = nullptr;

  try {
    sequence = zipped->map(vector_sum_pair<T>);
    result = create_from_sequence(sequence);
  } catch (...) {
    delete zipped;
    delete sequence;
    throw;
  }

  delete zipped;
  delete sequence;

  return result;
}

template <class T>
Vector<T>* Vector<T>::multiply_by_scalar(const T& scalar) const {
  Sequence<T>* sequence = nullptr;
  Vector<T>* result = nullptr;

  try {
    sequence = coordinates->map(vector_multiply_item<T>, scalar);
    result = create_from_sequence(sequence);
  } catch (...) {
    delete sequence;
    throw;
  }

  delete sequence;

  return result;
}

template <class T>
T Vector<T>::dot_product(const Vector<T>& other) const {
  check_dimension(other);

  T result = T();

  for (int i = 0; i < dimension; i++) {
    result = result + get(i) * other.get(i);
  }

  return result;
}

template <class T>
double vector_norm_square(const T& value) {
  return static_cast<double>(value * value);
}

inline double vector_norm_square(const Complex& value) {
  return value.get_real() * value.get_real() + value.get_imag() * value.get_imag();
}

template <class T>
double Vector<T>::norm() const {
  double result = 0.0;

  for (int i = 0; i < dimension; i++) {
    result += vector_norm_square(get(i));
  }

  return std::sqrt(result);
}

template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
  Vector<T>* result = sum(other);

  try {
    *this = *result;
  } catch (...) {
    delete result;
    throw;
  }

  delete result;

  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator*=(const T& scalar) {
  Vector<T>* result = multiply_by_scalar(scalar);

  try {
    *this = *result;
  } catch (...) {
    delete result;
    throw;
  }

  delete result;

  return *this;
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
  Vector<T> value(*this);
  value += other;

  return value;
}

template <class T>
Vector<T> Vector<T>::operator*(const T& scalar) const {
  Vector<T> value(*this);
  value *= scalar;

  return value;
}

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

template <class T>
Vector<T>::~Vector() {
  delete coordinates;
}
