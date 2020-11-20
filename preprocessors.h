#ifndef PREPROCESSORS_H
#define PREPROCESSORS_H

void get_bounding_box(int height, int width, int pixels[height][width],
	int *start_row, int *start_column, int *box_height, int *box_width);

void get_partitions(int height, int width, int pixels[height][width], int partitions[3]);
void remove_three_less(int height, int width, int pixels[height][width]);

#endif