#ifndef METRIC_CALCULATOR_H
#define METRIC_CALCULATOR_H

#include "data.h"
#define METRIC_INF 30

int digit(int height, int width, int pixels[height][width], double digit_stats[N_OF_METRICS]);
int calculate_digit(int height, int width, int pixels[height][width]);
int digit_by_metric_prob(double digit_summary[10][N_OF_METRICS][2], double digit_metrics[N_OF_METRICS], double prob_points[10][N_OF_METRICS]);

#endif