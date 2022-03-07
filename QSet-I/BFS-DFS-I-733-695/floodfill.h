#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <vector>
using namespace std;

/**
 * An image is represented by an m x n integer grid image where image[i][j] represents
 * the pixel value of the image.
 *
 * You are also given three integers sr, sc, and newColor. You should perform a flood
 * fill on the image starting from the pixel image[sr][sc].
 *
 * To perform a flood fill, consider the starting pixel, plus any pixels connected
 * 4-directionally to the starting pixel of the same color as the starting pixel, plus
 * any pixels connected 4-directionally to those pixels (also with the same color), and
 * so on. Replace the color of all of the aforementioned pixels with newColor.
 *
 * Return the modified image after performing the flood fill.
 *
 * Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
 * Output: [[2,2,2],[2,2,0],[2,0,1]]
 *
 * From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel),
 * all pixels connected by a path of the same color as the starting pixel (i.e., the blue
 * pixels) are colored with the new color. Note the bottom corner is not colored 2,
 * because it is not 4-directionally connected to the starting pixel.
 */

vector<vector<int>> floodFill_sol1(vector<vector<int>>& image, int sr, int sc, int newColor);
vector<vector<int>> floodFill_sol2(vector<vector<int>>& image, int sr, int sc, int newColor);

#endif // FLOODFILL_H
