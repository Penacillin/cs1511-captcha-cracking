#include "preprocessors.h"
#include <stdio.h>
#include "math.h"

#define PARTITION_RANGE (width / 7)

// Gets the x coordinates for partitioning the captcha into its 4 digits
void get_partitions(int height, int width, int pixels[height][width], int partitions[3])
{
	// start with a guess for each partition
	partitions[1] = width / 4;
	partitions[2] = width / 2;
	partitions[3] = 3 * width / 4;

	// keep the probabilities of partitions for above and below the assumption
	double prob_plus[PARTITION_RANGE];
	double prob_minus[PARTITION_RANGE];


	// for each guess, adjust it
	for (int j = 1; j < 4; j++)
	{
		int zeroFound = 0;
		// check width/5 to the right and left of the assumption to find the best partition
		for (int i = 0; i < PARTITION_RANGE && !zeroFound; i++)
		{
			int clear = 1;
			int n_pixels = 0;
			for (int y = 0; y < height; y++)
			{

				if (pixels[y][partitions[j] + i])
				{
					n_pixels++;
					clear = 0;
					y = height;
				}
			}
			prob_plus[i] = (double)n_pixels / height;
			if (i)
			{ 			
				prob_plus[i] += 1 - (double)1 / sqrt(i);
			}

			if (clear)
			{
				partitions[j] += i;
				prob_plus[i] = 0;
				i = width;				
				zeroFound = 1;
			}
			
			clear = 1;
			for (int y = 0; y < height && !zeroFound; y++)
			{
				if (pixels[y][partitions[j] - i])
				{
					n_pixels++;
					clear = 0;
					y = height;
				}
			}

			if (clear && !zeroFound)
			{
				partitions[j] -= i;

				prob_minus[i] = 0;
				i = width;
				zeroFound = 1;
			}
			if(!zeroFound)
			{
				
				prob_minus[i] = (double)n_pixels / height;
				if(i)
					prob_minus[i] += 1 - (double)(1 / sqrt(i));
			}
		}
		if (!zeroFound)
		{
			double low = 300;
			int lowi = 0;
			for (int i = 0; i < PARTITION_RANGE; i++)
			{
				if (prob_plus[i] < low) {
					low = prob_plus[i];
					lowi = i;
				}
			}
			for (int i = 0; i < PARTITION_RANGE; i++)
			{
				if (prob_minus[i] < low) {
					low = prob_minus[i];
					lowi = i*-1;
				}
			}
			partitions[j] += lowi;
		}

	}

}

// Cleans the image by despeckling 
void remove_three_less(int height, int width, int pixels[height][width])
{
	int blen = 0;
	int wlen = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				blen++;
				if (wlen <= 3)
				{
					// clean white
					for (int x1 = x; x1 >= x - wlen && x1 >= 0; x1--)
					{
						if((y < height - 1 && pixels[y + 1][x1] != 0)
							|| (y > 0 && pixels[y - 1][x1] != 0) || wlen == 1)
						pixels[y][x1] = 1;
					}

				}
				wlen = 0;
			}
			else
			{
				wlen++;
				if (blen <= 3)
				{
					// clean black
					for (int x1 = x; x1 >= x - blen && x1 >= 0; x1--)
					{
						if((y < height - 1 && pixels[y+1][x1] != 1)
							|| ( y > 0 && pixels[y-1][x1] != 1))
							pixels[y][x1] = 0;
					}
				}
				blen = 0;
			}
		}
	}
}

// gets the bounding box of the image
void get_bounding_box(int height, int width, int pixels[height][width],
	int *start_row, int *start_column, int *box_height, int *box_width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// found starting row, store it
				*start_row = i;
				// end loop
				j = width;
				i = height;
			}
		}
	}

	for (int i = height - 1; i > 0; i--)
	{
		for (int j = width - 1; j > 0; j--)
		{
			if (pixels[i][j])
			{
				// found top row, calculate heights
				*box_height = i - *start_row + 1;
				// end loop
				j = 0;
				i = 0;
			}
		}
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (pixels[j][i])
			{
				// found starting column, store it
				*start_column = i;
				// end loop
				i = width;
				j = height;
			}
		}
	}

	for (int i = width - 1; i > 0; i--)
	{
		for (int j = height - 1; j > 0; j--)
		{
			if (pixels[j][i])
			{
				// found right column, calculate box width
				*box_width = i - *start_column + 1;
				// end loop
				j = 0;
				i = 0;
			}
		}
	}
}
