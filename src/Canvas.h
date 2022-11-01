#pragma once
#include <iostream>
#include <stdlib.h>
#include "Matrix.h"

const char pixel[] = ".,-~:;=!*#$@";

class Canvas {
public:
    Canvas() { init(); }
    Canvas(int len, int wid): height(len), width(wid) {}

    void init() {
        height = 50;
        width  = 50;
    }
    void setBuf(std::vector<int> &buf) { buffer = buf; }
    void draw() {
        system("cls");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (buffer[(height-1-i)*width+j] == 0) printf("  ");
                else printf(" %c", pixel[0]);
            }
            printf("\n");
        }
    }

public:
    int height;
    int width;
    std::vector<int> buffer;
};

