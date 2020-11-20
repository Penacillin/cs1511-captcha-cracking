#include "utilities.h"
#include "stack.h"
#include <stdio.h>


int flood_filler(int height, int width, int x, int y, int pixels[height][width],
	int island_markings[height][width], int* island_size, int island_index, int* is_isolated)
{
	*is_isolated = 1;							// Assume is isolated until it hits a side
	*island_size = 0;
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
		while (cx >= 0 && pixels[y][cx] == currColor) cx--;
		cx++;

		// while this row of pixels belong to this island
		while (cx < width && pixels[y][cx] == currColor && island_markings[y][cx] == 0)
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
			// top left
			if (y > 0 && x > 0 && pixels[y - 1][cx - 1] == currColor && island_markings[y - 1][cx - 1] == 0)
			{
				if (!push(stack_arr, &stack_pointer, cx - 1, y - 1)) return 0;
			}
			// bottom left
			if (y < height -1  && x > 0 && pixels[y + 1][cx - 1] == currColor && island_markings[y - 1][cx - 1] == 0)
			{
				if (!push(stack_arr, &stack_pointer, cx - 1, y + 1)) return 0;
			}


			cx++;
		}
	}
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
				flood_filler(height, width, j, i, pixels, island_markings, 
					&(islands[*num_of_islands].size), (*num_of_islands), &(islands[*num_of_islands].is_isolated));
				islands[*num_of_islands].color = pixels[i][j];

				(*num_of_islands)++;				
			}
		}
	}

	return 1;
}

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