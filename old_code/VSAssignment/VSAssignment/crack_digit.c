#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "metrics.h"
#include "preprocessors.h"
#include "readers.h"
#include "utilities.h"

#define MAP_HEIGHT box_height
#define MAP_WIDTH box_width

double sumHorBalance = 0;
double sumVerBalance = 0;
double sumTallness = 0;
double sumHoleSize = 0;

int digit(int height, int width, int pixels[height][width])
{
	int  start_row, start_column, box_width, box_height;
	
	// Basic metric variables
	double horBalance, verBalance, tallness, hole_size_fraction = 0;
	int holes = 0;

	// Transfer bounded box into "box_pixels"
	get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);
	int box_pixels[box_height][box_width];
	copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

	// Arrays for islands
	// NOTE: island 0 means not part of an island, therefore islands are 1 indexed
	int island_markings[MAP_HEIGHT][MAP_WIDTH];
	zero_2D_array(MAP_HEIGHT, MAP_WIDTH, island_markings);
	
	Island islands[MAX_NUM_OF_ISLANDS];
	
	int num_of_islands = 1;


	// Calculate metrics
	horBalance = get_horizontal_balance(box_height, box_width, box_pixels);
	verBalance = get_vertical_balance(box_height, box_width, box_pixels);
	tallness = get_tallness(box_height, box_width, box_pixels);

	// Fill out island information
	fill_out_islands(MAP_HEIGHT, MAP_WIDTH, box_pixels, 
		island_markings, islands, &num_of_islands);

	// Count number of holes (i.e. isolated islands)
	for (int i = 1; i <= num_of_islands; i++)
	{
		// if it's isolated and its white, it's a hole... i think
		if (islands[i].is_isolated && islands[i].color == 0)
		{
			holes++;
			hole_size_fraction += islands[i].size;
		}
	}
	// calculate fraction of hole compared to bounding box
	hole_size_fraction /= MAP_HEIGHT*MAP_WIDTH;

	printf("Metrics for :\n");
	//print_image(box_height, box_width, box_pixels);
	printf("Horizontal Balance: %lf\n", horBalance);
	printf("Vertical Balance  : %lf\n", verBalance);
	printf("Tallness          : %lf\n", tallness);
	printf("Number of holes   : %d\n", holes);
	printf("hole size fraction: %lf\n", hole_size_fraction);
	printf("islands:\n");
	print_plain(MAP_HEIGHT, MAP_WIDTH, island_markings);
	printf("\n");

	if (holes != 0)
	{
		fprintf(stderr, "fuck");
		int xxx;
		scanf("%d", &xxx);
	}

	
	// averager adders
	sumHorBalance += horBalance;
	sumVerBalance += verBalance;
	sumTallness += tallness;
	sumHoleSize += hole_size_fraction;

	return 3;
}

int main(int argc, char *argv[]) {
	int height, width;
	char filename[30] = { 0 };
	strcpy(filename, argv[1]);	

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <image-file>\n", filename);
		return 1;
	}

	for (int i = 0; i < 99; i++)
	{
		strcpy(filename, "../../digit/");
		strcpy(filename + 12, argv[1]);
		strcpy(filename + 13, "_");
		sprintf(filename + 14, "%02d", i);
		strcat(filename, ".pbm");
		printf("filename is %s\n", filename);

		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			printf("%d\n", digit(height, width, pixels));
		}
	}

	printf("AVERAGE Metrics for %s :\n", argv[1]);
	//print_image(box_height, box_width, box_pixels);
	printf("Horizontal Balance: %lf\n", sumHorBalance);
	printf("Vertical Balance  : %lf\n", sumVerBalance);
	printf("Tallness          : %lf\n", sumTallness);
	printf("Number of holes   : %d\n", 1);
	printf("hole size fraction: %lf\n", sumHoleSize);
	printf("\n");

	
	return 0;
	while (filename[12] != 'q')
	{
		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			printf("%d\n", digit(height, width, pixels));
		}
		
		strcpy(filename, "../../digit/");
		fgets(filename + 12, 20, stdin);
		for (int i = 0; i < 30; i++)
		{
			if (filename[i] == '\n')
			{
				filename[i] = '\0';
				i = 30;
			}
		}
		printf("\n");
	}

    return 0;
}
