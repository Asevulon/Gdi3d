#include"math3d.h"

#include<algorithm>
#include<iterator>
using namespace std;

using namespace math3d;

mat4::mat4(float m11, float m12, float m13,
	float m21, float m22, float m23,
	float m31, float m32, float m33,
	float dx, float dy, float dz)
{
	_matrix[0][0] = m11;
	_matrix[0][1] = m12;
	_matrix[0][2] = m13;
	_matrix[0][3] = 0;

	_matrix[1][0] = m21;
	_matrix[1][1] = m22;
	_matrix[1][2] = m23;
	_matrix[1][3] = 0;

	_matrix[2][0] = m31;
	_matrix[2][1] = m32;
	_matrix[2][2] = m33;
	_matrix[2][3] = 0;

	_matrix[3][0] = dx;
	_matrix[3][1] = dy;
	_matrix[3][2] = dz;
	_matrix[3][3] = 1;
}


mat4& mat4::operator = (const mat4& right)
{
	for(int i = 0; i < _rank; i++)
	copy_n(right._matrix[i], _rank, _matrix[i]);
	return *this;
}


mat4 mat4::operator * (const mat4& right)
{
	mat4 res;

	for (int i = 0; i < _rank; i++)
	{
		for (int j = 0; j < _rank; j++)
		{
			double summ = 0;
			for (int k = 0; k < _rank; k++)
			{
				summ += _matrix[i][k] * right._matrix[k][j];
			}

			res._matrix[i][j] = summ;

		}
	}
	return res;
}


void mat4::reset()
{
	for (int i = 0; i < _rank; i++)
	{
		memset(_matrix[i], 0, sizeof(_matrix[i]));
		_matrix[i][i] = 1;
	}
}


mat4& mat4::rotateX(float angle)
{
	angle = angle * Pi / 180;

	mat4 rx(1, 0, 0, 0, cos(angle), sin(angle), 0, -sin(angle), cos(angle));
	*this = *this * rx;
	return *this;
}

mat4& mat4::rotateY(float angle)
{
	angle = angle * Pi / 180;
	mat4 ry(cos(angle), 0, - sin(angle), 0, 1, 0, sin(angle), 0, cos(angle));
	*this = *this * ry;
	return *this;
}

mat4& mat4::rotateZ(float angle)
{
	angle = angle * Pi / 180;
	mat4 rz(cos(angle), sin(angle), 0, -sin(angle), cos(angle), 0, 0, 0, 1);
	*this = *this * rz;
	return *this;
}


mat4& mat4::translate(float x, float y, float z)
{
	mat4 tr;
	tr._matrix[3][0] = x;
	tr._matrix[3][1] = y;
	tr._matrix[3][2] = z;
	*this = *this * tr;
	return *this;
}

mat4& mat4::scale(float x, float y, float z)
{
	mat4 ms;
	ms._matrix[0][0] = x;
	ms._matrix[1][1] = y;
	ms._matrix[2][2] = z;
	*this = *this * ms;
	return *this;
}

mat4& mat4::perspective(double x, double y, double z)
{
	mat4 per;
	if(x)per._matrix[0][3] = -1. / x;
	if(y)per._matrix[1][3] = -1. / y;
	if(z)per._matrix[2][3] = -1. / z;
	*this = *this * per;
	return *this;
}

//----------------------------------------------------------------------------------
//Вектор

vec4::vec4(float x, float y, float z)
{
	_vector[0] = x;
	_vector[1] = y;
	_vector[2] = z;
	_vector[3] = 1;
}

vec4& vec4::operator = (const vec4& right)
{
	copy_n(right._vector, _size, _vector);
	return *this;
}

vec4 vec4::operator * (const mat4& right)
{
	vec4 res;
	for (int i = 0; i < _size; i++)
	{
		double summ = 0;
		for (int k = 0; k < _size; k++)
		{
			summ += _vector[k] * right._matrix[k][i];
		}
		res._vector[i] = summ;
	}
	return res;
}


void vec4::normalize()
{
	for (int i = 0; i < _size; i++)_vector[i] /= _vector[_size - 1];
}
