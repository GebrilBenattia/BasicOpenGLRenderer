#include "MatrixNM.hpp"
#include <cassert>
#define _USE_MATH_DEFINES
#include "math.h"
#include <iostream>

Matrix::Matrix()
{

}

Matrix::Matrix(const int rows, const int column, float value)
{
	this->column = column;
	this->rows = rows;
	for (int i = 0; i < this->rows; i++) {
		std::vector<float> v;
		for (int j = 0; j < this->column; j++) {
			v.push_back(value);
		}
		matrixData.push_back(v);
	}
}

Matrix::Matrix(const int rows, const int column, std::vector<std::vector<float>> values)
{
	this->column = column;
	this->rows = rows;
	for (int i = 0; i < this->rows; i++) {
		std::vector<float> v;
		for (int j = 0; j < this->column; j++) {
			v.push_back(values[i][j]);
		}
		matrixData.push_back(v);
	}
}
/*
Matrix::Matrix(const std::initializer_list<const std::initializer_list<float>>& data)
{
	this->column = column;
	this->rows = data.size();



	for (int i = 0; i < this->rows; i++) {
		std::vector<float> v;
		const float* subData = data.begin()[i].begin();

		for (int j = 0; j < this->column; j++) {
			v.push_back(subData[j]);
		}
		matrixData.push_back(v);
	}
}
*/

Vector Matrix::Diag()
{
	int id = std::min(rows, column);
	//int id = (rows > column) ? rows - 1 : rows; //first thing I tried to avoid making the vector out of range
	std::vector<float> v;
	for (int i = 0; i < id; i++) {
			v.push_back(matrixData[i][i]);
	}
	return Vector(id, v);
}

float Matrix::Trace()
{
	float result = 0;
	const Vector diag = Diag();
	for (int i = 0; i < diag.vectorData.size(); i++) {
		result += diag.vectorData[i];
	}
	return result;
}

Matrix Matrix::Opp()
{
	Matrix opp(rows, column, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < column; j++) {
			opp.matrixData[i][j] = -matrixData[i][j];
		}
	}
	return opp;
}

Matrix Matrix::Transpose()
{
	Matrix transpose(column, rows, 0);
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < rows; j++) {
			transpose.matrixData[i][j] = matrixData[j][i];
		}
	}
	return transpose;
}

bool Matrix::IsSquare()
{
	if (rows == column)
		return true;
	else
		return false;
}

bool Matrix::IsDiagonal()
{
	assert(this->IsSquare() && "Matrix isn't square");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < column; j++) {
			if (matrixData[i][j] == 0 && matrixData[i][i] != 0) {
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

Matrix Matrix::Add(const Matrix& m, const Matrix& m2)
{
	assert(m.rows == m2.rows && m.column == m2.column && "Matrix does not have the same dimensions");

	Matrix add(m.rows, m.column, 0);
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.column; j++) {
			add.matrixData[i][j] += m.matrixData[i][j] + m2.matrixData[i][j];
		}
	}
	return add;
}

Matrix Matrix::MultiplyBy(const Matrix& m, const float f)
{
	Matrix multiply(m.rows, m.column, 0);
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.column; j++) {
			multiply.matrixData[i][j] += m.matrixData[i][j] * f;
		}
	}
	return multiply;
}

Matrix Matrix::MultiplyBy(const Matrix& m, const Matrix& m2)
{
	assert(m.column == m2.rows && "Left matrix column not equals to Right matrix rows");

	int id = std::max(m.column, m2.rows); // taking the maximum value assuming that the rows and m.columns are equals so we can use them as arrays index to calculate the multiplied matrix, these values are supposed to be equals
	Matrix multiply(m.rows, m2.column, 0);
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m2.column; j++) {
			for (int k = 0; k < id; k++) {
				multiply.matrixData[i][j] += m.matrixData[i][k] * m2.matrixData[k][j];
			}
		}
	}
	return multiply;
}

float Matrix::Determinant(const Matrix& m)
{
	assert(m.column == m.rows && "Can't do the determinant of a non-square matrix");

	if (m.rows == 2 && m.column == 2) {
		float result = 0;
		result += m.matrixData[0][0] * m.matrixData[1][1] - m.matrixData[1][0] * m.matrixData[0][1];
		return result;
	}

	float currentDet = 0;
	for (int i = 0; i < m.rows; i++) {
		std::vector<std::vector<float>> det;
		for (int j = 0; j < m.rows; j++) {
			if (j != i) {
				std::vector<float> row;
				for (int w = 1; w < m.column; w++) {
					row.push_back(m.matrixData[i][w]);
				}
				det.push_back(row);
			}
		}
		Matrix mat(det.size(), det[0].size(), det);
		if (i % 2 == 0) {
			currentDet += m.matrixData[i][1] * Matrix::Determinant(mat);
		}
		else
			currentDet -= m.matrixData[i][1] * Matrix::Determinant(mat);
		return currentDet;
	}

	return false;
}

Matrix Matrix::PivotGaussJordan(const Matrix& m)
{
	Matrix mat = m;
	int r = 0;
	for (int j = 0; j < mat.column; j++) {
		int k = 0;
		float maxValue = 0;
		float pivot = 0;

		for (int i = r; i < mat.rows; i++) {
			if (fabs(mat.matrixData[i][j]) > maxValue) {
				maxValue = fabs(mat.matrixData[i][j]);
				k = i;
				pivot = mat.matrixData[i][j];
			}
		}
		if (pivot != 0) {
			for (int o = r; o < mat.column; o++) {
				mat.matrixData[k][o] /= pivot;
			}
			if (k != r) {
				std::swap(mat.matrixData[r], mat.matrixData[k]);
			}
			for (int p = 0; p < mat.rows; p++) {
				if (p != r) {
					float value = mat.matrixData[p][j];

					for (int u = j; u < mat.column; u++) {
							mat.matrixData[p][u] -= value * mat.matrixData[r][u];
					}
				}
			}
			r++;
		}
	}
	return mat;
}

Matrix Matrix::Augment(const Matrix& m)
{
	Matrix temp(rows, column + m.column, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < temp.column; j++) {
			if (j < column) {
				temp.matrixData[i][j] = matrixData[i][j];
			}
			else {
				temp.matrixData[i][j] = m.matrixData[i][j-column];
			}
		}
	}
	return temp;
}

Matrix Matrix::Identity(int size)
{
	Matrix temp(size, size, 0);
	for (int i = 0; i < size; i++) {
		temp.matrixData[i][i] = 1;
	}

	return temp;
}

Matrix Matrix::Inverse(Matrix& m)
{
	Matrix mat = m.Augment(Matrix::Identity(m.rows));
	Matrix temp = Matrix::PivotGaussJordan(mat);
	Matrix result(m.rows, m.rows, 0);
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.column; j++) {
			result.matrixData[i][j] = temp.matrixData[i][j+m.column];
		}
	}
	return result;
}

Matrix Matrix::Rotation2D(const float angle)
{
	float sinRotation = (angle < 0) ? std::sin(angle) : -std::sin(angle);
	return Matrix (2, 2, { 
		{std::cos(angle), -sinRotation},
		{sinRotation, std::cos(angle)}
		});
}

Matrix Matrix::Scaling2D(const Vector& v)
{
	return Matrix(2, 2,{
		{v.vectorData[0],0},
		{0, v.vectorData[1]}
	});
}

Matrix Matrix::Rotation3D(const float angle, const Vector& v)
{
	const float cos = std::cos(angle);
	const float sin = std::sin(angle);
	const float c = 1 - cos;

	const float r00 = v.vectorData[0] * v.vectorData[0] * c + cos;
	const float r01 = v.vectorData[0] * v.vectorData[1] * c + v.vectorData[2] * sin;
	const float r02 = v.vectorData[0] * v.vectorData[2] * c - v.vectorData[1] * sin;

	const float r10 = v.vectorData[1] * v.vectorData[0] * c - v.vectorData[2] * sin;
	const float r11 = v.vectorData[1] * v.vectorData[1] * c + cos;
	const float r12 = v.vectorData[1] * v.vectorData[2] * c + v.vectorData[0] * sin;

	const float r20 = v.vectorData[2] * v.vectorData[0] * c + v.vectorData[1] * sin;
	const float r21 = v.vectorData[2] * v.vectorData[1] * c - v.vectorData[0] * sin;
	const float r22 = v.vectorData[2] * v.vectorData[2] * c + cos;

	return Matrix(3, 3, {
		{r00,r01,r02},
		{r10,r11,r12},
		{r20,r21,r22}
		});
}

Matrix Matrix::Scaling3D(const Vector& v)
{
	return Matrix(3, 3, {
		{v.vectorData[0], 0, 0},
		{0, v.vectorData[1], 0},
		{0, 0, v.vectorData[2]}
		});
}

Matrix Matrix::TRS(Vector translate, Vector angle, Vector scale)
{
	Matrix T(4, 4, {
		{0,0,0,translate.vectorData[0]},
		{0,0,0,translate.vectorData[1]},
		{0,0,0,translate.vectorData[2]},
		{0,0,0,1}
		});

	Matrix S(4, 4, {
		{scale.vectorData[0],0,0,0},
		{0,scale.vectorData[1],0,0},
		{0,0,scale.vectorData[2],0},
		{0,0,0,1}
		});

	Matrix Rx = Matrix::Rotation3D(angle.vectorData[0], Vector(3, { 1,0,0 }));

	Matrix Ry = Matrix::Rotation3D(angle.vectorData[1], Vector(3, { 0,1,0 }));

	Matrix Rxy = Matrix::MultiplyBy(Ry, Rx);

	Matrix Rz = Matrix::Rotation3D(angle.vectorData[2], Vector(3, { 0,0,1}));

	Matrix Rxyz = Matrix::MultiplyBy(Rz, Rxy);

	Matrix Rotation(4, 4, {
		{Rxyz.matrixData[0][0],Rxyz.matrixData[0][1],Rxyz.matrixData[0][2],0},
		{Rxyz.matrixData[1][0],Rxyz.matrixData[1][1],Rxyz.matrixData[1][2],0},
		{Rxyz.matrixData[2][0],Rxyz.matrixData[2][1],Rxyz.matrixData[2][2],0},
		{0,0,0,1}
		});

	return Matrix::MultiplyBy(Rotation,S);
}

Matrix::~Matrix()
{

}
/*
std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; i++) {
		os << "[ ";
		for (int j = 0; j < matrix.column; j++){
			os << matrix.matrixData[i][j];
			if (j != matrix.column - 1) {
				os << ", ";
			}
		}
		os << " ]\n";
	}
	return os;
}
*/