// Matrix.cpp

#include "Matrix.h"
#include <stdexcept>

// Default constructor
Matrix::Matrix() {}

// Constructor with rows and columns
Matrix::Matrix(int rows, int cols) {
  this->numRows = rows;
  this->numCols = cols;
  this->data = Vector<Vector<uint8_t>>(rows);
  for (int i = 0; i < rows; i++) {
     this->data[i] = Vector<uint8_t>(cols);
  }
}

Matrix::Matrix(uint8_t* imageData, int rows, int cols, int channels) {
  this->numRows = rows;
  this->numCols = cols;
  this->data = Vector<Vector<uint8_t>>(rows);
  for (int i = 0; i < rows; i++) {
     this->data[i] = Vector<uint8_t>(cols);
  }

  //this is taken directly from the save method below.
  //if this is how it's accessed and then this is how its declared.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < channels; k++) {
          this->data[i][j * channels + k] = *(imageData + i + j + k);
      }
    }
  }

}

// Copy constructor
Matrix::Matrix(const Matrix& other) {
  Matrix::data = Vector<Vector<uint8_t>>(other.getRows());
  Matrix::numRows = other.getRows();
  Matrix::numCols = other.getCols();
  for (int i = 0; i < Matrix::numRows; i++) {
    Matrix::data[i] = other[i]; //set the value of each element
  }
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {

  Matrix::data = Vector<Vector<uint8_t>>(other.getRows());
  Matrix::numRows = other.getRows();
  Matrix::numCols = other.getCols();
  for (int i = 0; i < Matrix::numRows; i++) {
    Matrix::data[i] = other[i]; //set the value of each element
  }

  return *this;
}

// Destructor
Matrix::~Matrix() {}

// Number of rows
int Matrix::getRows() const {
    return numRows;
}

// Number of columns
int Matrix::getCols() const {
    return this->numCols;
}


std::ostream& operator<<(std::ostream& out, const Matrix& mat) {

  out << "Rows, Columns: " << mat.getRows() << ", " << mat.getCols() << std::endl;
  out << "{" << std::endl;
  for (int i = 0; i < mat.getRows(); i++) {
    out << "," << mat[i];
  }
  out << "}" << std::endl;

  return out;



  //out << "Printed matrix!!\n";
  //return out;
}


// Arithmetic operators
Matrix Matrix::operator+(const Matrix& other) {
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols()) {
    std::cout << "Invalid Matrix dimensions for adding! Returning first matrix." << std::endl;
    return *this;
  }

  for (int i = 0; i < this->getRows(); i++) {
    this->data[i] = this->data[i] + other[i];
  }

  return *this;

}

Matrix Matrix::operator-(const Matrix& other) {
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols()) {
    std::cout << "Invalid Matrix dimensions for subtracting! Returning first matrix." << std::endl;
    return *this;
  }

  for (int i = 0; i < this->getRows(); i++) {
    //subtract vectors from each other
    this->data[i] = this->data[i] - other[i];
  }

  return *this;
}

Matrix Matrix::operator*(const Matrix& other) {
    // YOUR CODE HERE
}

// Subscript operator
Vector<uint8_t> Matrix::operator[](int index) const {
   if (index > Matrix::getRows()) index = Matrix::getRows();
   return Matrix::data[index];
}

const Vector<uint8_t>& Matrix::operator[](int index) {
  if (index > Matrix::getRows()) index = Matrix::getRows();
  return Matrix::data[index];
}

// Transpose function (in-place)
void Matrix::transpose() {
    /*

    Transposing a Matrix is in short making the rows the columns and the columns the rows.

    [
    1, 2, 3, 4
    5, 6, 7, 8
    ]

    transposes into:
    [
    1, 5
    2, 6
    3, 7
    4, 8
    ]

    */

    Vector<Vector<uint8_t>> newData = Vector<Vector<uint8_t>>(this->getCols());
    Vector<uint8_t> rows;

    for (int i = 0; i < this->getCols(); i++) {
      rows = Vector<uint8_t>(this->getCols());
      for (int j = 0; j < this->getRows(); j++) {
        rows.addElement(this->data[i][j]);
      }
    }

}
