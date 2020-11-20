#pragma once
#define MAX_NUM_OF_ISLANDS 100
#define STACK_SIZE 100000

#define TRUE 1
#define FALSE 0;

typedef struct Island Island;
struct Island {
	int size;
	int is_isolated;
	int color;
};

void print_image(int height, int width, int pixels[height][width]);
void print_plain(int height, int width, int pixels[height][width]);
void zero_2D_array(int height, int width, int pixels[height][width]);
void copy_pixels(int height, int width, int pixels[height][width],
	int start_row, int start_column, int copy_height, int copy_width,
	int copy[copy_height][copy_width]);

int flood_filler(int height, int width, int x, int y, int pixels[height][width],
	int island_markings[height][width], int* island_size, int island_index, int* is_isolated);
int fill_out_islands(int height, int width, int pixels[height][width],
	int island_markings[height][width], Island island[MAX_NUM_OF_ISLANDS],
	int* num_of_islands);
