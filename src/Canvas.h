#pragma once
#include <iostream>
#include <stdlib.h>
#include "Matrix.h"

const char pixel[] = ".,-~:;=!*#$@";

class Canvas {
public:
    Canvas() { init(); }
    Canvas(int len, int wid, char **buf = NULL): height(len), width(wid), buffer(buf) {}

    void init() {
        height = 50;
        width = 50;
    }
    void setBuf(char **buf) { buffer = buf; }
    void draw() {
        system("cls");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (buffer[i][j] == '\0') printf("  ");
                else printf("%c", buffer[i][j]);
            }
            printf("\n");
        }
    }

public:
    int height;
    int width;
    char **buffer = NULL;
};

