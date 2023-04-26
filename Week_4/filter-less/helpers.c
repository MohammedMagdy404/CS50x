#include "helpers.h"
#include <math.h>
#define red '0'
#define green '1'
#define blue '2'

RGBTRIPLE avg = {0};
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg.rgbtBlue = image[i][j].rgbtGreen;
            avg.rgbtRed = image[i][j].rgbtRed;
            avg.rgbtGreen = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = (avg.rgbtBlue + avg.rgbtGreen + avg.rgbtRed) / 3.0 + 0.5;
            image[i][j].rgbtGreen = (avg.rgbtBlue + avg.rgbtGreen + avg.rgbtRed) / 3.0 + 0.5;
            image[i][j].rgbtRed = (avg.rgbtBlue + avg.rgbtGreen + avg.rgbtRed) / 3.0 + 0.5;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sebiaRed = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue + 0.5);
            float sebiaGreen = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue + 0.5);
            float sebiaBlue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue + 0.5);

            if (sebiaBlue > 0xff)
                image[i][j].rgbtBlue = 0xff;
            else
                image[i][j].rgbtBlue = sebiaBlue;

            if (sebiaGreen > 0xff)
                image[i][j].rgbtGreen = 0xff;
            else
                image[i][j].rgbtGreen = sebiaGreen;

            if (sebiaRed > 0xff)
                image[i][j].rgbtRed = 0xff;
            else
                image[i][j].rgbtRed = sebiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img;
    for (int i = 0; i < height; i++)
    {
        int idx = 0;
        for (int j = 0; (j < width / 2); j++)
        {
            img = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = img;
            idx++;
        }
    }

    return;
}

// Blur image

int blurpixel(int height, int width, RGBTRIPLE copy[height][width], int idx1, int idx2, char color)
{
    float sum = 0;
    int count = 0;
    for (int i = idx1 - 1; i <= idx1 + 1; i++)
    {
        for (int j = idx2 - 1; j <= idx2 + 1; j++)
        {
            if (i < 0 || j < 0 || i >= height || j >= width)
                continue;
            /* if (i == idx1 && j == idx2)
                continue; */
            switch (color)
            {
            case red:
                sum += copy[i][j].rgbtRed;
                break;
            case green:
                sum += copy[i][j].rgbtGreen;
                break;
            case blue:
                sum += copy[i][j].rgbtBlue;
                break;
            }
            count++;
        }
    }
    return round(sum / count);
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j].rgbtRed = blurpixel(height, width, copy, i, j, red);
            image[i][j].rgbtGreen = blurpixel(height, width, copy, i, j, green);
            image[i][j].rgbtBlue = blurpixel(height, width, copy, i, j, blue);
        }
    }

    return;
}
