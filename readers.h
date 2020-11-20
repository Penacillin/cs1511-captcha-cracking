#ifndef READERS_H
#define READERS_H

int read_pbm(char filename[], int height, int width, int pixels[height][width]);
int get_pbm_dimensions(char filename[], int *height, int *width);

#endif