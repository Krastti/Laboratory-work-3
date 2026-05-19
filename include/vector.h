#ifndef LABORATORYWORK3_VECTOR_H
#define LABORATORYWORK3_VECTOR_H

#include "baseADT/array_sequence.h"

template <class T>
class Vector {
private:
  MutableArraySequence<T>* coordinates;
  int dimension;

  void check_index(int index) const;
  void check_dimension(const Vector<T>& other) const;

public:
  Vector();
  Vector(Sequence<T>* seq);
  Vector(const T* items, int count);
  Vector(const Vector<T>& other);

  Vector<T>& operator=(const Vector<T>& other);

  const T& get(int index) const;
  T& get(int index);
  const T& operator[](int index) const;
  T& operator[](int index);
  void set(int index, const T& value);

  int get_dimension() const;

  Vector<T>* sum(const Vector<T>& other) const;
  Vector<T>* multiply_by_scalar(const T& scalar) const;
  T dot_product(const Vector<T>& other) const;
  double norm() const;

  Vector<T>& operator+=(const Vector<T>& other);
  Vector<T>& operator*=(const T& scalar);
  Vector<T> operator+(const Vector<T>& other) const;
  Vector<T> operator*(const T& scalar) const;

  virtual ~Vector();
};

#include "vector.tpp"

#endif // LABORATORYWORK3_VECTOR_H
