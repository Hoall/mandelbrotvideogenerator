/*
 * my_complex.h
 *
 *      Author: Felix Paetow
 */

#ifndef MY_COMPLEX_H_
#define MY_COMPLEX_H_

#include <math.h>

typedef struct komplex {
	double real;
	double imaginary;
} my_complex_t;

double delta(const double min, const double max, const long size);
my_complex_t add_complex(my_complex_t a, my_complex_t b);
my_complex_t sub_complex(my_complex_t a, my_complex_t b);
my_complex_t mul_complex(my_complex_t a, my_complex_t b);
double sum_complex(my_complex_t a);

#endif /* MY_COMPLEX_H_ */
