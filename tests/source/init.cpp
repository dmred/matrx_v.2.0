#include "matrix.h"
#include <catch.hpp>

SCENARIO("Matrix init", "[init]") {
	GIVEN("The number of rows and columns") {
		auto rows = 3;
		auto columns = 3;
		WHEN("Create instansce of Matrix") {
			Matrix<int> m(rows, columns);
			Matrix<int> a;
			THEN("The number of rows and columns must be preserved") {
				REQUIRE(m.rowsNumber() == rows);
				REQUIRE(m.columnsNumber() == columns);
				REQUIRE(a.rowsNumber() == 0);
				REQUIRE(a.columnsNumber() == 0);
			}
		}
	}
}

SCENARIO("Matrix: operator +", "[addition]") {
	Matrix<int> A, B, expected;
	A.readFromFile("A2x2.txt");
	B.readFromFile("B2x2.txt");
	expected.readFromFile("A+B.txt");

	Matrix<int> result = A + B;
	REQUIRE(result == expected);
} 












SCENARIO("Matrix: operator *(matix, matrix)", "[multiplication]") {
	Matrix<int> A, B, expected;
	A.readFromFile("A2x2.txt");
	B.readFromFile("B2x2.txt");
	expected.readFromFile("A*B.txt");

	Matrix<int> result = A * B;
	REQUIRE(result == expected);
}

SCENARIO("Matrix: operator [](index)", "[get row]") {
	Matrix<int> A;
	int* a = new int[2]; a[0] = 1; a[1] = 2;
	A.readFromFile("A2x2.txt");

	bool flag = true;
	int* res = A[0];
	for (int i = 0; i < 2; i++) {
		if (a[i] != res[i]) {
			flag = false;
		}
	}
	REQUIRE(flag);
}

SCENARIO("Matrix: operator ==", "[equal]") {
	Matrix<int> A, B;
	A.readFromFile("A2x2.txt");
	B.readFromFile("A2x2.txt");
	bool flag = (A == B);

	REQUIRE(flag);
}

SCENARIO("Matrix: rowsNumber()", "[rows number]") {
	Matrix<int> A(3, 3);

	REQUIRE(A.rowsNumber() == 3);
}

SCENARIO("Matrix: columnsNumber()", "[columns number]") {
	Matrix<int> A(3, 3);

	REQUIRE(A.columnsNumber() == 3);
}

SCENARIO("Matrix: readFromFile()", "[filling]") {
	Matrix<int> A;
	int** a = new int*[2];
	int *row;
	for (int i = 0; i < 2; i++) {
		a[i] = new int[2];
	}
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	A.readFromFile("A2x2.txt");

	bool flag = true;
	for (int i = 0; i < 2; i++) {
		row = A[i];
		for (int j = 0; j < 2; j++) {
			if (a[i][j] != row[j]) {
				flag = false;
			}
		}
	}

	REQUIRE(flag);
}

SCENARIO("Matrix operator >>", "[fill]") {
	std::ifstream input("A2.txt");
	Matrix<int> A(2, 2);
	REQUIRE(input >> A);
	REQUIRE(A[0][0] == 1);
	REQUIRE(A[0][1] == 2);
	REQUIRE(A[1][0] == 3);
	REQUIRE(A[1][1] == 4);
}

SCENARIO("Matrix operator <<", "[print]") {
	std::ifstream input("A2.txt");
	fstream out; out.open("A2.txt");
	ifstream secondInput("A2.txt");
	Matrix<int> A(2, 2);
	input >> A;
	REQUIRE(out << A);
	REQUIRE(secondInput >> A);
	out.close();
	input.close();
	secondInput.close();
	REQUIRE(A[0][0] == 1);
	REQUIRE(A[0][1] == 2);
	REQUIRE(A[1][0] == 3);
	REQUIRE(A[1][1] == 4);
}

SCENARIO("MatrixException: init matrix", "[init]") {
	bool flag = false;
	Matrix<int> A;
	try {
		A.readFromFile("11111");
	}
	catch (initException &e) {
		flag = true;
	}
	REQUIRE(flag);
}

SCENARIO("MatrixException: empty matrix", "[empty]") {
	bool flag = false;
	Matrix<int> A;
	try {
		cout << A;
	}
	catch (emptyException &e) {
		flag = true;
	}
	REQUIRE(flag);
}

SCENARIO("MatrixException: index error", "[index]") {
	bool flag = false;
	Matrix<int> A(2, 2);
	try {
		int* a = A[3];
	}
	catch (indexException &e) {
		flag = true;
	}
	REQUIRE(flag);
}

SCENARIO("MatrixException: incompatible matrixes", "[size]") {
	bool flag = false;
	Matrix<int> A(2, 2), B(3, 3);
	try {
		A + B;
	}
	catch (incompatibleException &e) {
		flag = true;
	}
	REQUIRE(flag);
}

SCENARIO("Matrix: operator + for double", "[addition]") {
	Matrix<double> A, B, expected;
	A.readFromFile("A2x2.txt");
	B.readFromFile("B2x2.txt");
	expected.readFromFile("A+B.txt");

	Matrix<double> result = A + B;
	REQUIRE(result == expected);
}
