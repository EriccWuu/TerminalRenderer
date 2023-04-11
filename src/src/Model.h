#pragma once

#include <cmath>
#include <vector>
#include "Matrix.h"

#define PI 3.1415926535

struct Model {
    double r1 = 1, r2 = 2;
    std::vector<vec4> vertexs;

    void init() {
        // donut
        for (float i = 0; i < 2*PI; i += 0.07)
            for (float j = 0; j < 360; j += 1) vertexs.push_back(rotateZ(j)*vec4(2+r1*cos(i), 0, r1*sin(i), 1));

        // circle
        // float r = 3;
        // for (double i = 0; i < 2*PI; i += 0.07) vertexs.push_back(vec4(r*cos(i), r*sin(i), 0, 1));
        // for (float i = 0; i < 2*PI; i += 0.02)
        //     for (int j = 0; j < circle.size(); j++) vertexs.push_back(rotateY(i)*circle[j]);
    }

    static mat4 rotateX(double degree);
    static mat4 rotateY(double degree);
    static mat4 rotateZ(double degree);
    static mat4 rotate(vec3 n, double degree);
    static mat4 transport(vec3 destination);
    static mat4 scale(vec3 ratio);

};

mat4 Model::rotateX(double degree) {
    double radian = degree*PI/180;
    mat4 R;
    R = {{{1,            0,            0, 0},
            {0,  cos(radian),  sin(radian), 0},
            {0, -sin(radian),  cos(radian), 0},
            {0,            0,            0, 1}}};
    return R;
}

mat4 Model::rotateY(double degree) {
    double radian = degree*PI/180;
    mat4 R;
    R = {{{cos(radian), 0, -sin(radian), 0},
            {          0, 1,            0, 0},
            {sin(radian), 0,  cos(radian), 0},
            {          0, 0,            0, 1}}};
    return R;
}

mat4 Model::rotateZ(double degree) {
    double radian = degree*PI/180;
    mat4 R;
    R = {{{ cos(radian),  sin(radian), 0, 0},
            {-sin(radian),  cos(radian), 0, 0},
            {           0,            0, 1, 0},
            {           0,            0, 0, 1}}};
    return R;
}

mat4 Model::rotate(vec3 n, double degree) {
    mat4 R = mat4::identity();
    return R;
}

mat4 Model::transport(vec3 destination) {
    double x = destination.x;
    double y = destination.y;
    double z = destination.w;
    mat4 T;
    T = {{{1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0, 0, 0, 1}}};
    return T;
}

mat4 Model::scale(vec3 ratio) {
    double x = ratio.x;
    double y = ratio.y;
    double z = ratio.w;
    mat4 S;
    S = {{{x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, 1}}};
    return S;
}