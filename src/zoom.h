/*
 * zoom.h
 *
 *      Author: Felix Paetow
 */

#ifndef SRC_ZOOM_H_
#define SRC_ZOOM_H_

#include <math.h>
#include <stdio.h>
#include "my_complex.h"

my_complex_t find_dot_to_zoom(const double x_min, const double x_max,
		const double y_min, const double y_max, long * image, const long heigth,
		const long width, const long itr);
double calculate_distance_abs(const double a, const double b);
void reduce_section_focus_dot(double * const min, double * const max,
		const double dot, double reduction_value);
void reduce_plane_section_focus_dot(double * const x_min, double * const x_max,
		double * const y_min, double * const y_max,
		double reduction_in_percentage, my_complex_t dot);

#endif /* SRC_ZOOM_H_ */
