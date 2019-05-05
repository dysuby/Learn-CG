#include "Bresenham.h"

inline void push_back(std::vector<float> &v, int i1, int i2, int i3 = 0) {
    v.push_back((float)i1);
    v.push_back((float)i2);
    v.push_back((float)i3);
}


std::vector<float> BresenhamLine(int x0, int y0, int x1, int y1) {
    std::vector<float> ret;
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int deltax = x1 - x0;
    int deltay = std::abs(y1 - y0);
    int error = deltax / 2;
    int ystep;
    int y = y0;

    if (y0 < y1) ystep = 1;
    else ystep = -1;
    
    for (int x = x0; x <= x1; ++x) {
        if (steep) push_back(ret, y, x); 
        else push_back(ret, x, y);
        error -= deltay;
        if (error < 0) {
            y += ystep;
            error += deltax;
        }
    }
    return ret;
}

std::vector<float> BresenhamCircle(int xc, int yc, int radius) {
    std::vector<float> ret;
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    while (x <= y) {
        push_back(ret, xc + x, yc + y);
        push_back(ret, xc - x, yc + y);
        push_back(ret, xc + x, yc - y);
        push_back(ret, xc - x, yc - y);
        push_back(ret, xc + y, yc + x);
        push_back(ret, xc - y, yc + x);
        push_back(ret, xc + y, yc - x);
        push_back(ret, xc - y, yc - x);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            --y;
        }
        ++x;
    }
    return ret;
}

std::vector<float> rasterize(int vertices[3][2]) {
    // Find the bbox
    int minx = std::min(vertices[0][0], std::min(vertices[1][0], vertices[2][0]));
    int maxx = std::max(vertices[0][0], std::max(vertices[1][0], vertices[2][0]));
    int miny = std::min(vertices[0][1], std::min(vertices[1][1], vertices[2][1]));
    int maxy = std::max(vertices[0][1], std::max(vertices[1][1], vertices[2][1]));

    // Calculate lines 
    Line l1 = Line(vertices[0][0], vertices[0][1], vertices[1][0], vertices[1][1]);
    Line l2 = Line(vertices[0][0], vertices[0][1], vertices[2][0], vertices[2][1]);
    Line l3 = Line(vertices[1][0], vertices[1][1], vertices[2][0], vertices[2][1]);

    float v1 = l1.A * vertices[2][0] + l1.B * vertices[2][1] + l1.C;
    float v2 = l2.A * vertices[1][0] + l2.B * vertices[1][1] + l2.C;
    float v3 = l3.A * vertices[0][0] + l3.B * vertices[0][1] + l3.C;

    std::vector<float> ret;
    for (int i = minx; i <= maxx; ++i) {
        float pu = l1.A * i + l1.C;
        float pv = l2.A * i + l2.C;
        float pw = l3.A * i + l3.C;
        for (int j = miny; j <= maxy; ++j) {
            if (!((pu + l1.B * j) * v1 < 0 ||
                (pv + l2.B * j) * v2 < 0 ||
                (pw + l3.B * j) * v3 < 0)) {
                push_back(ret, i, j);
            }
        }
    }
    return ret;
}