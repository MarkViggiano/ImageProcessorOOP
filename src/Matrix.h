// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdint>
#include "Vector.h"

class Matrix {

protected:
    Vector<Vector<uint8_t>> data;

private:
    int numRows;
    int numCols;

public:
    // Default constructor
    Matrix();

    // Constructor with rows and columns
    Matrix(int rows, int cols);

    // Copy constructor
    Matrix(const Matrix& other);

    // Assignment operator
    Matrix& operator=(const Matrix& other);

    // Destructor
    virtual ~Matrix();

    // Arithmetic operators
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);

    // Subscript operator
    Vector<uint8_t> operator[](int index) const;
    const Vector<uint8_t>& operator[](int index);

    // Number of rows
    int getRows() const;

    //Set number of rows
    void setRows(int rows);

    // Number of columns
    int getCols() const;

    //Set number of columns
    void setColumns(int cols);

    // Transpose function (in-place)
    void transpose();

    // Input stream operator
    friend std::istream& operator>>(std::istream& in, Matrix& mat);

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);

};

#endif // MATRIX_H
