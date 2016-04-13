#include "matrix.h"
#include <iostream>
#include <fstream>
using namespace std;

	int Isclucheniya::FileNotOpen(){ err = 1; cout <<"error_"<< err <<": file not open\n"; return err; }
	int Isclucheniya::Razmery() { err = 2; cout << "error_" << err << ": nevernye razmery\n"; return err; }
	int Isclucheniya::WrongIndex() { err = 3; cout << "error_" << err << ": wrong index\n"; return err; }
	int Isclucheniya::Samoprisvaivanie() { err = 4; cout << "error_" << err << ": samoprisvaivanie\n"; return err; }

	Matrix::Matrix() : n(0), m(0), p(nullptr) {}

	Matrix::Matrix(int _n, int _m) : n(_n), m(_m){
		p = new int*[n];
		for (int i = 0; i < n; i++) { p[i] = new int[m]; }
	}

	Matrix::Matrix(const Matrix &M) : n(M.n), m(M.m) {
		p = new int*[n];
		for (int i = 0; i < n; i++){
			p[i] = new int[m];
			for (int j = 0; j < m; j++)
				p[i][j] = M.p[i][j];
		}
	}

	Matrix::~Matrix()
	{
		if (p != nullptr)
		{
			for (int i = 0; i < n; i++)
			{
				delete[] p[i];
			}
			delete[] p;
		}
	}

	void Matrix::set_matrix(char* a) const{
		ifstream fin;
		fin.open(a);
		if (!fin.is_open()) {
			Isclucheniya E;
			throw E.FileNotOpen();
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++)
				fin >> p[i][j];
		}
	}

	void Matrix::print() const{
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++)
				cout << p[i][j] << " ";
			cout << "\n";
		}
	}

	Matrix Matrix::operator +(const Matrix &M2) const{
		if ((n != M2.n) || (m != M2.m)) {
			Isclucheniya E;
			throw E.Razmery();
		}
		Matrix M_res(M2.n, M2.m);
		for (int i = 0; i < M2.n; i++)
		for (int j = 0; j < M2.m; j++)
			M_res.p[i][j] = p[i][j] + M2.p[i][j];
		cout << "M1+M2:\n";  M_res.print();
		return M_res;
	}
	Matrix Matrix::operator *(const Matrix &M2) const{
		if (m != M2.n){ 
			Isclucheniya E;
			throw E.Razmery();
	}
		Matrix M_res(n, M2.m);
		for (int i = 0; i < n; i++)
		for (int j = 0; j < M2.m; j++)
		{
			M_res.p[i][j] = 0;
			for (int k = 0; k < M2.m; k++)
				M_res.p[i][j] += (p[i][k] * M2.p[k][j]);
		}
		cout << "M1*M2:\n";  M_res.print();
		return M_res;
	}

	int* Matrix::operator [] (int k) const{
		if ((k < 0) || (k >= n)){ Isclucheniya E; throw E.WrongIndex(); }
		int *r = new int[m];
		for (int j = 0; j < m; j++){
			r[j] = p[k][j];
		}
		return r;
	}

	int Matrix::getnumstr() const{
		return n;
	}

	int Matrix::getnumcol() const{
		return m;
	}

	Matrix& Matrix::operator = (const Matrix &M) {
		if (this == &M){
		Isclucheniya E; throw E.Samoprisvaivanie(); 	
		}
			if (p != nullptr){
				for (int i = 0; i < n; i++){
					delete[] p[i];
				}
				delete[] p;
			}
			n = M.n;
			m = M.m;
			p = new int*[n];
			for (int i = 0; i < n; i++){
				p[i] = new int[m];
				for (int j = 0; j < m; j++) { p[i][j] = M.p[i][j]; }
			}
			return *this;
	}

	bool Matrix::operator ==(const Matrix &M2) const{
		if (n != M2.n || m != M2.m)
			return false; 

		for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		if (p[i][j] != M2.p[i][j])
			return false;

		return true; 
	}
