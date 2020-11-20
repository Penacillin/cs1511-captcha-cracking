#include "utilities.h"
#include "stack.h"
#include "data.h"
#include <stdio.h>

// Flood fill algorithm to find all 'islands' of whites or blacks in the image
int flood_filler(int height, int width, int x, int y, int pixels[height][width],
	int island_markings[height][width], int* island_size, int island_index, int* is_isolated)
{
	*is_isolated = TRUE;							// Assume is isolated until it hits a side
	*island_size = 0;

	// Stack variables
	point stack_arr[STACK_SIZE];
	int stack_pointer = 0;

	int currColor = pixels[y][x];

	pop_all(stack_arr, &stack_pointer);
	int cx;

	// push start pixel onto stack as first pixel to explore
	if (!push(stack_arr, &stack_pointer, x, y))
		return 0;

	// while there's pixels to explore
	while (pop(stack_arr, &stack_pointer, &x, &y))
	{
		cx = x;

		// include pixels on left side	
		while (cx >= 0 && pixels[y][cx] == currColor && island_markings[y][cx] == 0) cx--;
		cx++;

		// For Corners:

		// top left
		if (y > 0 && cx > 0 && pixels[y - 1][cx - 1] == currColor && island_markings[y - 1][cx - 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx - 1, y - 1)) return 0;
		}
		// bottom left
		if (y < height - 1 && cx > 0 && pixels[y + 1][cx - 1] == currColor && island_markings[y + 1][cx - 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx - 1, y + 1)) return 0;
		}
		// bottomr right
		if (y > 0 && cx < width - 1 && pixels[y - 1][cx + 1] == currColor && island_markings[y - 1][cx + 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx + 1, y - 1)) return 0;
		}
		// top right
		if (y < height - 1 && cx < width - 1 && pixels[y + 1][cx + 1] == currColor && island_markings[y + 1][cx + 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx + 1, y + 1)) return 0;
		}

		// while this row of pixels belong to this island
		while (cx < width  && pixels[y][cx] == currColor && island_markings[y][cx] == 0)
		{
			
			// mark new point of island on map and increase size of island
			island_markings[y][cx] = island_index;
			*island_size += 1;
			// check if pixel is on border, if so, set is_isolated to FALSE
			if ((*is_isolated) && (cx == 0 || y == 0 || cx == width - 1 || y == height - 1))
			{
				*is_isolated = FALSE;
			}

			// If the pixel above exists, and  and the above pixel is
			// our current color, and isn't already in another island, let's go up later
			if ( y > 0 && pixels[y - 1][cx] == currColor && island_markings[y - 1][cx] == 0)
			{
				if (!push(stack_arr, &stack_pointer, cx, y - 1)) return 0;
			}
			// same for below pixel
			if (  y < height - 1 && pixels[y + 1][cx] == currColor && island_markings[y + 1][cx] == 0)
			{
				if (!push(stack_arr, &stack_pointer, cx, y + 1)) return 0;
			}		

			cx++;
		}
		
		// For Corners:
		cx--;
		// top left
		if (y > 0 && cx > 0 && pixels[y - 1][cx - 1] == currColor && island_markings[y - 1][cx - 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx - 1, y - 1)) return 0;
		}
		// bottom left
		if (y < height - 1 && cx > 0 && pixels[y + 1][cx - 1] == currColor && island_markings[y + 1][cx - 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx - 1, y + 1)) return 0;
		}
		// bottom right
		if (y > 0 && cx < width - 1 && pixels[y - 1][cx + 1] == currColor && island_markings[y - 1][cx + 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx + 1, y - 1)) return 0;
		}
		// top right
		if (y < height - 1 && cx < width - 1 && pixels[y + 1][cx + 1] == currColor && island_markings[y + 1][cx + 1] == 0)
		{
			if (!push(stack_arr, &stack_pointer, cx + 1, y + 1)) return 0;
		}
		cx++;

	} // End popper loop

	return 1;

}

// Runs the flood_filler enough times to ensure every pixel is part of an island
int fill_out_islands(int height, int width, int pixels[height][width],
	int island_markings[height][width], Island islands[MAX_NUM_OF_ISLANDS],
	int* num_of_islands)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (island_markings[i][j] == 0)
			{
				(*num_of_islands)++;

				flood_filler(height, width, j, i, pixels, island_markings, 
					&(islands[*num_of_islands].size), (*num_of_islands), &(islands[*num_of_islands].is_isolated));
				islands[*num_of_islands].color = pixels[i][j];

			
			}
		}
	}

	return 1;
}

// Sets all values to 0 in a 2D array of ints
void zero_2D_array(int height, int width, int pixels[height][width])
{
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			pixels[i][j] = 0;
		}
	}	
}

// Sets all values to 0 in a 2D array of doubles
void zero_2D_double_array(int height, int width, double pixels[height][width])
{
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			pixels[i][j] = 0;
		}
	}
}

// Gets the length of a string
int mstrlen(char* str)
{
	int count = 0;
	while (*(str + count++)) {};
	return count;
}

// returns the max of two ints
int max(int a, int b)
{
	return a > b ? a : b;
}

// Prints the metrics for a digit
void print_digit_metrics(int height, int width, int pixels[height][width], double digit_stats[N_OF_METRICS])
{
	printf("\nMetrics for :\n");
	//print_image(height, width, pixels);
	printf("_Horizontal Balance: %lf\n", digit_stats[mhorBalance]);
	printf("Vertical Balance  : %lf\n", digit_stats[mverBalance]);
	printf("Tallness          : %lf\n", digit_stats[mtallness]);
	printf("Number of holes   : %lf\n", digit_stats[mholes]);
	printf("hole size fraction: %lf\n", digit_stats[mhole_size_fraction]);
	printf("density           : %lf\n", digit_stats[mdensity]);
	printf("max Vertical      : %lf\n", digit_stats[mmaxVertical]);
	printf("max horizontal	  : %lf\n", digit_stats[mmaxHorizontal]);
	printf("average width     : %lf\n", digit_stats[maverageWidth]);
	printf("middleleeft dens  : %lf\n", digit_stats[mmidLeftDensity]);
	printf("bot right   dens  : %lf\n", digit_stats[mbotRightDensity]);
	//printf("islands (%d) :\n", digit_stats[]);
	printf("---\n");
	printf("vert pos of hole  : %lf\n", digit_stats[mvertPosOfHole]);
	printf("---\n");
	printf("SD of hor balance : %lf\n", digit_stats[msdHorBalance]);
	printf("mean width of 3 x : %lf\n", digit_stats[mmeanWidthOfThree]);
	printf("   hor bal top    : %lf\n", digit_stats[mhorBalTop]);
	printf("steepst top left  : %lf\n", digit_stats[msteepestFallTopLeft]);
	printf("steepst bot righ  : %lf\n", digit_stats[msteepestFallBotRight]);
	//printf("smoothnes mid left: %lf\n", digit_stats[msmoothnessMidLeft]);
	printf("steepst mid left  : %lf\n", digit_stats[msteepestFallMidLeft]);
	printf("bot hor balance   : %lf\n", digit_stats[mbotHorBalance]);
	printf("deepest bot rig   : %lf\n", digit_stats[mdeepestLeftBotRight]);
	printf("vertical line sbot: %lf\n", digit_stats[mvertsBot]);
	printf("max diff vert bot : %lf\n", digit_stats[mmaxDiffVertBot]);
	printf("SD grad bot left  : %lf\n", digit_stats[mSDgradBotLeft]);
	printf("steepest bot right: %lf\n", digit_stats[mSDgradBotRight]);
	printf("delta top right   : %lf\n", digit_stats[mdeltaTR]);
	printf("steepest bot left : %lf\n", digit_stats[msteepestFallBotLeft]);
	printf("steepest top righ : %lf\n", digit_stats[msteepestFallTopRight]);
	printf("smoothness mid lef : %lf\n", digit_stats[msmoothnessMidLeft]);
	printf("fraction 3        : %lf\n", digit_stats[mfractionThree]);
	printf("mid right av grad : %lf\n", digit_stats[maverageGradMidRight]);
	printf("shallow bot left  : %lf\n", digit_stats[mshallowestBotLeft]);
	printf("delta BL          : %lf\n", digit_stats[mdeltaBL]);
	printf("smooth mid right  : %lf\n", digit_stats[msmoothnessMidRight]);
	printf("max grad chane BR : %lf\n", digit_stats[mmaxGradChangeBR]);
	//print_plain(MAP_HEIGHT, MAP_WIDTH, island_markings);
	printf("\n");
}