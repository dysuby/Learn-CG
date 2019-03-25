#pragma once

#include <vector>
#include <algorithm>

struct Line {
    float A;
    float B;
    float C;
    
    Line(int x1, int y1, int x2, int y2) {
        A = (float)(y1 - y2);
        B = (float)(x2 - x1);
        C = (float)(x1 * y2 - x2 * y1);
    }
};

std::vector<float> BresenhamLine(int x1, int y1, int x2, int y2);

std::vector<float> BresenhamCircle(int x, int y, int radius);

std::vector<float> rasterize(int vertices[3][2]);