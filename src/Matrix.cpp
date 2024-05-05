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
  for (int i = 0; i < cols; i++) {
    this->data[i].resize(cols);
  }

  // Initialize our matrix to 0 !
  for (int i = 0; i < rows; i++) {
    Vector<unsigned char> &row = this->data[i];
    for (int j = 0; i < cols; i++) {
      row[j] = 0;
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
Matrix::~Matrix() {
  for (int i = 0; i < this->getRows(); i++) {
    delete[] this->data[i].getElements();
  }
}

// Number of rows
int Matrix::getRows() const {
    return numRows;
}

void Matrix::setRows(int rows) {
    this->numRows = rows;
}

// Number of columns
int Matrix::getCols() const {
    return this->numCols;
}

void Matrix::setColumns(int cols) {
    this->numCols = cols;
}


std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    for (size_t i = 0; i < mat.getRows(); i++) {
        for (size_t j = 0; j < mat.getCols(); j++) {
          os << std::setw(3) << std::setfill('0') << static_cast<int>(mat[i][j]) << ' ';
        }
        os << '\n';
    }
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& in, Matrix& mat) {

  int rows;
  int cols;
  int itemSize;

  //Vector input-stream example: (rows, cols, item_size) (item1,item2, ...itemSize-1)
  in.ignore(); //ignore first (
  in >> std::setw(3) >> rows;

  in.ignore(2); //ignore , and space
  in >> std::setw(3) >> cols;

  in.ignore(2); //ignore , and space
  in >> std::setw(3) >> itemSize;

  mat = Matrix(rows, cols);

  in.ignore(3); //ignore ) (
  int temp; //for easy casting!!!
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      in >> std::setw(itemSize) >> temp; //set the value
      mat.data[i][j] = temp;
      in.ignore(); //skip the comma
    }
  }

  return in;
}

// Arithmetic operators
Matrix Matrix::operator+(const Matrix& other) {
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols()) {
    std::cout << "Invalid Matrix dimensions for adding! Returning first matrix." << std::endl;
    return *this;
  }

  for (int i = 0; i < this->getRows(); i++) {
    //Add the two vectors
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
    if (this->getCols() != other.getRows()) {
        std::cout << "Invalid Matrix dimensions for multiplication! Returning first matrix." << std::endl;
        return *this;
    }

    Matrix result(this->getRows(), other.getCols());

    for (int i = 0; i < this->getRows(); i++) {
        for (int j = 0; j < other.getCols(); j++) {
            for (int k = 0; k < this->getCols(); k++) {
                result.data[i][j] += this->data[i][k] * other[k][j];
            }
        }
    }

    for (int i = 0; i < this->getRows(); i++) {
        for (int j = 0; j < other.getCols(); j++) {
          this->data[i][j] = result.data[i][j] > 255 ? 255 : result.data[i][j];
        }
    }

    return result;
}

// Subscript operator
Vector<uint8_t> Matrix::operator[](int index) const {
   if (index > this->getRows()) index = this->getRows() - 1;
   return this->data[index];
}

const Vector<uint8_t>& Matrix::operator[](int index) {
  if (index > this->getRows()) index = this->getRows() - 1;
  return this->data[index];
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

    //Create a copy of this
    Matrix m = *this;

    //Prevent memory leaks
    for (int i = 0; i < this->getRows(); i++) delete[] this->data[i].getElements();

    //create new matrix of the proper sizing, rows become cols and cols become rows.
    *this = Matrix(m.getCols(), m.getRows());

    //transpose the matrix
    for (int i = 0; i < m.getCols(); i++) {
      for (int j = 0; j < m.getRows(); j++) {
        this->data[i][j] = m[j][i];
      }
    }

}
