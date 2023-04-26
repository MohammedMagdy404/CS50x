#include "helpers.h"
#include <math.h>
#define red '0'
#define green '1'
#define blue '2'

// Convert image to grayscale
RGBTRIPLE avg = {0};
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

// Detect edges

int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

int edgepixel(int height, int width, RGBTRIPLE copy[height][width], int i, int j, char color)
{
    int sumx = 0;
    int sumy = 0;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (i - 1 + x < 0 || i - 1 + x >= height || j - 1 + y < 0 || j - 1 + y >= width)
                continue;

            switch (color)
            {
            case red:
                sumx += copy[i - 1 + x][j - 1 + y].rgbtRed * gx[x][y];
                sumy += copy[i - 1 + x][j - 1 + y].rgbtRed * gy[x][y];
                break;
            case green:
                sumx += copy[i - 1 + x][j - 1 + y].rgbtGreen * gx[x][y];
                sumy += copy[i - 1 + x][j - 1 + y].rgbtGreen * gy[x][y];
                break;
            case blue:
                sumx += copy[i - 1 + x][j - 1 + y].rgbtBlue * gx[x][y];
                sumy += copy[i - 1 + x][j - 1 + y].rgbtBlue * gy[x][y];
                break;
            }
        }
    }
    return round(sqrt(sumx * sumx + sumy * sumy));
}
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            image[i][j].rgbtRed = fmin(edgepixel(height, width, copy, i, j, red), 255);
            image[i][j].rgbtGreen = fmin(edgepixel(height, width, copy, i, j, green), 255);
            image[i][j].rgbtBlue = fmin(edgepixel(height, width, copy, i, j, blue), 255);
        }
    }

    return;
}
