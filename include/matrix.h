#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

class Isclucheniya {
public:
	int FileNotOpen();
	int Razmery();
	int WrongIndex();
	int Samoprisvaivanie();
private:
	int err;	
};

class Matrix{
	
public:
	Matrix();
	Matrix(int _n, int _m);
	Matrix(const Matrix &M);
	~Matrix();
	void set_matrix(char* a) const;
	void print() const;
	Matrix operator +(const Matrix &M2) const;
	Matrix operator *(const Matrix &M2) const;
	int* operator [] (int k) const;
	int getnumstr() const;
	int getnumcol() const;
	Matrix& operator = (const Matrix &M);
	bool operator ==(const Matrix &M2) const;

private:
	int n;
	int m;
	int **p;

};

#endif
