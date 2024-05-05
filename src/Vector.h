// Vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <iomanip>

template<typename T>
class Vector {
private:
  T* elements;
  int index = 0;
  size_t size;

public:
  //Empty Constructor
  Vector<T>() : Vector<T>(0){}

  //Constructor with size
  //template<typename T>
  Vector<T>(size_t size) : size(size), elements(nullptr) {
    if (size > 0) {
      this->elements = new T[size];
    }
  }

  //Copy Constructor
  Vector<T>(const Vector& other) : size(other.getSize()) {
    this->elements = new T[size];
    std::copy(other.elements, other.elements + size, elements);
  }

  //for adding elements
  int getIndex() const {
    return this->index;
  }

  size_t getSize() const {
    return this->size;
  }

  bool isFull() const {
    return this->size - 1 == this->index;
  }

  void resize(const size_t new_size) {
    T *new_arr = new T[new_size];

    if (this->size > 0) {
        // Take minimum between new_size and size_ for the loop end declaration
        size_t copy_size = (new_size > this->size ? this->size : new_size);
        for (int i = 0; i < copy_size; i++) {
            new_arr[i] = this->elements[i];
        }
        delete[] this->elements;
    }
    this->elements = new_arr;
    this->size = new_size;
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
    if(this == &other) {
        return *this;
    }
    delete[] this->elements;
    this->size = other.getSize();
    this->elements = new T[this->size];
    std::copy(other.elements, other.elements + this->getSize(), elements);
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

  Vector<T> operator*(const Vector& other) const {
    if (this->getSize() != other.getSize()) {
      std::cout << "Invalid sizes for multiplying vectors! Returning the source vector." << std::endl;
      return *this;
    }

    for (int i = 0; i < this->getSize(); i++) *(this->getElements() + i) = *(this->getElements() + i) * *(other.getElements() + i);
    return *this;

  }

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

    int vectorSize;
    int itemSize;

    //Vector input-stream example: (size, item_size) (item1,item2, ...itemSize-1)
    in.ignore(); //ignore first (
    in >> std::setw(3) >> vectorSize;
    vector.resize(vectorSize);

    in.ignore(2); //ignore ,
    in >> std::setw(3) >> itemSize;
    in.ignore(3); //ignore ) (
    for (int i = 0; i < vector.getSize(); i++) {
      in >> std::setw(itemSize) >> vector.getElements()[i]; //set the value
      in.ignore(); //skip the comma
    }

    return in;
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
