#include "matrix.h"
#include "MatrixException.h"  
#include <string> 
#include <iostream>   
#include <fstream>  
using namespace std;   
 
#ifndef MATR_CPP
#define MATR_CPP

template <typename T>
Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns) : matrix(new T *[_rows]), rows(_rows), columns(_columns) {
	for (int i = 0; i < rows; i++) {
		matrix[i] = new T[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = 0;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix & x) : matrix(new T *[x.rows]), columns(x.columns), rows(x.rows) {
	for (int i = 0; i < rows; i++) {
		matrix[i] = new T[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = x.matrix[i][j];
		}
	}
}

template <typename T>
Matrix<T>::Matrix(T **matr, unsigned int _rows, unsigned int _columns) : matrix(new T *[_rows]), rows(_rows), columns(_columns) {
	for (int i = 0; i < rows; i++) {
		matrix[i] = new T[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = matr[i][j];
		}
	}
}
template <typename T>
bool Matrix<T>::readFromFile(char* path) {
	ifstream stream;
	try {
		stream.open(path);

		if (stream.is_open()) {
			unsigned int rows, columns;

			stream >> rows >> columns;
			T **mass = new T*[rows];
			for (int i = 0; i < rows; i++) {
				mass[i] = new T[columns];
				for (int j = 0; j < columns; j++) {
					stream >> mass[i][j];
				}
			}

			this->matrix = mass;
			this->rows = rows;
			this->columns = columns;
			stream.close();

			return true;
		}
		else {
			throw initException();
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return false;
	}
	return false;
}

template <typename T>
unsigned int Matrix<T>::rowsNumber() const {
	return rows;
}

template <typename T>
unsigned int Matrix<T>::columnsNumber() const {
	return columns;
}

template <typename T>
Matrix<T> & Matrix<T>::operator =(const Matrix<T>& m2) {
	if (this != &m2) {
		(Matrix(m2)).swap(*this);
	}
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator +(const Matrix<T> &m2) {
	if (m2.columns != this->columns || m2.rows != this->rows) {
		throw incompatibleException();
	}
	Matrix temp(this->rows, this->columns);
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			temp[i][j] = m2.matrix[i][j] + this->matrix[i][j];
		}
	}
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(const Matrix<T> &m2) {
	if (m2.columns != this->columns || m2.rows != this->rows) {
		throw incompatibleException();
	}
	Matrix temp(this->rows, this->columns);
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			temp.matrix[i][j] = matrix[i][j] - m2.matrix[i][j];
		}
	}
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(double num) {
	if (this->matrix == nullptr || this->rows == 0 || this->columns == 0) {
		throw emptyException();
	}
	Matrix temp(this->rows, this->columns);
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			temp.matrix[i][j] = this->matrix[i][j] * num;
		}
	}
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(const Matrix &m2) {
	if (this->columns != m2.rows) {
		throw incompatibleException();
	}
	Matrix temp(this->rows, m2.columns);

	T t = 0;

	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < m2.columns; col++) {
			t = 0;
			for (int inner = 0; inner < this->columns; inner++) {
				t = t + this->matrix[row][inner] * m2.matrix[inner][col];
			}
			temp.matrix[row][col] = t;
		}
	}
	return temp;
}

template <typename T>
bool Matrix<T>::operator ==(const Matrix & m2) {
	if (rows != m2.rows || columns != m2.columns) {
		return false;
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (matrix[i][j] != m2.matrix[i][j]) {
				return false;
			}
		}
	}

	return true;
}

template <typename T>
T* Matrix<T>::operator [](unsigned int index) {
	if (index < 0 || index > this->rows) {
		throw indexException();
	}
	if (rows == 0 || matrix == nullptr) {
		throw emptyException();
	}

	return this->matrix[index];
}

template <typename T>
void Matrix<T>::swap(Matrix & x) {
	std::swap(x.matrix, matrix);
	std::swap(x.columns, columns);
	std::swap(x.rows, rows);
}

template <typename T>
Matrix<T>::~Matrix() {
	if (matrix != nullptr) {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}

template <typename T>
std::ostream & operator <<(std::ostream & os, const Matrix<T> & x) {
	if (x.columns == 0 || x.rows == 0 || x.matrix == nullptr) {
		throw emptyException();
	}
	for (int i = 0; i < x.rows; ++i) {
		for (int j = 0; j < x.columns; ++j) {
			os.width(4);
			os << x.matrix[i][j];
		}
		os << std::endl;
	}

	return os;
}

template <typename T>
std::istream & operator >>(std::istream & input, Matrix<T> & matrix) {
	for (int i = 0; i < matrix.rows; ++i) {
		for (int j = 0; j < matrix.columns; ++j) {
		
				if (!(input >> matrix.matrix[i][j])) {
					throw initException();
				}
			
			
		}
	}

	return input;
}
