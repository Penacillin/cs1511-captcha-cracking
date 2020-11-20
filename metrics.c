#include "metrics.h"
#include "utilities.h"
#include <stdio.h>
#include <math.h>

// Gets the vertical balance of the image
double get_vertical_balance(int height, int width, int pixels[height][width])
{
	int row_sum = 0;
	int n_black_pixels = 0;

	for (int i = 0; i < height; i++)
	{
		int currRowSum = 0;
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				currRowSum++;
				n_black_pixels++;
			}
		}
		// after found sum of black pixels in current column, add to total
		row_sum += currRowSum * i;
	}

	return ((double)row_sum / n_black_pixels + 0.5) / height;
}

// Gets the horizontal balance of the image
double get_horizontal_balance(int height, int width, int pixels[height][width])
{
	int column_sum = 0;
	int n_black_pixels = 0;

	for (int i = 0; i < width; i++)
	{
		int currColumnSum = 0;
		for (int j = 0; j < height; j++)
		{
			if (pixels[j][i])
			{
				// if pixel is black
				currColumnSum++;
				n_black_pixels++;
			}
		}
		// after found sum of black pixels in current column, add to total
		column_sum += currColumnSum * i;
	}

	return ((double)column_sum / n_black_pixels + 0.5) / width;
}

// Gets the tallness of the image (height / width)
double get_tallness(int height, int width)
{
	return (double)height / width;
}

// Gets the density of black in the image
double get_density(int height, int width, int pixels[height][width])
{
	int n_black_pixels = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				n_black_pixels++;
			}
		}
	}
	//printf("num of black pixels:%d, sqare: %d\n", n_black_pixels, height*width);
	return (double) n_black_pixels / (height*width);
}

//  Get the maximum vertical line length as a ratio of its height
double get_max_vertical(int height, int width, int pixels[height][width])
{

	int max = 0;

	for (int i = 0; i < width; i++)
	{
		int curr_col_sum = 0;
		for (int j = 0; j < height; j++)
		{
			if (pixels[j][i])
			{
				// if pixel is black
				curr_col_sum++;
			}
		}
		if (curr_col_sum > max)
			max = curr_col_sum;
	}

	return (double) max / height;
}

// Get the maximum horizontal line as a ratio of the width
double get_max_horizontal(int height, int width, int pixels[height][width])
{

	int max = 0;

	for (int i = 0; i < height; i++)
	{
		int curr_row_sum = 0;
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				curr_row_sum++;
			}
		}
		if (curr_row_sum > max)
			max = curr_row_sum;
	}

	return (double) max / width;
}

// Get the average width of the digit as a ratio of its width
double get_average_width(int height, int width, int pixels[height][width])
{
	double sum_width = 0;
	
	int left_side = 0;
	int right_side = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				left_side = j;
				j = width;
			}
		}
		for (int j = width-1; j >= 0; j--)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				right_side = j;
				j = -1;
			}
		}

		sum_width += right_side - left_side;
	}

	return sum_width / height / width;
}

// gets the density within certain bounds
double get_density_within_bounds(int y, int h, int x, int w,  int height, int width,  int pixels[height][width])
{
	int n_black_pixels = 0;

	for (int i = y; i < h + y; i++)
	{
		for (int j = x; j < w + x; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				n_black_pixels++;
			}
		}
	}
	//printf("num of black pixels:%d, sqare: %d\n", n_black_pixels, height*width);
	return (double)n_black_pixels / (height*width);
}

// Return density of the rectangle 1/3 up from the bottom left and halfway across
// the image
double get_middle_left_density(int height, int width, int pixels[height][width])
{
	return get_density_within_bounds(height / 3, height / 3, 0, width / 2,  height, width, pixels);
}

// Return density of rectangle 1/3 from bottom right and halway across
double get_bottom_right_density(int height, int width, int pixels[height][width])
{
	return get_density_within_bounds(0, height / 3, width / 2, width / 2,  height, width, pixels);
}

// Get the horizontal balance of the bottom half of the image
double get_bot_horizontal_balance(int height, int width, int pixels[height][width])
{

	int column_sum = 0;
	int n_black_pixels = 0;

	for (int i = 0; i < width; i++)
	{
		int currColumnSum = 0;
		for (int j = 0; j < height / 2; j++)
		{
			if (pixels[j][i])
			{
				// if pixel is black
				currColumnSum++;
				n_black_pixels++;
			}
		}
		// after found sum of black pixels in current column, add to total
		column_sum += currColumnSum * i;
	}

	return ((double)column_sum / n_black_pixels + 0.5) / width;
}

// Gets the vertical position of hte midpoint of a given island  (as a ratio of height)
double get_vert_pos_of_island(int height, int width, int island[height][width], int indi)
{
	int bot = 0;
	int top = 0;
	// Check its an existant island
	if (indi == 0)
		return 0;

	// Search for bottom of island
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (island[y][x] == indi)
			{
				bot = y;
				x = width;
				y = height;
			}
		}
	}

	// Search for top of island
	for (int y = bot + 1; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (island[y][x] == indi)
			{
				top = y;
			}
		}
	}

	// return its height as a fraction of picture height
	return (double)(top + bot) / 2 / height;
}

// Gets the standard deviation of the horizontal balance
double get_SD_hor_bal(int height, int width, int pixels[height][width])
{
	double mean = 0;
	double values[height];

	for (int y = 0; y < height; y++)
	{
		int curr_row = 0;
		int n_pixels = 0;
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				curr_row += x;
				n_pixels++;
			}
		}
		if (n_pixels != 0)
			values[y] = ((double)curr_row / n_pixels + 0.5) / width;
		else
			values[y] = 0.5;
		mean += values[y];
	}
	mean /= height;
	double square_difference_sum = 0;
	for (int i = 0; i < height; i++)
	{
		square_difference_sum += (values[i] - mean)*(values[i] - mean);
	}
	square_difference_sum /= height - 1;
	return sqrt(square_difference_sum);
}

// Gets how far from the left side the number has 3 strokes
double get_mean_width_of_three(int height, int width, int pixels[height][width])
{
	int threes = 0;
	int black = 0;
	int swaps = 0;
	for (int x = 0; x < width; x++)
	{
		black = pixels[0][x];
		swaps = 0;
		if (black)
			swaps++;
		for (int y = 1; y < height; y++)
		{
			if (pixels[y][x] != black)
			{
				swaps++;
				black = pixels[y][x];
			}
		}
		if (black)
			swaps++;
		if (swaps == 6)
		{
			return (double)x / width;
			threes++;
		}
	}

	return (double)threes / width;
}

#define LEFT_DIST_TOP (height - (height / 5))
#define LEFT_DIST_BOT (2 * height / 3)

// Get the Standard deviation of how far from the left the pixels are 
// in the top third of the image
double get_SD_dist_from_left_first_third(int height, int width, int pixels[height][width])
{
	double mean = 0;
	int values[(LEFT_DIST_TOP - LEFT_DIST_BOT) + 1];

	for (int y = LEFT_DIST_TOP; y > LEFT_DIST_BOT; y--)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				mean += x;
				values[LEFT_DIST_TOP - y] = x;
				x = width;
			}
		}
	}
	 
	mean /= (double)(LEFT_DIST_TOP - LEFT_DIST_BOT) / width;
	double square_difference_sum = 0;
	
	for (int i = 0; i < LEFT_DIST_TOP - LEFT_DIST_BOT; i++)
	{
		square_difference_sum += (values[i] - mean)*(values[i] - mean);
	}
	square_difference_sum /= (LEFT_DIST_TOP - LEFT_DIST_BOT) - 1;
	
	return sqrt(square_difference_sum);
}

// Get fraction of width of image that has three horizontal strokes
// for example 7 should have 0, 3 would have some fraction
double get_fraction_three(int height, int width, int pixels[height][width])
{
	double mean = 0;
	int color = 0;
	

	for (int x = 0; x < width; x++)
	{
		int swaps = 0;
		color = pixels[0][x];
		if (color == 1)
			swaps++;
		for (int y = 0; y < height; y++)
		{			
			if (pixels[y][x] != color)
			{
				swaps += 1;
				color = pixels[y][x];
			}
		}
		if (color == 1)
			swaps++;
		if (swaps == 6)
			mean++;
	}

	return mean / width;
}

// Gets the standard deviation of the horizontal balance
double get_hor_bal_top(int height, int width, int pixels[height][width])
{
	double mean = 0;
	double values[LEFT_DIST_TOP - LEFT_DIST_BOT];

	for (int y = LEFT_DIST_TOP; y > LEFT_DIST_BOT; y--)
	{
		int curr_row = 0;
		int n_pixels = 0;
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				curr_row += x;
				n_pixels++;
			}
		}
		if (n_pixels != 0)
			values[LEFT_DIST_TOP - y] = ((double)curr_row / n_pixels + 0.5) / width;
		else
			values[LEFT_DIST_TOP - y] = 0.5;
		mean += values[LEFT_DIST_TOP - y];
	}
	mean /= LEFT_DIST_TOP - LEFT_DIST_BOT;
	
	return mean;
}

// Get the longest vertical line in the top third of image
double get_longest_vert_top(int height, int width, int pixels[height][width])
{
	int longest = 0;
	int index = 0;
	for (int x = 0; x < width; x++)
	{
		int curr = 0;
		for (int y = height - 1; y > height / 3; y++)
		{
			if (pixels[y][x])
			{
				curr++;
			}
			else
			{
				if (curr > longest)
					longest = curr;
				curr = 0;
			}
		}
	}

	return index / width;
}

double get_max_fall_top_left(int height, int width, int pixels[height][width])
{
	int x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height-1][x])
		{
			x2 = x;

			x = width;
		}
	}
	// Get second pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height - 2][x])
		{
			x1 = x;

			x = width;
		}
	}
	if ((double)(x1 - x2)  < 0)
	{
		sum += (double)(x1 - x2) ;
		counter++;
	}

	for (int y = height - 3; y > 2 * height / 3; y--)
	{
		for (int x = 0; x < width; x++)
		{	
			if (pixels[y][x]) {
				x2 = x1;
				x1 = x;
				if ((double)(x1 - x2) < 0)
				{
					sum += (double)(x1 - x2) ;
					counter++;
				}
				x = width;
			}
		}
		
	}
	if (counter > 0) {
		sum /= counter;
		return sum /= width;
	}
	else
		return 0;
}

// Get maximum fall on bottom right (averaged)
double get_max_fall_bot_right(int height, int width, int pixels[height][width])
{
	int  x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = width - 1; x > 0; x--)
	{
		if (pixels[0][x])
		{
			x2 = x;

			x = 0;
		}
	}
	// Get second pixel
	for (int x = width  - 1; x > 0; x--)
	{
		if (pixels[1][x])
		{
			x1 = x;

			x = 0;
		}
	}
	// If the gradient is negative, keep
	if ((double)(x1 - x2)   < 0)
	{
		sum += (double)(x1 - x2) ;
		counter++;
	}
	// from the bottom right, look for negative gradients, and 
	// add them to the sum while incrementing a counter (to take mean)
	for (int y = 2; y < height / 8; y++)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x]) {
				x2 = x1;
				x1 = x;
				if ((double)(x1 - x2)  < 0)
				{
					sum += (double)(x1 - x2) ;
					counter++;
				}
				x = 0;
			}
		}

	}
	if (counter > 0) {
		sum /= counter;
		return sum ;
	}
	else
		return 0;
}

// Get maximum fall on top right (averaged)
double get_max_fall_top_right(int height, int width, int pixels[height][width])
{
	int y1 = 1, y2 = 0, x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = width - 1; x > 0; x--)
	{
		if (pixels[height - 1][x])
		{
			x2 = x;
			y2 = 0;

			x = 0;
		}
	}
	// Get second pixel
	for (int x = width - 1; x > 0; x--)
	{
		if (pixels[height - 2][x])
		{
			y1 = 1;
			x1 = x;

			x = 0;
		}
	}
	if ((double)(x1 - x2) / (y1 - y2) < 0)
	{
		sum += (double)(x1 - x2) / (y1 - y2);
		counter++;
	}

	for (int y = height - 3; y > 2 * height / 3; y--)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x]) {
				x2 = x1;
				y2 = y1;
				x1 = x;
				y1 = y;
				if ((double)(x1 - x2) / (y1 - y2) < 0)
				{
					sum += (double)(x1 - x2) / (y1 - y2);
					counter++;
				}
				x = 0;
			}
		}

	}
	if (counter > 0) {
		sum /= counter;
		return sum /= width;
	}
	else
		return 0;
}

// Get the maximum fall on the bottom left (averaged)
double get_max_fall_bot_left(int height, int width, int pixels[height][width])
{
	int x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = 0; x < width ; x++)
	{
		if (pixels[0][x])
		{
			x2 = x;

			x = width;
		}
	}
	// Get second pixel
	for (int x = 0; x < width ; x++)
	{
		if (pixels[1][x])
		{
			x1 = x;

			x = width;
		}
	}
	if ((double)(x1 - x2)  > 0)
	{
		sum += (double)(x1 - x2);
		counter++;
	}

	for (int y = 2; y < height / 2; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x]) {
				x2 = x1;
				x1 = x;
				if ((double)(x1 - x2)  > 0)
				{
					sum += (double)(x1 - x2) ;
					counter++;
				}
				x = width;
			}
		}

	}
	if (counter > 0) {
		sum /= counter;
		return sum /= width;
	}		
	else
		return 0;
}

// Get the maximum fall inwards from the middle left (up or down)
double get_max_fall_mid_left(int height, int width, int pixels[height][width])
{
	int x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height / 3][x])
		{
			x2 = x;

			x = width;
		}
	}
	// Get second pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height / 3 + 1][x])
		{
			x1 = x;

			x = width;
		}
	}
	if ((double)(x1 - x2)  < 0)
	{
		sum += (double)(x1 - x2);
		counter++;
	}

	for (int y = height / 3 + 2; y < 2 * height / 3; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x]) {
				x2 = x1;
				x1 = x;	
				if ((double)(x1 - x2) < 0)
				{
					sum += (double)(x1 - x2) ;
					counter++;
				}
				x = width;
			}
		}

	}
	if (counter > 0) {
		sum /= counter;
		return sum /= width;
	}
	else
		return 0;
}

// Get the maximum fall in the middle left in the downwards direction to the right
// For example a '3' would go inwards from the centre down
double get_max_fall_mid_left_down_right(int height, int width, int pixels[height][width])
{
	int y1 = 0, y2 = 0, x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[2 * height / 3][x])
		{
			x2 = x;
			y2 = 2 * height / 3;

			x = width;
		}
	}
	// Get second pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height / 3 - 1][x])
		{
			y1 = 2 * height / 3 - 1;
			x1 = x;

			x = width;
		}
	}
	if ((double)(x1 - x2) / (y1 - y2) < 0)
	{
		sum += (double)(x1 - x2);
		counter++;
	}

	for (int y = 2*  height / 3 - 1; y > height / 3; y--)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x]) {
				x2 = x1;
				y2 = y1;
				x1 = x;
				y1 = y;
				if ((double)(x1 - x2) / (y1 - y2) < 0)
				{
					sum += (double)(x1 - x2) / (y1 - y2);
					counter++;
				}
				x = width;
			}
		}

	}
	if (counter > 0) {
		sum /= counter;
		return sum /= width;
	}
	else
		return 0;
}

// Gets how much indententation there is of the middle left side of the image
// 0 for  indentation, 1 for no indentation
double get_smoothness_mid_left(int height, int width, int pixels[height][width])
{
	int rightest = 0;
	int yrightest = 0;
	for (int y = 2 * height / 3; y > height / 3 + 1; y--)
	{

		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				if (x > rightest)
				{
					rightest = x;
					yrightest = y;
				}
				x = width;
			}
		}
	}

	int uppery = yrightest;
	int upperx = rightest;
	for (int y = yrightest; y < 2 * height / 3; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{				
				if (x < upperx)
				{
					upperx = x;
					uppery = y;
				}

				x = width;
			}
		}
	}

	int lowery = rightest;
	int lowerx = yrightest;
	for (int y = yrightest; y >  height / 3; y--)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x] )
			{
				if (x < lowerx)
				{
					lowerx = x;
					lowery = y;
				}

				x = width;
			}
		}
	}

	if (yrightest == uppery || yrightest == lowery)
		return 1;
	return 0;
}

// Gets how much indententation there is of the middle right side of the image
// 0 for  indentation, 1 for no indentation
double get_smoothness_mid_right(int height, int width, int pixels[height][width])
{
	int leftest = 200;
	int yleftest = 0;

	// get shortest
	for (int y = 2 * height / 3; y > height / 3 + 1; y--)
	{

		for (int x = width -1 ; x > 0; x--)
		{
			if (pixels[y][x])
			{
				if (x < leftest)
				{
					leftest = x;
					yleftest = y;
				}
				x = 0;
			}
		}
	}

	// Check above for a taller side
	int uppery = yleftest;
	int upperx = leftest;
	for (int y = yleftest; y < 2 * height / 3; y++)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x])
			{
				if (x > upperx)
				{
					upperx = x;
					uppery = y;
				}

				x = 0;
			}
		}
	}

	// Check below for a taller side
	int lowery = yleftest;
	int lowerx = leftest;
	for (int y = yleftest; y > height / 3; y--)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x])
			{
				if (x > lowerx)
				{
					lowerx = x;
					lowery = y;
				}

				x = 0;
			}
		}
	}
	// if there was none, return 1, if there was a taller side on both
	// sides, return 0
	if (yleftest == uppery || yleftest == lowery)
		return 1;
	return 0;
}


// gets the furthest left pixel as a ratio of the width
// in the bottom right of the image
double get_deepest_left_bot_right(int height, int width, int pixels[height][width])
{
	int deepest = 200;

	for (int y = height / 10; y < height / 3; y++)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x]) {
				if (x < deepest)
					deepest = x;

				x = 0;
			}
		}

	}
	return (double) deepest / width;
}

// Get the furthest lest pixel of the bottom third of the image
// as a ratio to the width of the image
double get_shallowest_bot_left(int height, int width, int pixels[height][width])
{
	int shallowest = 200;

	for (int y = height / 20; y < height / 4; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x]) {
				if (x < shallowest)
					shallowest = x;

				x = width;
			}
		}

	}
	return (double)shallowest / width;
}

// gets the number of vertical strokes in the bottom half of the image
double get_verts_bot(int height, int width, int pixels[height][width])
{
	double swaps = 0;
	int color = 0;
	for (int y = height / 8; y < height / 3; y++)
	{
		color = pixels[y][0];
		for (int x = 1; x < width; x++)
		{
			if (pixels[y][x] != color) {
				swaps++;
				color = pixels[y][x];
			}
		}

	}
	return swaps / (height / 3 - height / 8);
}

// get max change in bottom vertical line in the bottom half of image
double get_max_diff_vert(int height, int width, int pixels[height][width])
{
	int longest = 0;
	int shortest = 200;
	for (int x = 0; x < width; x++)
	{
		int y = 0;
		while (pixels[y][x] == 0 && y < height / 3) y++;
		
		int len = 0;
		if (y != height / 3)
		{
			while (y < height && pixels[y][x] == 1 )
			{
				y++;
				len++;
			}

			if (len > longest)
				longest = len;
			if (len < shortest)
				shortest = len;
		}
	}

	return (double)(longest-shortest) / height;

}

// Gets the standard deviation of the gradients along the bottom
// left of the image
double get_SD_grad_bot_left(int height, int width, int pixels[height][width])
{
	int N = height / 3;
	double grads[N];

	for (int y = 0; y < N; y++)
	{
		int x1, x2;

		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				x1 = x;

				x = width;
			}
		}

		for (int x = 0; x < width; x++)
		{
			if (pixels[y + 1][x])
			{
				x2 = x;

				x = width;
			}
		}
		grads[y] = (double)(x1 - x2);
		//printf("grad is %lf", grads[2 * height / 3 - y]);
		//int x;
		//scanf("%d", &x);
	}

	// Calculate SD
	double mean = 0;
	for (int i = 0; i < N; i++)
	{
		mean += grads[i];
	}

	mean /= N;
	double square_difference_sum = 0;
	for (int i = 0; i < N; i++)
	{
		square_difference_sum += (grads[i] - mean)*(grads[i] - mean);
	}
	square_difference_sum /= N;

	return sqrt(square_difference_sum);
}

// gets largest difference in width of rightmost and leftmost pixel
// from right side of image of the bottom right of image
double get_SD_grad_bot_right(int height, int width, int pixels[height][width])
{
	int N = height / 3;

	int tallest = 0;
	int shortest = 0;
	int y1 = 0;

	// find tallest
	for (int y = 0; y < N; y++)
	{
		int x = width - 1;
		while (pixels[y][x] == 0 && x > 0) x--;

		if (x > tallest)
		{
			tallest = x;
			y1 = y;
		}
	}	
	shortest = tallest;
	// find shortest above  tallest
	for (int y = y1; y < N; y++)
	{
		int x = width - 1;
		while (pixels[y][x] == 0 && x > 0) x--;

		if (x < shortest)
			shortest = x;
	}
	//printf("tallest shortest %d %d %lf\n", tallest, shortest, (double)(tallest - shortest) / width);
	return (double)(tallest - shortest) / width;

}

// gets largest difference in width of rightmost and leftmost pixel
// from right side of image of the top right of image
double get_largest_delta_TR(int height, int width, int pixels[height][width])
{
	int tallest = 0;
	int shortest = 200;
	int y1 = 0;

	// find tallest
	for (int y = height - 1; y > 2 * height / 3; y--)
	{
		int x = width - 1;
		while (pixels[y][x] == 0 && x > 0) x--;

		if (x > tallest)
		{
			tallest = x;
			y1 = y;
		}
	}
	shortest = tallest;
	// find shortest below  tallest
	for (int y = y1; y > 2 * height / 3; y--)
	{
		int x = width - 1;
		while (pixels[y][x] == 0 && x > 0) x--;

		if (x < shortest)
			shortest = x;
	}
	//printf("tallest shortest %d %d %lf\n", tallest, shortest, (double)(tallest - shortest) / width);
	return (double)(tallest - shortest) / width;

}

// gets the largest difference between leftmost and rightmost pixel from
// left side of image of bottom left of image
double get_largest_delta_BL(int height, int width, int pixels[height][width])
{
	int tallest = 200;
	int shortest = 0;
	int y1 = 0;

	// find tallest
	for (int y = 0; y < height / 3; y++)
	{
		int x = 0;
		while (pixels[y][x] == 0 && x > 0) x++;

		if (x < tallest)
		{
			tallest = x;
			y1 = y;
		}
	}
	shortest = tallest;
	// find shortest above  tallest
	for (int y = y1; y < height / 3; y++)
	{
		int x = 0;
		while (pixels[y][x] == 0 && x > 0) x++;

		if (x > shortest)
			shortest = x;
	}
	//printf("tallest shortest %d %d %lf\n", tallest, shortest, (double)(tallest - shortest) / width);
	return (double)(shortest - tallest) / width;

}

// get the average gradient in the middle right of image 
double get_average_grad_mid_right(int height, int width, int pixels[height][width])
{
	double mean = 0;
	int counter = 0;
	// find tallest
	for (int y = height / 3; y < 2 * height / 3; y++)
	{
		int x = width - 1;
		int x2 = width - 1;
		while (pixels[y][x] == 0 && x > 0) x--;
		while (pixels[y+1][x2] == 0 && x2 > 0) x2--;

		if (x != x2)
		{
			mean += x > x2 ? x - x2 : x2 - x;
			counter++;
		}
	}

	if (counter == 0)
		return 0;
	return (double) mean / counter;

}

// get the maximum change in gradient for the bottom right of image
double get_max_grad_change_BR(int height, int width, int pixels[height][width])
{
	double smallest = 300;
	double largest = -300;
	for (int y = 0; y < height / 3; y++)
	{
		int x = width - 1;
		int x1 = width - 1;
		while (x > 0 && pixels[y][x] == 0 ) x--;
		while (x1 > 0 && pixels[y+1][x1] == 0 ) x1--;

		if (x - x1 < smallest)
			smallest = x - x1;
		if (x - x1 > largest)
			largest = x - x1;
	}

	return largest - smallest;
}

// Get the maximum change in gradient in the bottom left of image
double get_max_grad_change_BL(int height, int width, int pixels[height][width])
{
	double smallest = 300;
	double largest = -300;
	for (int y = 0; y < height / 3; y++)
	{
		int x = 0;
		int x1 = 0;
		while (x < width && pixels[y][x] == 0) x++;
		while (x1 < width && pixels[y + 1][x1] == 0) x1++;

		if (x - x1 < smallest)
			smallest = x - x1;
		if (x - x1 > largest)
			largest = x - x1;
	}

	return largest - smallest;
}

// get longest horizontal line in the bottom third of image
double get_max_hor_bot(int height, int width, int pixels[height][width])
{
	double largest = 0;
	for (int y = 1; y < height / 3; y++)
	{
		int x = 0;
		int len = 0;
		while (x < width && (pixels[y+1][x] == 0 || pixels[y][x] == 0 || pixels[y-1][x] == 0) 
			) x++;
		while (x < width && (pixels[y + 1][x] == 1 || pixels[y][x] == 1 || pixels[y - 1][x] == 1)
			)  x++, len++;

		if (len > largest)
			largest = len;
	}

	return (double) largest / width;
}

// Get the largest difference in horizontal lines in the bottom
double get_max_width_diff_bot(int height, int width, int pixels[height][width])
{
	double largest = 0;
	for (int y = 1; y < height / 4; y++)
	{
		int x = 0;
		int x2 = width - 1;
		while (x < width && (pixels[y + 1][x] == 0 || pixels[y][x] == 0 || pixels[y - 1][x] == 0)
			) x++;
		while (x2 >= 0 && (pixels[y + 1][x2] == 0 || pixels[y][x2] == 0 || pixels[y - 1][x2] == 0)
			)  x2--;

		if (x2 - x > largest)
			largest = x2 - x;
	}

	return (double)largest / width;
}

double get_top_third_right(int height, int width, int pixels[height][width])
{
	double mean = 0;
	for (int y = height - 1; y > 2 * height / 3; y--)
	{
		int x = 0;
		while (x < width && pixels[y][x] == 0) x++;

		mean += (double) x / width;
	}

	return mean / (double) (height / 3);
}