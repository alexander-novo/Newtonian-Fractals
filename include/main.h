#define _USE_MATH_DEFINES
#include <complex>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

#define CLAMP(x, y, z) ((x) < (y) ? (y) : ((x) > (z) ? (z) : (x)))

typedef  std::complex<long double> comp;

template<typename T>
struct vector3 {
	union {
		T x;
		T r;
	};
	union {
		T y;
		T g;
	};
	union {
		T z;
		T b;
	};
};

typedef vector3<long double> vec3;

comp easy(const comp& num);
comp easyPrime(const comp& num);
void run();
vec3 zToRGB(comp z);