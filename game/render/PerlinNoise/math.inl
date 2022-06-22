#ifndef MATH_INL
#define MATH_INL
template <class T>
T lerp(T a, T b, T t)
{
	return a + t * (b - a);
}

template <class T>
T smooth(T t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
#endif