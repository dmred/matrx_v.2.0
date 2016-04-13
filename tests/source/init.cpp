#include <matrix.h>
#include <catch.hpp>
#include <fstream>
#include <iostream>
using namespace std;

SCENARIO("Matrix init", "[init]") {

	GIVEN("The number of rows and columns") {

		auto rows = 3;
		auto columns = 3;

		WHEN("Create instansce of Matrix") {
			Matrix matrix(rows, columns);
			THEN("The number of rows and columns must be preserved") {

				REQUIRE(matrix.getnumstr() == rows);
				REQUIRE(matrix.getnumcol() == columns);
			}
		}
	}
}

SCENARIO("Iscl_set", "[set]"){
	int O=0;
	Matrix A(2,2);
	try{
	A.set_matrix("Avada_Kedavra.txt");
	}
	catch(...){O++;}
	REQUIRE(O==1);
}

SCENARIO("Matrix +", "[summ]") {
	Matrix A(2, 2);
	A.set_matrix("A2x2.txt");
	Matrix B(2, 2);
	B.set_matrix("B2x2.txt");
	Matrix expected(2, 2);
	expected.set_matrix("A+B2x2.txt");
	Matrix result = A + B;
	REQUIRE(result == expected);
}

SCENARIO("Iscl_martrix +","[summ]"){
	int O=0;
	Matrix A(1, 2);
	A.set_matrix("A2x2.txt");
	Matrix B(2, 2);
	B.set_matrix("B2x2.txt");	
	try{
		A+B;
	}
	catch (...) {O++;}
	REQUIRE(O==1);
}

SCENARIO("Matrix *", "[mult]") {
	Matrix A(2, 2);
	A.set_matrix("A2x2.txt");
	Matrix B(2, 2);
	B.set_matrix("B2x2.txt");
	Matrix expected(2, 2);
	expected.set_matrix("A*B2x2.txt");
	Matrix result = A * B;
	REQUIRE(result == expected);
}

SCENARIO("Iscl_martrix *","[mult]"){
	int O=0;
	Matrix A(2, 2);
	A.set_matrix("A2x2.txt");
	Matrix B(1, 2);
	B.set_matrix("B2x2.txt");	
	try{
		A*B;
	}
	catch (...) {O++;}
	REQUIRE(O==1);
}

SCENARIO("Matrix: operator ==", "[equal]") {
	Matrix A, B;
	A.set_matrix("A2x2.txt");
	B.set_matrix("A2x2.txt");
	bool f = (A == B);
	REQUIRE(f);
}

SCENARIO("Matrix operator [](int)", "[s]") 
{
	Matrix A(2,2);
	A.set_matrix("A2x2.txt");
	int* s = A[1];
	REQUIRE(s[0]==1);
	REQUIRE(s[1]==1);
}

SCENARIO("Iscl_[]", "[s]"){
	int O=0;
	Matrix A(2,2);
	A.set_matrix("A2x2.txt");
	try{
		int* s = A[5];
	}
	catch(...){O++;}
	REQUIRE(O==1);
}

SCENARIO("samoprisv", "="){
	int O=0;
	Matrix A(2,2);
	A.set_matrix("A2x2.txt");
	try{
		A=A;
	}
	catch(...){O++;}
	REQUIRE(O==1);
}
