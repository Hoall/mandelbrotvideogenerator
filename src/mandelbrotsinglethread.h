/*
 * mandelbrotsinglethread.h
 *
 *  Created on: Sep 18, 2015
 *      Author: fpaetow
 */

#ifndef MANDELBROTSINGLETHREAD_H_
#define MANDELBROTSINGLETHREAD_H_

#include <stdio.h>
#include <stdlib.h>

#include "my_complex.h"
#include "mybmpwriter.h"

my_complex_t calculate_dot(const my_complex_t z, const my_complex_t c);
long iterate_dot(const my_complex_t c, const double abort_value, const long itr);
void calculate_imagedots_iterations(const double x_min, const double x_max,
		const double y_min, const double y_max, const long x_mon,
		const long y_mon, const double abort_value, const long itr,
		long * image);
void calculate_color(const long width, long height, long itr,
		long * imagevalues, unsigned char * image);
void calculate_image(const double x_min, const double x_max, const double y_min, const double y_max,
		const long width, const long height, const double abort_value, const long itr,
		long * imagevalues, unsigned char * image);
void calculate_and_safe_image(const long i, const double x_min,
		const double x_max, const double y_min, const double y_max,
		const long width, const long height, const double abort_value,
		const long itr);

#endif /* MANDELBROTSINGLETHREAD_H_ */
