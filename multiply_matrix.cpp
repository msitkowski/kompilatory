// multiply_matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "string"
#include "iostream"
#include "sstream"
#include "fstream"
#include "ostream"

using namespace std;

class Matrix {
private:
	int rows;
	int cols;
	int **A; // mog¹ byæ double

public:
	Matrix(){};
	Matrix(int, int);
	Matrix(string);
	~Matrix(){}

	int getRows();
	int getCols();
	int** getA();

	void generateMatrixValues();
	void multiplyMatrix(Matrix *, Matrix *);
	void displayMatrix();
	void saveInFile(string);

};

Matrix::Matrix(int n, int m)
{
	this->rows = n;
	this->cols = m;
	this->A = new int*[n];

	int i, j;
	for (i = 0; i<n; i++)
	{
		this->A[i] = new int[m];
		for (j = 0; j<m; j++)
		{
			this->A[i][j] = 0;
		}
	}
}

Matrix::Matrix(string file_name)
{
	ifstream file(file_name.c_str());
	string input;
	getline(file, input, '\n');
	int len = input.find(" ");
	this->rows = atoi(input.substr(0, len).c_str());
	this->cols = atoi(input.substr(len + 1, input.length()).c_str());
	this->A = new int*[this->rows];

	int i, j;
	for (i = 0; i < this->rows; i++)
	{
		getline(file, input, '\n');
		string val;
		this->A[i] = new int[this->cols];
		for (j = 0; j < this->cols; j++)
		{
			len = input.find(" ");
			if (j < this->cols - 1)
			{
				val = input.substr(0, len);
			}
			else
			{
				val = input.substr(0, input.length());
			}
			this->A[i][j] = atoi(val.c_str());
			input.erase(0, len + 1);
		}
	}
	file.close();
}

int Matrix::getRows()
{
	return this->rows;
}

int Matrix::getCols()
{
	return this->cols;
}

int** Matrix::getA()
{
	return this->A;
}

void Matrix::generateMatrixValues()
{
	int i, j;
	for (i = 0; i < this->rows; i++)
	{
		for (j = 0; j < this->cols; j++)
		{
			this->A[i][j] = rand() % 100;
		}
	}
	return;
}

void Matrix::multiplyMatrix(Matrix *A, Matrix *B)
{
	int i, j, k, n;
	n = A->rows;
	for (i = 0; i < A->rows; i++)
	{
		for (j = 0; j < B->cols; j++)
		{
			for (k = 0; k < B->cols; k++)
			{
				this->A[i][j] += A->A[i][k] * B->A[k][j];
			}
		}
	}
	return;
}

void Matrix::displayMatrix()
{
	int i, j;
	for (i = 0; i < this->rows; i++)
	{
		for (j = 0; j < this->cols; j++)
		{
			printf("%d ", this->A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Matrix::saveInFile(string file_name)
{
	ofstream file(file_name.c_str());
	file << this->rows << " " << this->cols << "\n";

	int i, j;
	for (i = 0; i < this->rows; i++)
	{
		string output;
		for (j = 0; j < this->cols; j++)
		{
			stringstream val;
			if (j < this->cols - 1)
			{
				val << this->A[i][j] << " ";
				output += val.str();
			}
			else
			{
				val << this->A[i][j] << "\n";
				output += val.str();
			}
		}
		file << output;
	}
	file.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	//Matrix *m1 = new Matrix(500, 500);
	//m1->generateMatrixValues();
	//m1->saveInFile("matrix1.txt");
	Matrix *m1 = new Matrix("matrix1.txt");
	//m1->displayMatrix();

	//Matrix *m2 = new Matrix(500, 500);
	//m2->generateMatrixValues();
	//m2->saveInFile("matrix2.txt");
	Matrix *m2 = new Matrix("matrix2.txt");
	//m2->displayMatrix();

	Matrix *res = new Matrix(m1->getRows(), m2->getCols());
	res->multiplyMatrix(m1, m2);
	res->displayMatrix();

	getchar();
	return 0;
}