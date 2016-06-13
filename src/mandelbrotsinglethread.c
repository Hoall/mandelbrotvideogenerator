/*
 * mandelbrot.c
 *
 *      Author: Felix Paetow
 */

#include "mandelbrotsinglethread.h"

/**
 *  Calculate z(n+1) = z(n)^2 - c
 * @param z The complex number z.
 * @param c The complex number c.
 * @return The complex number z(n+1)
 */
my_complex_t calculate_dot(const my_complex_t z, const my_complex_t c) {
	my_complex_t result, interim_result;
	result.real = -1;
	result.imaginary = -1;

	interim_result = mul_complex(z, z);
	result = sub_complex(interim_result, c);

	return result;
}

/**
 * Calculates and validates whether a point belongs to the Mandelbrot set or
 * not.
 *
 * The formula is as long as calculated until either the absolute value exceeds
 * the abort condition or the number of iterations has been performed.
 *
 * If the abort condition was fulfilled, the point does not belong to the
 * Mandelbrot set. If not, then most likely.
 *
 * @param c The test point.
 * @param abort_value The value of the abort condition. Normally 2.
 * @param itr The number of required iterations.
 * @return The number of iterations for that point.
 */
long iterate_dot(const my_complex_t c, const double abort_value, const long itr) {
	double sum = -1;

	//define z
	my_complex_t z;
	z.real = 0;
	z.imaginary = 0;

	long i = 0;
	while (i < itr && sum < abort_value) {
		my_complex_t z_neu;

		z_neu = calculate_dot(z, c);	//calculate z(n+1) = z(n) - c
		sum = sum_complex(z_neu);		//calculate |z|
		z = z_neu;

		if (sum < abort_value) {
			++i;
		}
	}

	return i;
}

/**
 * Calculates a Mandelbrot image without colors.
 *
 * For each point of the image it calculates the points and saves the number of
 * iterations for it. From the number of iterations you can say i a point
 * belongs to a Mandelbrot set or not.
 *
 * Based on the number of iterations the color is choosen later.

 *
 * @param x_min Smallest X-value of the plane section.
 * @param x_max Greatest X-value of the plane section.
 * @param y_min Smallest Y-value of the plane section.
 * @param y_max Greatest Y-value of the plane section.
 * @param x_mon Resolution of the monitor on the horizontal axis.
 * @param y_mon Resolution of the monitor on the vertical axis.
 * @param abort_value The value of the abort condition. Normally 2.
 * @param itr The number of required iterations.
 * @param image The image as a set of iteration values.
 */
void calculate_imagedots_iterations(const double x_min, const double x_max,
		const double y_min, const double y_max, const long x_mon,
		const long y_mon, const double abort_value, const long itr,
		long * image) {
	double delta_x = delta(x_min, x_max, x_mon);
	double delta_y = delta(y_min, y_max, y_mon);

	//set to top left corner
	my_complex_t c;
	c.real = x_min;
	c.imaginary = y_max;

	//pass through the rows
	for (int i = 0; i < y_mon; ++i) {

		//pass through the columns
		c.real = x_min;
		for (int j = 0; j < x_mon; ++j) {
			*(image + (i * x_mon + j)) = iterate_dot(c, abort_value, itr);
			c.real += delta_x;
		}

		c.real = x_min;
		c.imaginary -= delta_y;
	}
}

/**
 * Calculates the color from the iteration values.
 *
 * @param imagevalues The calculated iteration values.
 * @param image The final image.
 * @param width The width.
 * @param height The height.
 */
void calculate_color(const long width, long height, long itr,
		long * imagevalues, unsigned char * image) {

	double color_steps = (double) 255.0 / (double) itr;
	double red = color_steps;
	double green = color_steps;
	double blue = color_steps;

	for (long i = 0; i < height; ++i) {
		for (long j = 1; j <= width + 1; ++j) {
			long value = *(imagevalues + (i * width + j - 1));
			value = itr - value;

			double myred = (double) value * red / 1.1;
			double mygreen = (double) value * green / 1.05;
			double myblue = (double) value * blue;

			if (myred > 255.0) {
				myred = 255;
			}
			if (mygreen > 255.0) {
				mygreen = 255;
			}
			if (myblue > 255.0) {
				myblue = 255;
			}

			*(image + (i * width * 3 + j * 3 - 3)) = (unsigned char) myred;
			*(image + (i * width * 3 + j * 3 - 2)) = (unsigned char) mygreen;
			*(image + (i * width * 3 + j * 3 - 1)) = (unsigned char) myblue;
		}
	}
}

/**
 * First it calculates the iteration values for the points of the image and
 * than the resulting color values for each point.
 *
 * @param x_min Smallest X-value of the plane section.
 * @param x_max Greatest X-value of the plane section.
 * @param y_min Smallest Y-value of the plane section.
 * @param y_max Greatest Y-value of the plane section.
 * @param width The width.
 * @param height The height.
 * @param abort_value The value of the abort condition. Normally 2.
 * @param itr The number of required iterations.
 * @param imagevalues The image as a set of iteration values.
 * @param image The color values of the image.
 */
void calculate_image(const double x_min, const double x_max, const double y_min,
		const double y_max, const long width, const long height,
		const double abort_value, const long itr, long * imagevalues,
		unsigned char * image) {

	calculate_imagedots_iterations(x_min, x_max, y_min, y_max, width, height,
			abort_value, itr, imagevalues);
	calculate_color(width, height, itr, imagevalues, image);
}

/**
 * First it calculates the iteration values for the points of the image and
 * than the resulting color values for each point. After that, it saves the
 * image to a bmp file.
 *
 * @param i The number of the image (for the name).
 * @param x_min Smallest X-value of the plane section.
 * @param x_max Greatest X-value of the plane section.
 * @param y_min Smallest Y-value of the plane section.
 * @param y_max Greatest Y-value of the plane section.
 * @param width The width.
 * @param height The height.
 * @param abort_value The value of the abort condition. Normally 2.
 * @param itr The number of required iterations.
 */
void calculate_and_safe_image(const long i, const double x_min,
		const double x_max, const double y_min, const double y_max,
		const long width, const long height, const double abort_value,
		const long itr) {

	long * bildptr;
	bildptr = (long *) malloc(width * height * sizeof(long));

	unsigned char * myimage;
	myimage = (unsigned char *) malloc(width * height * 3);

	calculate_image(x_min, x_max, y_min, y_max, width, height, abort_value, itr,
			bildptr, myimage);

	free(bildptr);

	// save the image
	char filename[50];
	sprintf(filename, "img-%ld.bmp", i);

	safe_image_to_bmp(width, height, myimage, filename);

	free(myimage);
}
