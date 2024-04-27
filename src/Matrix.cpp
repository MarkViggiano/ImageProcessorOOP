// Matrix.cpp

#include "Matrix.h"
#include <stdexcept>

// Default constructor
Matrix::Matrix() {}

// Constructor with rows and columns
Matrix::Matrix(int rows, int columns) {
  std::cout << "calling constructor\n";
  //Matrix::data = Vector<Vector<uint8_t>>(rows);
  std::cout << "setting data\n";
  Matrix::numRows = rows;
  Matrix::numCols = columns;
  std::cout << "generating data\n";
  //for (int i = 0; i < rows; i++) {
    //Matrix::data[i] = Vector<uint8_t>(columns);
    //for (int j = 0; j < columns; j++) {
      //Matrix::data[i][j] = 0;
    //}
  //}
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
}

// Destructor
Matrix::~Matrix() {}

// Number of rows
int Matrix::getRows() const {
    return data.getSize();
}

// Number of columns
int Matrix::getCols() const {
    return Matrix::data.getSize() > 0 ? Matrix::data[0].getSize() : 0;
}

std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
  /*

  out << "Rows, Columns: " << mat.getRows() << ", " << mat.getCols() << "\n";
  out << "{\n";
  for (int i = 0; i < mat.getRows(); i++) {
    out << mat[i];
  }
  out << "}\n";

  return out;

  */

  out << "Printed matrix!!\n";
  return out;
}

// Arithmetic operators
Matrix Matrix::operator+(const Matrix& other) {
    // YOUR CODE HERE
}

Matrix Matrix::operator-(const Matrix& other) {
    // YOUR CODE HERE
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
    // YOUR CODE HERE
}
