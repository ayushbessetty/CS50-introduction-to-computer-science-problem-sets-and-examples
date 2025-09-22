#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtRed = a;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tempr = 0, tempg = 0, tempb = 0;
            tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tempr;

            tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tempg;

            tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tempb;
        }
    }
    return;
}

// Blur image
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
            int sumr = copy[i][j].rgbtRed;
            int sumg = copy[i][j].rgbtGreen;
            int sumb = copy[i][j].rgbtBlue;
            int count = 1;
            if ((i - 1) >= 0)
            {
                sumr += copy[i - 1][j].rgbtRed;
                sumg += copy[i - 1][j].rgbtGreen;
                sumb += copy[i - 1][j].rgbtBlue;
                count++;

                if ((j - 1) >= 0)
                {
                    sumr += copy[i - 1][j - 1].rgbtRed;
                    sumg += copy[i - 1][j - 1].rgbtGreen;
                    sumb += copy[i - 1][j - 1].rgbtBlue;
                    count++;
                }

                if ((j + 1) < width)
                {
                    sumr += copy[i - 1][j + 1].rgbtRed;
                    sumg += copy[i - 1][j + 1].rgbtGreen;
                    sumb += copy[i - 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            if ((i + 1) < height)
            {
                sumr += copy[i + 1][j].rgbtRed;
                sumg += copy[i + 1][j].rgbtGreen;
                sumb += copy[i + 1][j].rgbtBlue;
                count++;

                if ((j - 1) >= 0)
                {
                    sumr += copy[i + 1][j - 1].rgbtRed;
                    sumg += copy[i + 1][j - 1].rgbtGreen;
                    sumb += copy[i + 1][j - 1].rgbtBlue;
                    count++;
                }

                if ((j + 1) < width)
                {
                    sumr += copy[i + 1][j + 1].rgbtRed;
                    sumg += copy[i + 1][j + 1].rgbtGreen;
                    sumb += copy[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            if ((j - 1) >= 0)
            {
                sumr += copy[i][j - 1].rgbtRed;
                sumg += copy[i][j - 1].rgbtGreen;
                sumb += copy[i][j - 1].rgbtBlue;
                count++;
            }
            if ((j + 1) < width)
            {
                sumr += copy[i][j + 1].rgbtRed;
                sumg += copy[i][j + 1].rgbtGreen;
                sumb += copy[i][j + 1].rgbtBlue;
                count++;
            }

            image[i][j].rgbtRed = round((float) sumr / (float) count);
            image[i][j].rgbtGreen = round((float) sumg / (float) count);
            image[i][j].rgbtBlue = round((float) sumb / (float) count);
        }
    }
    return;
}

// Detect edges
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

    // using sobel formulae and gx and gy kernerls
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumrx = 0;
            int sumgx = 0;
            int sumbx = 0;
            int sumry = 0;
            int sumgy = 0;
            int sumby = 0;

            if ((i - 1) >= 0)
            {
                sumry += (copy[i - 1][j].rgbtRed * (-2));
                sumgy += (copy[i - 1][j].rgbtGreen * (-2));
                sumby += (copy[i - 1][j].rgbtBlue * (-2));

                if ((j - 1) >= 0)
                {
                    sumrx += (copy[i - 1][j - 1].rgbtRed * (-1));
                    sumgx += (copy[i - 1][j - 1].rgbtGreen * (-1));
                    sumbx += (copy[i - 1][j - 1].rgbtBlue * (-1));
                    sumry += (copy[i - 1][j - 1].rgbtRed * (-1));
                    sumgy += (copy[i - 1][j - 1].rgbtGreen * (-1));
                    sumby += (copy[i - 1][j - 1].rgbtBlue * (-1));
                }

                if ((j + 1) < width)
                {
                    sumrx += copy[i - 1][j + 1].rgbtRed;
                    sumgx += copy[i - 1][j + 1].rgbtGreen;
                    sumbx += copy[i - 1][j + 1].rgbtBlue;
                    sumry += (copy[i - 1][j + 1].rgbtRed * (-1));
                    sumgy += (copy[i - 1][j + 1].rgbtGreen * (-1));
                    sumby += (copy[i - 1][j + 1].rgbtBlue * (-1));
                }
            }

            if ((i + 1) < height)
            {
                sumry += (copy[i + 1][j].rgbtRed * 2);
                sumgy += (copy[i + 1][j].rgbtGreen * 2);
                sumby += (copy[i + 1][j].rgbtBlue * 2);

                if ((j - 1) >= 0)
                {
                    sumrx += (copy[i + 1][j - 1].rgbtRed * (-1));
                    sumgx += (copy[i + 1][j - 1].rgbtGreen * (-1));
                    sumbx += (copy[i + 1][j - 1].rgbtBlue * (-1));
                    sumry += copy[i + 1][j - 1].rgbtRed;
                    sumgy += copy[i + 1][j - 1].rgbtGreen;
                    sumby += copy[i + 1][j - 1].rgbtBlue;
                }

                if ((j + 1) < width)
                {
                    sumrx += copy[i + 1][j + 1].rgbtRed;
                    sumgx += copy[i + 1][j + 1].rgbtGreen;
                    sumbx += copy[i + 1][j + 1].rgbtBlue;
                    sumry += copy[i + 1][j + 1].rgbtRed;
                    sumgy += copy[i + 1][j + 1].rgbtGreen;
                    sumby += copy[i + 1][j + 1].rgbtBlue;
                }
            }

            if ((j - 1) >= 0)
            {
                sumrx += (copy[i][j - 1].rgbtRed * (-2));
                sumgx += (copy[i][j - 1].rgbtGreen * (-2));
                sumbx += (copy[i][j - 1].rgbtBlue * (-2));
            }
            if ((j + 1) < width)
            {
                sumrx += (copy[i][j + 1].rgbtRed * 2);
                sumgx += (copy[i][j + 1].rgbtGreen * 2);
                sumbx += (copy[i][j + 1].rgbtBlue * 2);
            }

            if (round(sqrt(pow(sumrx, 2) + pow(sumry, 2))) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(sqrt(pow(sumrx, 2) + pow(sumry, 2)));
            }

            if (round(sqrt(pow(sumgx, 2) + pow(sumgy, 2))) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(sqrt((pow(sumgx, 2) + pow(sumgy, 2))));
            }

            if (round(sqrt(pow(sumbx, 2) + pow(sumby, 2))) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(sqrt(pow(sumbx, 2) + pow(sumby, 2)));
            }
        }
    }
    return;
}
