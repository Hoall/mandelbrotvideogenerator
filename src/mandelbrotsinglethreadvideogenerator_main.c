/*
 * mandelbrotsinglethread_main.c
 *
 *      Author: Felix Paetow
 */

#include "mybmpwriter.h"
#include "mandelbrotsinglethread.h"
#include "zoom.h"
#include <sys/time.h>
#include <stdio.h>

int main(void) {

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	//plane section values
	double x_ebene_min = -1;
	double y_ebene_min = -1;
	double x_ebene_max = 2;
	double y_ebene_max = 1;

	//monitor resolution values
	const long x_mon = 640;
	const long y_mon = 480;

	//Iterations
	long itr = 100;

	//abort condition
	double abort_value = 2;

	//Number of images per second
	long fps = 25;

	//video duration in seconds
	long video_duration = 10;

	//zoom speed in percentage
	double reduction = 20;

	//first run, find zoom point

	//Save iteration values
	long * bildptr;
	bildptr = (long *) malloc(x_mon * y_mon * sizeof(long));

	//save color values
	unsigned char * myimage;
	myimage = (unsigned char *) malloc(y_mon * x_mon * 3);

	calculate_image(x_ebene_min, x_ebene_max, y_ebene_min, y_ebene_max, x_mon,
			y_mon, abort_value, itr, bildptr, myimage);

	struct komplex zoom_dot = find_dot_to_zoom(x_ebene_min, x_ebene_max,
			y_ebene_min, y_ebene_max, bildptr, y_mon, x_mon, itr);

	free(bildptr);

	// save the image
	char filename[50];
	sprintf(filename, "img-%d.bmp", 0);

	safe_image_to_bmp(x_mon, y_mon, myimage, filename);

	free(myimage);

	reduce_plane_section_focus_dot(&x_ebene_min, &x_ebene_max, &y_ebene_min,
			&y_ebene_max, reduction, zoom_dot);

	//Calculate all other images
	long i = 1;
	do {
		calculate_and_safe_image( i, x_ebene_min, x_ebene_max, y_ebene_min,
				y_ebene_max, x_mon, y_mon, abort_value, itr);

		reduce_plane_section_focus_dot(&x_ebene_min, &x_ebene_max, &y_ebene_min,
				&y_ebene_max, reduction, zoom_dot);

		++i;
		itr += i * 10;
	} while (i < (fps * video_duration));

	gettimeofday(&tv2, NULL);
	printf("Total time = %f seconds\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
					+ (double) (tv2.tv_sec - tv1.tv_sec));
	printf("\n\n");
	fflush(stdout);

	return 0;
}
