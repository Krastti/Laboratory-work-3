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

protected:
  /*
   * Спросить, является ли название данной функции семантически верным.
   * Функция является виртуальной фабрикой результатов. То есть f: Sequence<T> -> Vector<T>
   */
  virtual Vector<T>* create_from_sequence(Sequence<T>* sequence) const;

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

  virtual Vector<T>* sum(const Vector<T>& other) const;
  virtual Vector<T>* multiply_by_scalar(const T& scalar) const;
  T dot_product(const Vector<T>& other) const;
  double norm() const;

  Vector<T> operator+(const Vector<T>& other) const;
  Vector<T> operator*(const T& scalar) const;

  virtual ~Vector();
};

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vector);

#include "vector.tpp"

#endif // LABORATORYWORK3_VECTOR_H
