#include "data.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readers.h"
#include "metric_calculator.h"
#include "stats.h"

// Returns the total sum of a particular metric
double getSum(double digit_metrics[100][N_OF_METRICS], Metric metric)
{
	double sum = 0;
	for (int i = 0; i < 100; i++)
	{
		sum += digit_metrics[i][metric];
	}
	return sum;
}

// Returns the average of a particular metric
double getAverage(double digit_metrics[100][N_OF_METRICS], Metric metric)
{
	return getSum(digit_metrics, metric) / 100;
}

// Returns the standard deviation of a particular metric
double get_stddevS(double digit_metrics[100][N_OF_METRICS], Metric metric)
{
	double mean = getAverage(digit_metrics, metric);
	double square_difference_sum = 0;
	for (int i = 0; i < 100; i++)
	{
		square_difference_sum += (digit_metrics[i][metric] - mean)*(digit_metrics[i][metric] - mean);
	}
	square_difference_sum /= 98;
	return sqrt(square_difference_sum);
}

// Reads the digit statistics data from file and puts it into the array passed in
void read_stats_table(double digit_stats[10][N_OF_METRICS][2])
{
	for (int dig = 0; dig < 10; dig++)
	{
		for (int i = 0; i < N_OF_METRICS; i++)
		{
			digit_stats[dig][i][0] = statsArray[dig][i * 2 + 1];
			digit_stats[dig][i][1] = statsArray[dig][i * 2 + 2];
		}
	}

	return;
}

// Get the statistical data for a single digit into the digit_stat array
int getStatsFor(int dig, double digit_stat[100][N_OF_METRICS])
{
	int height, width;
	char filename[30] = { 0 };

	for (int i = 0; i <= 99; i++)
	{
		// Construct the file name automatically
		strcpy(filename, "./digit/"); // ./digit/
		sprintf(filename + 8, "%d", dig); // .digit/x
		strcpy(filename + 9, "_"); // ./digit/x_
		sprintf(filename + 10, "%02d", i); // ./digit/x_xx
		strcat(filename, ".pbm"); // ./digit/x_xx.pbm

		// read the file
		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		// Parse file through digit to get information, and store it
		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			digit(height, width, pixels, digit_stat[i]);
		}
	}

	printf("\nAVERAGE Metrics for %d :\n", dig);
	//print_image(box_height, box_width, box_pixels);
	printf("Horizontal Balance : %.8lf\n",  getAverage(digit_stat, mhorBalance));
	printf("Vertical Balance  : %lf\n", getAverage(digit_stat, mverBalance));
	printf("Tallness          : %lf\n", getAverage(digit_stat, mtallness));
	printf("Number of holes   : %lf\n", getAverage(digit_stat, mholes));
	printf("hole size fraction: %lf\n", getAverage(digit_stat, mhole_size_fraction));
	printf("desnity           : %lf\n", getAverage(digit_stat, mdensity));
	printf("max vertical	  : %lf\n", getAverage(digit_stat, mmaxVertical));
	printf("max horizontal	  : %lf\n", getAverage(digit_stat, mmaxHorizontal));
	printf("average width	  : %lf\n", getAverage(digit_stat, maverageWidth));
	printf("middleleeft dens  : %lf\n", getAverage(digit_stat, mmidLeftDensity));
	printf("bot right   dens  : %lf\n", getAverage(digit_stat, mbotRightDensity));
	printf("vert pos of hole  : %lf\n", getAverage(digit_stat, mvertPosOfHole));
	printf("SD of hor balance : %lf\n", getAverage(digit_stat, msdHorBalance));
	printf("mean width of 3 x : %lf\n", getAverage(digit_stat, mmeanWidthOfThree));
	printf("   hor bal top    : %lf\n", getAverage(digit_stat, mhorBalTop));
	printf("steepst top left  : %lf\n", getAverage(digit_stat, msteepestFallTopLeft));
	printf("steepst bot righ  : %lf\n", getAverage(digit_stat, msteepestFallBotRight));
	//printf("smoothness mid  l : %lf\n", getAverage(digit_stat, msmoothnessMidLeft));
	printf("steepst mid left  : %lf\n", getAverage(digit_stat, msteepestFallMidLeft));
	printf("bot hor balance   : %lf\n", getAverage(digit_stat, mbotHorBalance));
	printf("deepest left bot r: %lf\n", getAverage(digit_stat, mdeepestLeftBotRight));
	printf("vertical lines bot: %lf\n", getAverage(digit_stat, mvertsBot));
	printf("max vert diff bot : %lf\n", getAverage(digit_stat, mmaxDiffVertBot));
	printf("SD bot left grad  : %lf\n", getAverage(digit_stat, mSDgradBotLeft));
	printf("SD bot right grad : %lf\n", getAverage(digit_stat, mSDgradBotRight));
	printf("top right big delt: %lf\n", getAverage(digit_stat, mdeltaTR));
	printf("bot left steepeest: %lf\n", getAverage(digit_stat, msteepestFallBotLeft));
	printf("top right stepeest: %lf\n", getAverage(digit_stat, msteepestFallTopRight));
	printf("smoothness mid lef: %lf\n", getAverage(digit_stat, msmoothnessMidLeft));
	printf("fraction 3 width  : %lf\n", getAverage(digit_stat, mfractionThree));
	printf("mean mid right gra: %lf\n", getAverage(digit_stat, maverageGradMidRight));
	printf("sahllow bot left  : %lf\n", getAverage(digit_stat, mshallowestBotLeft));
	printf("Delta bot left    : %lf\n", getAverage(digit_stat, mdeltaBL));
	printf("smooth mid right  : %lf\n", getAverage(digit_stat, msmoothnessMidRight));
	printf("max grad change BR: %lf\n", getAverage(digit_stat, mmaxGradChangeBR));
	printf("max grad change BL: %lf\n", getAverage(digit_stat, mmaxGradChangeBL));
	printf("max hor bot width : %lf\n", getAverage(digit_stat, mmaxHorBot));
	printf("max diff bot width: %lf\n", getAverage(digit_stat, mmaxWidthDiffBot));
	printf("top third right   : %lf\n", getAverage(digit_stat, mtopThirdRight));
	printf("\n");


	return 0;
}

// Runs every digit through the program, then writes its averages and 
// standard deviation to file, so that it can be used for cracking
void create_summary_csv()
{
	FILE* stats;
	FILE* statsh;
	stats = fopen("./stats.csv", "w");
	statsh = fopen("./stats.h", "w");
	double digitsStats[10][100][N_OF_METRICS];

	fprintf(statsh, "#pragma once\n//WRITTEN BY PROGRAM, DO NOT EDIT\ndouble statsArray[10][%d] = {", 2 * N_OF_METRICS + 1);

	for (int digit = 0; digit <= 9; digit++)
	{

		getStatsFor(digit, digitsStats[digit]);
		fprintf(stats, "%d,", digit);
		fprintf(statsh, "{%d", digit);
		for (int i = 0; i < N_OF_METRICS; i++)
		{
			double stdDev = get_stddevS(digitsStats[digit], i);
			/*
				Following fixes up a few digits that get rejected too strongly
			*/
			if (i == msteepestFallBotLeft)
				stdDev *= 3;
			if (i == mmidLeftDensity && digit == 3)
				stdDev *= 2;
			if (i == mbotHorBalance && digit == 3)
				stdDev *= 2;
			if (i == mdeepestLeftBotRight && digit == 3)
				stdDev *= 2;
			if (i == mdensity)
				stdDev *= 2;
			if (i == maverageWidth && digit == 3)
				stdDev *= 2;
			if (i == msdHorBalance && digit == 3)
				stdDev *= 2;
			if (i == mmaxVertical && digit == 3)
				stdDev *= 2;
			if (i == mfractionThree && digit == 2)
				stdDev *= 5;
			if (i == maverageWidth && digit == 2)
				stdDev *= 4;
			if (i == mbotHorBalance && digit == 2)
				stdDev *= 3;
			if (i == mmaxVertical && digit == 2)
				stdDev *= 3;
			if (i == mdeepestLeftBotRight && digit == 2)
				stdDev *= 2;
			if (i == msmoothnessMidLeft && digit == 7)
				stdDev *= 4;
			if (i == maverageWidth && digit == 9)
				stdDev *= 3;
			if (i == mmeanWidthOfThree && digit == 2)
				stdDev *= 3;
			if (i == msmoothnessMidRight && digit == 3)
				stdDev *= 3;
			if (i == mmaxHorBot && digit == 3)
				stdDev *= 2;
			if (i == mmaxWidthDiffBot && digit == 3)
				stdDev *= 3;
			if (i == msmoothnessMidRight && digit == 5)
				stdDev *= 5;
			if (i == msdHorBalance && digit == 5)
				stdDev *= 4;
			fprintf(stats, "%lf,%lf,",
				getAverage(digitsStats[digit], i),
				stdDev
			);

			fprintf(statsh, ",%lf,%lf",
				getAverage(digitsStats[digit], i),
				stdDev
			);
		}
		fprintf(stats, "\n");
		if (digit != 9)
			fprintf(statsh, "},\n");
		else
			fprintf(statsh, "}};\n");
	}
}