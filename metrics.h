#ifndef METRICS_H
#define METRICS_H

double get_vertical_balance(int height, int width, int pixels[height][width]);
double get_horizontal_balance(int height, int width, int pixels[height][width]);
double get_tallness(int height, int width);
double get_holes(int height, int width, int pixels[height][width]);
double get_hole_size_fraction(int height, int width, int pixels[height][width]);
double get_density(int height, int width, int pixels[height][width]);
double get_max_vertical(int height, int width, int pixels[height][width]);
double get_max_horizontal(int height, int width, int pixels[height][width]);
double get_average_width(int height, int width, int pixels[height][width]);
double get_middle_left_density(int height, int width, int pixels[height][width]);
double get_bottom_right_density(int height, int width, int pixels[height][width]);
double get_vert_pos_of_island(int height, int width, int island[height][width], int indi);
double get_SD_hor_bal(int height, int width, int pixels[height][width]);
double get_mean_width_of_three(int height, int width, int pixels[height][width]);
double get_SD_dist_from_left_first_third(int height, int width, int pixels[height][width]);
double get_hor_bal_top(int height, int width, int pixels[height][width]);
double get_max_fall_top_left(int height, int width, int pixels[height][width]);
double get_max_fall_bot_right(int height, int width, int pixels[height][width]);
double get_max_fall_mid_left(int height, int width, int pixels[height][width]);
double get_smoothness_mid_left(int height, int width, int pixels[height][width]);
double get_bot_horizontal_balance(int height, int width, int pixels[height][width]);
double get_deepest_left_bot_right(int height, int width, int pixels[height][width]);
double get_verts_bot(int height, int width, int pixels[height][width]);
double get_max_diff_vert(int height, int width, int pixels[height][width]);
double get_SD_grad_bot_left(int height, int width, int pixels[height][width]);
double get_SD_grad_bot_right(int height, int width, int pixels[height][width]);
double get_largest_delta_TR(int height, int width, int pixels[height][width]);
double get_max_fall_bot_left(int height, int width, int pixels[height][width]);
double get_max_fall_top_right(int height, int width, int pixels[height][width]);
double get_fraction_three(int height, int width, int pixels[height][width]);
double get_average_grad_mid_right(int height, int width, int pixels[height][width]);
double get_shallowest_bot_left(int height, int width, int pixels[height][width]);
double get_largest_delta_BL(int height, int width, int pixels[height][width]);
double get_smoothness_mid_right(int height, int width, int pixels[height][width]);
double get_max_grad_change_BR(int height, int width, int pixels[height][width]);
double get_max_grad_change_BR(int height, int width, int pixels[height][width]);
double get_max_grad_change_BL(int height, int width, int pixels[height][width]);
double get_max_hor_bot(int height, int width, int pixels[height][width]);
double get_max_width_diff_bot(int height, int width, int pixels[height][width]);
double get_top_third_right(int height, int width, int pixels[height][width]);

#endif