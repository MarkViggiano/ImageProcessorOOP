// Vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
private:
  T* elements;
  int index = 0;
  int size;

public:
  //Empty Constructor
  Vector<T>() {}

  //Constructor with size
  Vector<T>(int size) {
    this->size = size;
    this->elements = new T[size];
  }

  //Copy Constructor
  Vector<T>(const Vector& vector) {
    this->size = vector.getSize();
    this->index = vector.getIndex();
    this->elements = new T[this->size];
    for (int i = 0; i < this->getSize(); i++) {
      *(this->elements + i) = vector[i];
    }
  }

  //for adding elements
  int getIndex() const {
    return this->index;
  }

  int getSize() const {
    return this->size;
  }

  bool isFull() const {
    return this->size - 1 == this->index;
  }

  void addElement(const T& element) {
    if (this->isFull()) return;
    *(this->elements + this->index++) = element;
  }

  void setElements(const T* elements) {
    if (this->getElements() != NULL && this->getIndex() != 0) {
      for (int i = 0; i < this->getSize(); i++) {
        delete(this->getElements()[i]);
      }
      delete(this->getElements());
    }
  }

  T* getElements() const {
    return this->elements;
  }

  //Assignment
  Vector<T>& operator=(const Vector& other) {
    //Prevent Memory Leaks
    if (this->getElements() != NULL) delete(this->getElements());

    this->elements = new T[other.getSize()];
    this->size = other.getSize();
    this->index = other.getIndex();

    for (int i = 0; i < this->size; i++) {
      *(this->elements + i) = other[i];
    }

    return *this;
  }

  //Arithmetic
  Vector<T> operator+(const Vector& other) {
    if (other.getSize() != this->getSize()) {
      std::cout << "Invalid sizes for adding Vectors! Returning the first vector!" << std::endl;
      return *this;
    }

    for (int i = 0; i < this->getSize(); i++) *(this->getElements() + i) = *(this->getElements() + i) + *(other.getElements() + i);
    return *this;
  }

  Vector<T> operator-(const Vector& other) {
    if (other.getSize() != this->getSize()) {
      std::cout << "Invalid sizes for subtracting Vectors! Returning the first vector!" << std::endl;
      return *this;
    }

    for (int i = 0; i < this->getSize(); i++) *(this->getElements() + i) = *(this->getElements() + i) - *(other.getElements() + i);
    return *this;
  }

  //Vector<T> operator*(const Vector& other) const;

  // Subscript operator
  T operator[](int index) const {
      //if (this->getElements() == NULL) return NULL;
      if (this->getIndex() < index) index = this->getIndex();

      return *(this->getElements() + index);
  }

  T& operator[](int index) {
    //if (this->getElements() == NULL) return NULL;
    if (this->getIndex() < index) index = this->getIndex();

    return *(this->getElements() + index);
  }

  //Destructor
  virtual ~Vector() {
    //Free the memory of the elements list
    delete[] elements;
  }


  // Input stream operator
  friend std::istream& operator>>(std::istream& in, Vector& vector) {

  }

  // Output stream operator
  friend std::ostream& operator<<(std::ostream& out, const Vector& vector) {
    if (vector.getSize() == 0) {
        out << "{}" << std::endl;
    } else {
        out << "{";
        for (int i = 0; i < vector.getSize() - 1; i++) {
            out << "," << vector[i] << ", ";
        }
        out << vector[vector.getSize() - 1] << "}" << std::endl;
    }
    return out;
  }


};

#endif // VECTOR_H
