#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width])
{
    int column_sum = 0;
    int n_black_pixels = 0;

    for(int i = 0; i < width; i++)
    {
        int currColumnSum = 0;
        for(int j = 0; j < height; j++)
        {
            if(pixels[j][i])
            {
                // if pixel is black
                currColumnSum++;
                n_black_pixels++;
            }
        }
        // after found sum of black pixels in current column, add to total
        column_sum += currColumnSum * i;
    }

    return ((double) column_sum/n_black_pixels + 0.5)/width;
}
