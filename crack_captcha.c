#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "metrics.h"
#include "preprocessors.h"
#include "readers.h"
#include "utilities.h"
#include "data.h"
#include "metric_calculator.h"

#define MAP_HEIGHT box_height
#define MAP_WIDTH box_width

int captcha(int height, int width, int pixels[height][width], int digits[4])
{
	// Use bounding box on overall captcha
	int  start_row, start_column, box_width, box_height;
	print_image(height, width, pixels);
	// Clean the image
	remove_three_less(height, width, pixels);
	
	// Transfer bounded box into "box_pixels"
	get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);
	int box_pixels[box_height][box_width];
	copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

	//Clean the image again
	remove_three_less(box_height, box_width, box_pixels);

	print_image(box_height, box_width, box_pixels);

	int partitions[5] = { 0 };
	partitions[0] = 0;
	partitions[4] = box_width - 1;
	// get the partition markers (x coord where to split the image)
	get_partitions(box_height, box_width, box_pixels, partitions);	
	// Create arrays for horizontally segmented 
	int digit_height, digit_width;

	
	// for each digit
	for (int dig = 1; dig < 5; dig++)
	{
		// get the digit's width by using the difference of its left and right 
		// partition markers
		int horDigitWidth = partitions[dig] - partitions[dig - 1];

		// Create a array big enough for it and copy it in
		int horizontal_bound_digit[box_height][horDigitWidth];
		copy_pixels(box_height, box_width, box_pixels, 0, partitions[dig-1], box_height, horDigitWidth, horizontal_bound_digit);
		
		remove_three_less(box_height, horDigitWidth, horizontal_bound_digit);
		// Next step is to bound it on the top and bottom:
		get_bounding_box(box_height, horDigitWidth, horizontal_bound_digit, &start_row, &start_column, &digit_height, &digit_width);
		int digit[digit_height][digit_width];
		copy_pixels(box_height, horDigitWidth, horizontal_bound_digit, start_row, start_column, digit_height, digit_width, digit);
		
		//print_image(digit_height, digit_width, digit);

		// After we have the digit, just put it through the digit function
		// (becomes same problem as part 1)
		digits[dig-1] = calculate_digit(digit_height, digit_width, digit);
		
	}
	return 42;
}

int main(int argc, char *argv[]) {


	char filename[30];
	int height, width;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
		return 1;
	}

	// if a filename is inputted, try crack
	if (mstrlen(argv[1]) > 2)
	{
		strcpy(filename, argv[1]);
		
		// get dimensions
		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		// Create array big enough for captcha
		int pixels[height][width];
		// Create array to store answer
		int digits[4] = { 0 };
		// Read file and call captcha to try crack
		if (read_pbm(filename, height, width, pixels)) {			
			captcha(height, width, pixels, digits);
		}
		printf("%d%d%d%d\n", digits[0],digits[1], digits[2], digits[3]);

		return 0;
	}

	

	return 0;
}
