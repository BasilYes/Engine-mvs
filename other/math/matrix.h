#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H
#include <cmath>
#include "vector.h"

template <class Type, int sizeX, int sizeY>
struct matrix
{
	Type data[sizeX][sizeY];
	
	inline Type* operator[](const int a)
	{
		return data[a];
	}
};

//operator*  matrix * vector ----------------------------------------------------------------------------------------------------------------
template <typename Type, int sizeX>
vector<Type, sizeX> operator*(const matrix<Type, sizeX, 3>& left, const vector<Type, 3>& right)
{
	vector<Type, sizeX> out{};

	for (unsigned int x = 0; x < sizeX; x++) {
		out.data[x] =
			left.data[x][0] * right.data[0] +
			left.data[x][1] * right.data[1] +
			left.data[x][2] * right.data[2];
	}

	return out;
}

template <typename Type, int sizeX>
vector<Type, sizeX> operator*(const matrix<Type, sizeX, 4>& left, const vector<Type, 4>& right)
{
	vector<Type, sizeX> out{};

	for (unsigned int x = 0; x < sizeX; x++) {
		out.data[x] =
			left.data[x][0] * right.data[0] +
			left.data[x][1] * right.data[1] +
			left.data[x][2] * right.data[2] +
			left.data[x][3] * right.data[3];
	}

	return out;
}

template <typename Type, int sizeX, int sizeY>
vector<Type, sizeX> operator*(const matrix<Type, sizeX, sizeY>& left, const vector<Type, sizeY>& right)
{
	vector<Type, sizeX> out;

	for (unsigned int x = 0; x < sizeX; x++) {
		out.data[x] = left.data[x][0] * right.data[0];
		for (unsigned int y = 1; y < sizeY; y++) {
			out.data[x] += left.data[x][y] * right.data[y];
		}
	}

	return out;
}

//operator*  matrix * matrix ----------------------------------------------------------------------------------------------------------------
template <typename Type, int sizeX, int rSize>
matrix<Type, sizeX, rSize> operator*(const matrix<Type, sizeX, 3>& left, const matrix<Type, 3, rSize>& right)
{
	matrix<Type, sizeX, rSize> out;

	for (unsigned int x = 0; x < sizeX; x++) {
		for (unsigned int y = 0; y < rSize; y++) {
			out.data[x][y] =
				left.data[x][0] * right.data[0][y] +
				left.data[x][1] * right.data[1][y] +
				left.data[x][2] * right.data[2][y];
		}
	}

	return out;
}

template <typename Type, int sizeX, int rSize>
matrix<Type, sizeX, rSize> operator*(const matrix<Type, sizeX, 4>& left, const matrix<Type, 4, rSize>& right)
{
	matrix<Type, sizeX, rSize> out;

	for (unsigned int x = 0; x < sizeX; x++) {
		for (unsigned int y = 0; y < rSize; y++) {
			out.data[x][y] =
				left.data[x][0] * right.data[0][y] +
				left.data[x][1] * right.data[1][y] +
				left.data[x][2] * right.data[2][y] +
				left.data[x][3] * right.data[3][y];
		}
	}

	return out;
}

template <typename Type, int sizeX, int sizeY, int rSize>
matrix<Type, sizeX, rSize> operator*(const matrix<Type, sizeX, sizeY>& left, const matrix<Type, sizeY, rSize>& right)
{
	matrix<Type, sizeX, rSize> out;

	for (unsigned int x = 0; x < sizeX; x++) {
		for (unsigned int y = 0; y < rSize; y++) {
			out.data[x][y] = left.data[x][0] * right.data[0][y];;
			for (unsigned int i = 1; i < sizeY; i++) {
				out.data[x][y] += left.data[x][i] * right.data[i][y];
			}
		}
	}

	return out;
}




//math to mat 3x3 -----------------------------------------------------------------------------------------------------
template <typename Type>
void initScaleTransform(matrix<Type, 3, 3>& mat, const vector<Type, 3>& scale)
{
	mat.data[0][0] = scale.data[0]; mat.data[0][1] = 0.0f;          mat.data[0][2] = 0.0f;
	mat.data[1][0] = 0.0f;		    mat.data[1][1] = scale.data[1]; mat.data[1][2] = 0.0f;
	mat.data[2][0] = 0.0f;          mat.data[2][1] = 0.0f;          mat.data[2][2] = scale.data[2];
}

template <typename Type>
void initRotateTransform(matrix<Type, 3, 3>& mat, const vector<Type, 3>& rotate)
{
	matrix<Type, 3, 3> rx, ry, rz;

	rx.data[0][0] = 1.0f; rx.data[0][1] = 0.0f;                rx.data[0][2] = 0.0f;
	rx.data[1][0] = 0.0f; rx.data[1][1] = cos(rotate.data[0]); rx.data[1][2] = -sin(rotate.data[0]);
	rx.data[2][0] = 0.0f; rx.data[2][1] = sin(rotate.data[0]); rx.data[2][2] = cos(rotate.data[0]);

	ry.data[0][0] = cos(rotate.data[1]); ry.data[0][1] = 0.0f; ry.data[0][2] = -sin(rotate.data[1]);
	ry.data[1][0] = 0.0f;                ry.data[1][1] = 1.0f; ry.data[1][2] = 0.0f;
	ry.data[2][0] = sin(rotate.data[1]); ry.data[2][1] = 0.0f; ry.data[2][2] = cos(rotate.data[1]);

	rz.data[0][0] = cos(rotate.data[2]); rz.data[0][1] = -sin(rotate.data[2]); rz.data[0][2] = 0.0f;
	rz.data[1][0] = sin(rotate.data[2]); rz.data[1][1] = cos(rotate.data[2]);  rz.data[1][2] = 0.0f;
	rz.data[2][0] = 0.0f;			     rz.data[2][1] = 0.0f;                 rz.data[2][2] = 1.0f;

	mat = rz * ry * rx;
}

template <typename Type>
void initRotateTransformT(matrix<Type, 3, 3>& mat, const vector<Type, 3>& rotate)
{
	matrix<Type, 3, 3> rx, ry, rz;

	rx.data[0][0] = 1.0f; rx.data[0][1] = 0.0f;                 rx.data[0][2] = 0.0f;
	rx.data[1][0] = 0.0f; rx.data[1][1] = cos(rotate.data[0]);  rx.data[1][2] = sin(rotate.data[0]);
	rx.data[2][0] = 0.0f; rx.data[2][1] = -sin(rotate.data[0]); rx.data[2][2] = cos(rotate.data[0]);

	ry.data[0][0] = cos(rotate.data[1]);  ry.data[0][1] = 0.0f; ry.data[0][2] = sin(rotate.data[1]);
	ry.data[1][0] = 0.0f;                 ry.data[1][1] = 1.0f; ry.data[1][2] = 0.0f;
	ry.data[2][0] = -sin(rotate.data[1]); ry.data[2][1] = 0.0f; ry.data[2][2] = cos(rotate.data[1]);

	rz.data[0][0] = cos(rotate.data[2]);  rz.data[0][1] = sin(rotate.data[2]); rz.data[0][2] = 0.0f;
	rz.data[1][0] = -sin(rotate.data[2]); rz.data[1][1] = cos(rotate.data[2]); rz.data[1][2] = 0.0f;
	rz.data[2][0] = 0.0f;			      rz.data[2][1] = 0.0f;                rz.data[2][2] = 1.0f;

	mat = rz * ry * rx;
}

//math to mat 4x4 -------------------------------------------------------------------------------------------------------------------
template <typename Type>
void initPersProjTransform(matrix<Type, 4, 4>& mat, Type FOV, Type Width, Type Height, Type zNear, Type zFar) // FOV in radian
{
	const Type ar = Width / Height;
	const Type zRange = zNear - zFar;
	const Type tanHalfFOV = tan(FOV / 2.0f);

	mat.data[0][0] = 1.0f / (tanHalfFOV * ar); mat.data[0][1] = 0.0f;              mat.data[0][2] = 0.0f;                     mat.data[0][3] = 0.0;
	mat.data[1][0] = 0.0f;                     mat.data[1][1] = 1.0f / tanHalfFOV; mat.data[1][2] = 0.0f;                     mat.data[1][3] = 0.0;
	mat.data[2][0] = 0.0f;                     mat.data[2][1] = 0.0f;              mat.data[2][2] = (-zNear - zFar) / zRange; mat.data[2][3] = 2.0f * zFar * zNear / zRange;
	mat.data[3][0] = 0.0f;                     mat.data[3][1] = 0.0f;              mat.data[3][2] = 1.0f;                     mat.data[3][3] = 0.0;
}

template <typename Type>
void initPersProjTransformT(matrix<Type, 4, 4>& mat, Type FOV, Type Width, Type Height, Type zNear, Type zFar) // FOV in radian
{
	const Type ar = Width / Height;
	const Type zRange = zNear - zFar;
	const Type tanHalfFOV = tan(FOV / 2.0f);

	mat.data[0][0] = 1.0f / (tanHalfFOV * ar); mat.data[0][1] = 0.0f;              mat.data[0][2] = 0.0f;                         mat.data[0][3] = 0.0;
	mat.data[1][0] = 0.0f;                     mat.data[1][1] = 1.0f / tanHalfFOV; mat.data[1][2] = 0.0f;                         mat.data[1][3] = 0.0;
	mat.data[2][0] = 0.0f;                     mat.data[2][1] = 0.0f;              mat.data[2][2] = (-zNear - zFar) / zRange;     mat.data[2][3] = 1.0f;
	mat.data[3][0] = 0.0f;                     mat.data[3][1] = 0.0f;              mat.data[3][2] = 2.0f * zFar * zNear / zRange; mat.data[3][3] = 0.0;
}

template <typename Type>
void initScaleTransform(matrix<Type, 4, 4>& mat, const vector<Type, 3>& scale)
{
	mat.data[0][0] = scale.data[0]; mat.data[0][1] = 0.0f;          mat.data[0][2] = 0.0f;          mat.data[0][3] = 0.0f;
	mat.data[1][0] = 0.0f;		   mat.data[1][1] = scale.data[1]; mat.data[1][2] = 0.0f;          mat.data[1][3] = 0.0f;
	mat.data[2][0] = 0.0f;          mat.data[2][1] = 0.0f;          mat.data[2][2] = scale.data[2]; mat.data[2][3] = 0.0f;
	mat.data[3][0] = 0.0f;          mat.data[3][1] = 0.0f;          mat.data[3][2] = 0.0f;          mat.data[3][3] = 1.0f;
}

template <typename Type>
void initRotateTransform(matrix<Type, 4, 4>& mat, const vector<Type, 3>& rotate)
{
	matrix<Type, 4, 4> rx, ry, rz;

	rx.data[0][0] = 1.0f; rx.data[0][1] = 0.0f;                rx.data[0][2] = 0.0f;                 rx.data[0][3] = 0.0f;
	rx.data[1][0] = 0.0f; rx.data[1][1] = cos(rotate.data[0]); rx.data[1][2] = -sin(rotate.data[0]); rx.data[1][3] = 0.0f;
	rx.data[2][0] = 0.0f; rx.data[2][1] = sin(rotate.data[0]); rx.data[2][2] = cos(rotate.data[0]);  rx.data[2][3] = 0.0f;
	rx.data[3][0] = 0.0f; rx.data[3][1] = 0.0f;                rx.data[3][2] = 0.0f;                 rx.data[3][3] = 1.0f;

	ry.data[0][0] = cos(rotate.data[1]); ry.data[0][1] = 0.0f; ry.data[0][2] = -sin(rotate.data[1]); ry.data[0][3] = 0.0f;
	ry.data[1][0] = 0.0f;                ry.data[1][1] = 1.0f; ry.data[1][2] = 0.0f;                 ry.data[1][3] = 0.0f;
	ry.data[2][0] = sin(rotate.data[1]); ry.data[2][1] = 0.0f; ry.data[2][2] = cos(rotate.data[1]);  ry.data[2][3] = 0.0f;
	ry.data[3][0] = 0.0f;                ry.data[3][1] = 0.0f; ry.data[3][2] = 0.0f;                 ry.data[3][3] = 1.0f;

	rz.data[0][0] = cos(rotate.data[2]); rz.data[0][1] = -sin(rotate.data[2]); rz.data[0][2] = 0.0f; rz.data[0][3] = 0.0f;
	rz.data[1][0] = sin(rotate.data[2]); rz.data[1][1] = cos(rotate.data[2]);  rz.data[1][2] = 0.0f; rz.data[1][3] = 0.0f;
	rz.data[2][0] = 0.0f;			     rz.data[2][1] = 0.0f;                 rz.data[2][2] = 1.0f; rz.data[2][3] = 0.0f;
	rz.data[3][0] = 0.0f;                rz.data[3][1] = 0.0f;                 rz.data[3][2] = 0.0f; rz.data[3][3] = 1.0f;

	mat = rz * ry * rx;
}

template <typename Type>
void initRotateTransformT(matrix<Type, 4, 4>& mat, const vector<Type, 3>& rotate)
{
	matrix<Type, 4, 4> rx, ry, rz;

	rx.data[0][0] = 1.0f; rx.data[0][1] = 0.0f;                 rx.data[0][2] = 0.0f;                rx.data[0][3] = 0.0f;
	rx.data[1][0] = 0.0f; rx.data[1][1] = cos(rotate.data[0]);  rx.data[1][2] = sin(rotate.data[0]); rx.data[1][3] = 0.0f;
	rx.data[2][0] = 0.0f; rx.data[2][1] = -sin(rotate.data[0]); rx.data[2][2] = cos(rotate.data[0]); rx.data[2][3] = 0.0f;
	rx.data[3][0] = 0.0f; rx.data[3][1] = 0.0f;                 rx.data[3][2] = 0.0f;                rx.data[3][3] = 1.0f;

	ry.data[0][0] = cos(rotate.data[1]);  ry.data[0][1] = 0.0f; ry.data[0][2] = sin(rotate.data[1]); ry.data[0][3] = 0.0f;
	ry.data[1][0] = 0.0f;                 ry.data[1][1] = 1.0f; ry.data[1][2] = 0.0f;                ry.data[1][3] = 0.0f;
	ry.data[2][0] = -sin(rotate.data[1]); ry.data[2][1] = 0.0f; ry.data[2][2] = cos(rotate.data[1]); ry.data[2][3] = 0.0f;
	ry.data[3][0] = 0.0f;                 ry.data[3][1] = 0.0f; ry.data[3][2] = 0.0f;                ry.data[3][3] = 1.0f;

	rz.data[0][0] = cos(rotate.data[2]);  rz.data[0][1] = sin(rotate.data[2]); rz.data[0][2] = 0.0f; rz.data[0][3] = 0.0f;
	rz.data[1][0] = -sin(rotate.data[2]); rz.data[1][1] = cos(rotate.data[2]); rz.data[1][2] = 0.0f; rz.data[1][3] = 0.0f;
	rz.data[2][0] = 0.0f;			      rz.data[2][1] = 0.0f;                rz.data[2][2] = 1.0f; rz.data[2][3] = 0.0f;
	rz.data[3][0] = 0.0f;                 rz.data[3][1] = 0.0f;                rz.data[3][2] = 0.0f; rz.data[3][3] = 1.0f;

	mat = rz * ry * rx;
}

template <typename Type>
void initTranslationTransform(matrix<Type, 4, 4>& mat, const vector<Type, 3>& locate)
{
	mat.data[0][0] = 1.0f; mat.data[0][1] = 0.0f; mat.data[0][2] = 0.0f; mat.data[0][3] = locate.data[0];
	mat.data[1][0] = 0.0f; mat.data[1][1] = 1.0f; mat.data[1][2] = 0.0f; mat.data[1][3] = locate.data[1];
	mat.data[2][0] = 0.0f; mat.data[2][1] = 0.0f; mat.data[2][2] = 1.0f; mat.data[2][3] = locate.data[2];
	mat.data[3][0] = 0.0f; mat.data[3][1] = 0.0f; mat.data[3][2] = 0.0f; mat.data[3][3] = 1.0f;
}

template <typename Type>
void initTranslationTransformT(matrix<Type, 4, 4>& mat, const vector<Type, 3>& locate)
{
	mat.data[0][0] = 1.0f;           mat.data[0][1] = 0.0f;           mat.data[0][2] = 0.0f;           mat.data[0][3] = 0.0f;
	mat.data[1][0] = 0.0f;           mat.data[1][1] = 1.0f;           mat.data[1][2] = 0.0f;           mat.data[1][3] = 0.0f;
	mat.data[2][0] = 0.0f;           mat.data[2][1] = 0.0f;           mat.data[2][2] = 1.0f;           mat.data[2][3] = 0.0f;
	mat.data[3][0] = locate.data[0]; mat.data[3][1] = locate.data[1]; mat.data[3][2] = locate.data[2]; mat.data[3][3] = 1.0f;
}

template <typename Type>
void initLookDirection(matrix<Type, 4, 4>& mat, const vector<Type, 3>& up, const vector<Type, 3>& right, const vector<Type, 3>& front)
{
	mat.data[0][0] = right.data[0]; mat.data[0][1] = right.data[1]; mat.data[0][2] = right.data[2]; mat.data[0][3] = 0.0f;
	mat.data[1][0] = up.data[0];    mat.data[1][1] = up.data[1];    mat.data[1][2] = up.data[2];    mat.data[1][3] = 0.0f;
	mat.data[2][0] = front.data[0]; mat.data[2][1] = front.data[1]; mat.data[2][2] = front.data[2]; mat.data[2][3] = 0.0f;
	mat.data[3][0] = 0.0f;          mat.data[3][1] = 0.0f;          mat.data[3][2] = 0.0f;          mat.data[3][3] = 1.0f;
}

template <typename Type>
void initLookDirectionT(matrix<Type, 4, 4>& mat, const vector<Type, 3>& up, const vector<Type, 3>& right, const vector<Type, 3>& front)
{
	mat.data[0][0] = right.data[0]; mat.data[0][1] = up.data[0]; mat.data[0][2] = front.data[0]; mat.data[0][3] = 0.0f;
	mat.data[1][0] = right.data[1]; mat.data[1][1] = up.data[1]; mat.data[1][2] = front.data[1]; mat.data[1][3] = 0.0f;
	mat.data[2][0] = right.data[2]; mat.data[2][1] = up.data[2]; mat.data[2][2] = front.data[2]; mat.data[2][3] = 0.0f;
	mat.data[3][0] = 0.0f;          mat.data[3][1] = 0.0f;       mat.data[3][2] = 0.0f;          mat.data[3][3] = 1.0f;
}




template <typename Type, int size>
void initIdentity(matrix<Type, size, size>& matrix)
{
	for (unsigned int x = 0; x < size; x++) {
		for (unsigned int y = 0; y < size; y++) {
			matrix.data[x][y] = y == x ? 1 : 0;
		}
	}
}

template <typename Type>
void initIdentity(matrix<Type, 4, 4>& mat)
{
	mat.data[0][0] = 1.0f; mat.data[0][1] = 0.0f; mat.data[0][2] = 0.0f; mat.data[0][3] = 0.0f;
	mat.data[1][0] = 0.0f; mat.data[1][1] = 1.0f; mat.data[1][2] = 0.0f; mat.data[1][3] = 0.0f;
	mat.data[2][0] = 0.0f; mat.data[2][1] = 0.0f; mat.data[2][2] = 1.0f; mat.data[2][3] = 0.0f;
	mat.data[3][0] = 0.0f; mat.data[3][1] = 0.0f; mat.data[3][2] = 0.0f; mat.data[3][3] = 1.0f;
}

template <typename Type>
void initIdentity(matrix<Type, 3, 3>& mat)
{
	mat.data[0][0] = 1.0f; mat.data[0][1] = 0.0f; mat.data[0][2] = 0.0f;
	mat.data[1][0] = 0.0f; mat.data[1][1] = 1.0f; mat.data[1][2] = 0.0f;
	mat.data[2][0] = 0.0f; mat.data[2][1] = 0.0f; mat.data[2][2] = 1.0f;
}

using mat2 = matrix<float, 2, 2>;
using mat3 = matrix<float, 3, 3>;
using mat4 = matrix<float, 4, 4>;
#endif