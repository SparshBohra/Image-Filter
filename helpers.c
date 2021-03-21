#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            int x = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3;
            image[i][j].rgbtRed = round(x);
            image[i][j].rgbtBlue = round(x);
            image[i][j].rgbtGreen = round(x);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for ( int j = 0; j < width / 2; j++) {
            RGBTRIPLE test;

            test.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = test.rgbtRed;

            test.rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = test.rgbtBlue;

            test.rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = test.rgbtGreen;
        }
    }
    return;
}

// Blur the image
void blur(int height, int width, RGBTRIPLE image[height][width]) {

    RGBTRIPLE test[height][width];
    float avg = 0, testRed = 0, testBlue = 0, testGreen = 0;

    for (int i = 0; i < height; i++) {
        for ( int j = 0; j < width; j++) {
            for ( int k = -1; k < 2; k++) {
                for ( int l = -1; l < 2; l++) {
                    if (i + k >= 0 && j + l >= 0 && i + k < height && j + l < width) {
                        testRed += image[i + k][j + l].rgbtRed;
                        testBlue += image[i + k][j + l].rgbtBlue;
                        testGreen += image[i + k][j + l].rgbtGreen;
                        avg++;
                    }
                }
            }
            test[i][j].rgbtRed = round(testRed / avg);
            test[i][j].rgbtBlue = round(testBlue / avg);
            test[i][j].rgbtGreen = round(testGreen / avg);
            avg = 0; testRed = 0; testBlue = 0; testGreen = 0;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = test[i][j];
        }
    }
    return;
}

// Vertical and horizontal edge detection
void edges(int height, int width, RGBTRIPLE image[height][width]) {

    float testRedx = 0, testBluex = 0, testGreenx = 0, testRedy = 0, testBluey = 0, testGreeny = 0;
    RGBTRIPLE test2[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            for ( int k = -1; k < 2; k++) {
                for ( int l = -1; l < 2; l++) {
                    if (i + k >= 0 && j + l >= 0 && i + k < height && j + l < width) {
                        testRedx += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        testBluex += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                        testGreenx += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];

                        testRedy += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                        testBluey += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                        testGreeny += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    }
                }
            }
            int a = round(sqrt((pow(testRedx, 2) + pow(testRedy, 2))));
            int b = round(sqrt((pow(testBluex, 2) + pow(testBluey, 2))));
            int c = round(sqrt((pow(testGreenx, 2) + pow(testGreeny, 2))));
            testRedx = 0; testBluex = 0; testGreenx = 0;
            testRedy = 0; testBluey = 0; testGreeny = 0;

            if (a > 255) {
                a = 255;
            }
            if (b > 255) {
                b = 255;
            }
            if (c > 255) {
                c = 255;
            }

            test2[i][j].rgbtRed = a;
            test2[i][j].rgbtBlue = b;
            test2[i][j].rgbtGreen = c;
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b] = test2[a][b];
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]){

    int newRed = 0, newBlue = 0, newGreen = 0;

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            // These specific values are the values for sepia tone that are recommended by Microsoft.
            newRed   = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            newGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue); 
            newBlue  = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);

            // If any of these output values is greater than 255, we set it to 255.
            image[i][j].rgbtRed   = (newRed > 255) ? 255 :newRed;
            image[i][j].rgbtBlue  = (newBlue > 255) ? 255 : newBlue;
            image[i][j].rgbtGreen = (newGreen > 255) ? 255 :newGreen;

        }
    }

    return;

}