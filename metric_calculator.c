#include "metric_calculator.h"
#include "utilities.h"
#include "metrics.h"
#include "preprocessors.h"
#include <stdio.h>
#include <math.h>

#define MAP_HEIGHT box_height
#define MAP_WIDTH box_width

// Guess the digit using metrics and probability (normal distribution)
int digit_by_metric_prob(double digit_summary[10][N_OF_METRICS][2], double digit_metrics[N_OF_METRICS], double prob_points[10][N_OF_METRICS])
{
	// create array to store points for each metric for each digit
	// The digit that has the most points at the end has the highest chance of 
	// being the digit
	zero_2D_double_array(10, N_OF_METRICS, prob_points);

	// Calculate z score for each metric for each digit
	double z = 0;
	for (int dig = 0; dig < 10; dig++)
	{
		for (int i = 0; i < N_OF_METRICS; i++)
		{
			// if SD is 0, and the x = mean, then its still 0
			if (digit_summary[dig][i][1] == 0.0f && digit_metrics[i] == digit_summary[dig][i][0])
			{
				z = 0;
			}
			// else if SD is 0, its infinity
			else if (digit_summary[dig][i][1] == 0)
			{
				z = METRIC_INF;
			}
			// else calculate z = (x - mean)/SD
			else
			{
				z = (digit_metrics[i] - digit_summary[dig][i][0]) / digit_summary[dig][i][1];
			}
			prob_points[dig][i] = fabs(z);
		}
	}

	

	// Sum up all the z scores for each digit
	double sum_z[10] = { 0.0 };
	for(int i = 0; i < 10;i++)
	{
		for (int j = 0; j < N_OF_METRICS; j++)
		{
			if (j == mhorBalance)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if(j == mmaxVertical)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if(j == mtallness)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if (j == mmaxDiffVertBot)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if(j == mtallness)
				sum_z[i] += prob_points[i][j] * 1;
			else
				sum_z[i] += prob_points[i][j];
		}
	}

	// Find lowest z score, this is the guess for the digit
	double min_z = sum_z[0];
	double min_z2 = sum_z[0];
	int guess = 0;
	int guess2 = 0;
	for (int i = 1; i < 10; i++)
	{
		if (sum_z[i] < min_z)
		{
			min_z2 = min_z;
			min_z = sum_z[i];
			guess2 = guess;
			guess = i;
		}
		if (sum_z[i] < min_z2)
		{
			min_z2 = sum_z[i];
			guess2 = i;
		}
	}
	// If top two guesses are 1 and 2, amplify the metric to differentiate them
	if (guess == 2 && guess2 == 1)
	{
		prob_points[1][mmaxDiffVertBot] *= 3;
		prob_points[2][mmaxDiffVertBot] *= 3;
	}

	return guess;
}

int digit(int height, int width, int pixels[height][width], double digit_stats[N_OF_METRICS])
{
	int  start_row, start_column, box_width, box_height;

	// metric variables
	double  hole_size_fraction = 0, 
		vert_pos_of_hole = 0 ;

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

	int num_of_islands = 0;

	// Fill out island information
	fill_out_islands(MAP_HEIGHT, MAP_WIDTH, box_pixels,
		island_markings, islands, &num_of_islands);

	// variable to indicate the island number of a hole
	int island_indicator_of_hole[8] = { 0 };

	// Count number of holes (i.e. isolated islands)
	for (int i = 1; i <= num_of_islands; i++)
	{
		// if it's isolated and its white, it's a hole... i think
		if (islands[i].is_isolated && islands[i].color == 0 && islands[i].size > 10)
		{
			holes++;
			hole_size_fraction += islands[i].size;
			island_indicator_of_hole[holes - 1] = i;
			//printf("hole island is %d\n", i);
		}
	}

	// Find the mean vertical positions of hole(s)
	for (int i = 0; i < holes; i++)
	{
		vert_pos_of_hole += get_vert_pos_of_island(MAP_HEIGHT, MAP_WIDTH, island_markings, island_indicator_of_hole[i]);
	}
	if (holes != 0)
		vert_pos_of_hole /= holes;

	// calculate fraction of hole compared to bounding box
	hole_size_fraction /= MAP_HEIGHT*MAP_WIDTH;

	// put details into digit stats
	digit_stats[mhorBalance] = get_horizontal_balance(box_height, box_width, box_pixels);
	digit_stats[mverBalance] = get_vertical_balance(box_height, box_width, box_pixels);
	digit_stats[mtallness] = get_tallness(box_height, box_width);
	digit_stats[mhole_size_fraction] = hole_size_fraction;
	digit_stats[mholes] = holes;
	digit_stats[mdensity] = get_density(box_height, box_width, box_pixels);
	digit_stats[mmaxVertical] = get_max_vertical(box_height, box_width, box_pixels);
	digit_stats[mmaxHorizontal] = get_max_horizontal(box_height, box_width, box_pixels);
	digit_stats[maverageWidth] = get_average_width(box_height, box_width, box_pixels);
	digit_stats[mmidLeftDensity] = get_middle_left_density(box_height, box_width, box_pixels);
	digit_stats[mbotRightDensity] = get_bottom_right_density(box_height, box_width, box_pixels);
	digit_stats[mvertPosOfHole] = vert_pos_of_hole;
	digit_stats[msdHorBalance] = get_SD_hor_bal(box_height, box_width, box_pixels);
	digit_stats[mmeanWidthOfThree] = get_mean_width_of_three(box_height, box_width, box_pixels);
	digit_stats[mhorBalTop] = get_hor_bal_top(box_height, box_width, box_pixels);
	digit_stats[msteepestFallTopLeft] = get_max_fall_top_left(box_height, box_width, box_pixels);
	digit_stats[msteepestFallBotRight] = get_max_fall_bot_right(box_height, box_width, box_pixels);
	digit_stats[msteepestFallMidLeft] = get_max_fall_mid_left(box_height, box_width, box_pixels);
	digit_stats[mbotHorBalance] = get_bot_horizontal_balance(box_height, box_width, box_pixels);
	digit_stats[mdeepestLeftBotRight] = get_deepest_left_bot_right(box_height, box_width, box_pixels);
	digit_stats[mvertsBot] = get_verts_bot(box_height, box_width, box_pixels);
	digit_stats[mmaxDiffVertBot] = get_max_diff_vert(box_height, box_width, box_pixels);
	digit_stats[mSDgradBotLeft] = get_SD_grad_bot_left(box_height, box_width, box_pixels);
	digit_stats[mSDgradBotRight] = get_SD_grad_bot_right(box_height, box_width, box_pixels);
	digit_stats[mdeltaTR] = get_largest_delta_TR(box_height, box_width, box_pixels);
	digit_stats[msteepestFallBotLeft] = get_max_fall_bot_left(box_height, box_width, box_pixels);
	digit_stats[msteepestFallTopRight] = get_max_fall_top_right(box_height, box_width, box_pixels);
	digit_stats[msmoothnessMidLeft] = get_smoothness_mid_left(box_height, box_width, box_pixels);
	digit_stats[mfractionThree] = get_fraction_three(box_height, box_width, box_pixels);
	digit_stats[maverageGradMidRight] = get_average_grad_mid_right(box_height, box_width, box_pixels);
	digit_stats[mshallowestBotLeft] = get_shallowest_bot_left(box_height, box_width, box_pixels);
	digit_stats[mdeltaBL] = get_largest_delta_BL(box_height, box_width, box_pixels);
	digit_stats[msmoothnessMidRight] = get_smoothness_mid_right(box_height, box_width, box_pixels);
	digit_stats[mmaxGradChangeBR] = get_max_grad_change_BR(box_height, box_width, box_pixels);
	digit_stats[mmaxGradChangeBL] = get_max_grad_change_BL(box_height, box_width, box_pixels);
	digit_stats[mmaxHorBot] = get_max_hor_bot(box_height, box_width, box_pixels);
	digit_stats[mmaxWidthDiffBot] = get_max_width_diff_bot(box_height, box_width, box_pixels);
	digit_stats[mtopThirdRight] = get_top_third_right(box_height, box_width, box_pixels);

	return 0;
}

// Function to handle digit handling calls and data
int calculate_digit(int height, int width, int pixels[height][width])
{
	// create arrays to store digits statistics, and current digit metrics, and a table of proabilities to guess which digit the current one is
	double digit_stats[N_OF_METRICS];
	digit(height, width, pixels, digit_stats);
	double prob_points[10][N_OF_METRICS];

	double digit_summary[10][N_OF_METRICS][2];
	read_stats_table(digit_summary);

	//print_digit_metrics(height, width, pixels, digit_stats);

	return digit_by_metric_prob(digit_summary, digit_stats, prob_points);
}