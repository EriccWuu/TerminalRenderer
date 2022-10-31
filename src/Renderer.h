#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "Canvas.h"
#include "Camera.h"

#define PI 3.14

struct RenderObj {
    double r1 = 1, r2 = 2;
    std::vector<vec4> vertexs;

    void init() {
        // donut
        // std::vector<vec4> circle1;
        // for (float i = 0; i < 2*PI; i += 0.07)
        //     for (float j = 0; j < 2*PI; j += 0.02) circle1.push_back(vec4(2+r1*cos(i), 0, r1*sin(j), 1));

        // for (float i = 0; i < 2*PI; i += 0.02)
        //     for (int j = 0; j < circle1.size(); j++) vertexs.push_back(rotateZ(i)*circle1[j]);

        // circle
        std::vector<vec4> circle;
        float r = 1;
        for (float i = 0; i < 2*PI; i += 0.007)
            circle.push_back(vec4(r*cos(i), r*sin(i), 0, 1));
        for (vec4 v : circle)
            vertexs.push_back(v);
        // for (float i = 0; i < 2*PI; i += 0.002)
        //     for (int j = 0; j < circle.size(); j++) vertexs.push_back(rotateY(i)*circle[j]);
    }

    mat4 rotateX(double degree) {
        mat4 R;
        R = {{{1,  0,            0          , 0},
              {0,  cos(degree),  sin(degree), 0},
              {0, -sin(degree),  cos(degree), 0},
              {0,  0,            0          , 1}}};
        return R;
    }

    mat4 rotateY(double degree) {
        mat4 R;
        R = {{{cos(degree), 0, -sin(degree), 0},
              {0,           1,  0          , 0},
              {sin(degree), 0,  cos(degree), 0},
              {0,           0,  0,           1}}};
        return R;
    }

    mat4 rotateZ(double degree) {
        mat4 R;
        R = {{{ cos(degree),  sin(degree), 0, 0},
              {-sin(degree),  cos(degree), 0, 0},
              { 0,            0,           1, 0},
              { 0,            0,           0, 1}}};
        return R;
    }

    mat4 rotate(vec3 n, double degree);

    mat4 transport(vec3 destination) {
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

    mat4 scale(vec3 ratio) {
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
};

class Renderer {
public:
    Renderer() {
        donut.init();
        Model = mat4::identity();
        for (int i = 0; i < canvas.width * canvas.height; i++) {
            frameBuf.push_back(0);
            depthBuf.push_back(100);
        }
    }

    std::vector<vec4> getVertexs() {
        std::vector<vec4> v = donut.vertexs;
        return v;
    }

    mat4 rotateX(double degree) {
        mat4 model;
        return model = donut.rotateX(degree);
    }

    mat4 rotateY(double degree) {
        mat4 model;
        return model = donut.rotateY(degree);
    }

    mat4 rotateZ(double degree) {
        mat4 model;
        return model = donut.rotateZ(degree);
    }

    mat4 transport(vec3 r) {
        mat4 model;
        return model = donut.transport(r);
    }

    mat4 scale(vec3 ratio) {
        mat4 model;
        return model = donut.scale(ratio);
    }

    void setModelMat(mat4 model) {
        Model = model;
    }

    mat4 viewMat() {
        mat4 view;
        return view = camera.view();
    }

    mat4 projMat() {
        mat4 projection;
        return projection = camera.projection();
    }

    void draw() {
        std::vector<vec4> vert = donut.vertexs;
        // mat4 MVP = mat4::identity() * camera.projection() * camera.view();
        mat4 MVP = projMat() * viewMat() * Model;

        int width  = canvas.width;
        int height = canvas.height;

        float f1 = (100 - 0.1) / 2.0;
        float f2 = (100 + 0.1) / 2.0;

        for (vec4 &v : vert) {
            // MVP transform
            v = MVP * v;

            // projection division, transform to NDC
            v = v / v.w;

            // NDC to screen
            v.x = 0.5 * width  * (v.x + 1.0);
            v.y = 0.5 * height * (v.y + 1.0);
            v.z = v.z * f1 + f2;

            //
            int x = floor(v.x);
            int y = floor(v.y);
            // std::cout << x << " " << y << " " << v.z << std::endl;

            int ind = getIndex(x, y);
            if (v.z < depthBuf[ind]) {
                frameBuf[ind] = 1;
                depthBuf[ind] = v.z;
            }
        }

        canvas.setBuf(frameBuf);
        canvas.draw();

        // std::cout << "number of vertexs: " << vert.size() << std::endl;
        // std::cout << "MVP: "<< std::endl << MVP;
        // for (vec4 v : vert) std::cout << v << std::endl;
        // for (int i = 0; i < frameBuf.size(); i++) std::cout << frameBuf[i] << " " << depthBuf[i] << std::endl;
    }

    int getIndex(int x, int y) {
        return (canvas.height - 1 - y) * canvas.width + x;
    }

public:
    Canvas canvas;
    Camera camera;
    RenderObj donut;
    std::vector<float> depthBuf;
    std::vector<int>   frameBuf;

    mat4 Model, View, Proj;
};