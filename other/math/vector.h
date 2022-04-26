#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H
#include <cmath>
#include <initializer_list>

template <typename Type, int size>
struct vector
{
	Type data[size];

	vector()
		: data{0}
	{};

	vector(const std::initializer_list<Type>& list)
	{
		auto a = list.begin();
		for (int i = 0; i < size; i++)
		{
			data[i] = *a;
			a++;
		}
	}

	vector<Type, size>& operator=(const std::initializer_list<Type>& list)
	{
		auto a = list.begin();
		for (int i = 0; i < size; i++)
		{
			data[i] = *a;
			a++;
		}

		return *this;
	}


	vector<Type, size> operator-()
	{
		vector<Type, size> out;
		for (int i = 0; i < size; i++)
			out.data[i] = -data[i];
		return out;
	}

	Type len() const
	{
		Type a = 0;
		for (int i = 0; i < size; i++)
		{
			a += data[i] * data[i];
		}
		return sqrt(a);
	}

	vector<Type, size>& normalize()
	{
		Type a = len();
		for (int i = 0; i < size; i++)
		{
			data[i] /= a;
		}

		return *this;
	}

	vector<Type, size>& operator+=(const vector<Type, size> r)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] += r.data[i];
		}

		return *this;
	}
	vector<Type, size>& operator-=(const vector<Type, size> r)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] -= r.data[i];
		}

		return *this;
	}


	vector<Type, size>& operator*=(Type f)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] *= f;
		}

		return *this;
	}
	vector<Type, size>& operator/=(Type f)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] /= f;
		}

		return *this;
	}


	vector<Type, size> operator*(Type r) const
	{
		vector<Type, size> out;
		for (int i = 0; i < size; i++)
		{
			out.data[i] = data[i] * r;
		}

		return out;
	}
	vector<Type, size> operator/(Type r) const
	{
		vector<Type, size> out;
		for (int i = 0; i < size; i++)
		{
			out.data[i] = data[i] / r;
		}

		return out;
	}


	vector<Type, size> operator+(const vector<Type, size> r) const
	{
		vector<Type, size> out;
		for (int i = 0; i < size; i++)
		{
			out.data[i] = data[i] + r.data[i];
		}

		return out;
	}

	vector<Type, size> operator-(const vector<Type, size> r) const
	{
		vector<Type, size> out;
		for (int i = 0; i < size; i++)
		{
			out.data[i] = data[i] - r.data[i];
		}

		return out;
	}


	vector<Type, size> operator*(const vector<Type, size> r) const
	{
		vector<Type, size> out{};
		for (int i = 0; i < size; i++)
		{
			out[i] = data[i] * r.data[i];
		}

		return out;
	}

	inline Type& operator[](const int a)
	{
		return data[a];
	}
};

template <typename Type, int size>
Type dot(const vector<Type, size>& l, const vector<Type, size>& r)
{
	Type out;

	for (int i = 0; i < size; i++)
		out += l.data[i] * r.data[i];

	return out;
}

template <typename Type>
vector<Type, 3> cross(const vector<Type, 3>& l, const vector<Type, 3>& r)
{
	vector<Type, 3> out;

	out.data[0] = l.data[1] * r.data[2] - l.data[2] * r.data[1];
	out.data[1] = l.data[2] * r.data[0] - l.data[0] * r.data[2];
	out.data[2] = l.data[0] * r.data[1] - l.data[1] * r.data[0];

	return out;
}

using vec4 = vector<float, 4>;
using vec3 = vector<float, 3>;
using vec2 = vector<float, 2>;
#endif