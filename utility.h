#pragma once

#include <array>
#include <algorithm>

template<typename T, size_t N>
T& random_from_array(std::array<T, N> ts)
{
	int n = rand() % N;
	return ts[n];
}

template<typename T>
T& random_from_array(T* ts, int n)
{
	int r = rand() % n;
	return ts[r];
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}