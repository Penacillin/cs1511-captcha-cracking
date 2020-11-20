#include "preprocessors.h"

void get_bounding_box(int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width)
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(pixels[i][j])
			{
				// found starting row, store it
				*start_row = i;
				// end loop
				j = width;
				i = height;
			}
		}
	}

	for(int i = height - 1; i > 0; i--)
	{
		for(int j =  width - 1; j > 0; j--)
		{
			if(pixels[i][j])
			{
				// found top row, calculate heights
				*box_height = i - *start_row + 1;
				// end loop
				j = 0;
				i = 0;
			}
		}
	}

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			if(pixels[j][i])
			{
				// found starting column, store it
				*start_column = i;
				// end loop
				i = width;
				j = height;
			}
		}
	}

	for(int i = width - 1; i > 0; i--)
	{
		for(int j =  height - 1; j > 0; j--)
		{
			if(pixels[j][i])
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
