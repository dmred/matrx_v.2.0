#pragma once
#ifndef MATR_H
#define NATR_H
#include "MatrixException.h"
#include <iostream>
#include <cstring> 

template <typename T>
class Matrix;

template <class T>
std::ostream & operator<<(std::ostream & output, const Matrix<T> &);

template <class T>
std::istream & operator>>(std::istream & input, Matrix<T> &);


template <typename T>
class Matrix {
private:
	void swap(Matrix & x);
	T **matrix;
	int columns;
	int rows;

public:
	Matrix() : rows(0), columns(0), matrix(nullptr) {};	// Done
	Matrix(unsigned int n, unsigned int m);					// Done
	Matrix(T **matr, unsigned int _n, unsigned int _m);
	Matrix(Matrix const & x);
	~Matrix();

	unsigned int rowsNumber() const;							// Done
	unsigned int columnsNumber() const;							// Done
	bool readFromFile(char *path);								// Done
	Matrix &operator =(const Matrix& m2);
	Matrix operator +(const Matrix& m2);						// Done
	Matrix operator -(const Matrix& m2);						// Done
	Matrix operator *(double num);								// Done
	Matrix operator *(const Matrix& m2);						// Done
	bool operator ==(const Matrix& m2);						// Done
	T* operator [](unsigned int index);							// Done

	friend std::ostream & operator<< <>(std::ostream & output, const Matrix & matrix);	// Done
	friend std::istream & operator>> <>(std::istream & input, Matrix<T> & matrix);		// Done
};


#include "Matrix.cpp"

