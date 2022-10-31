#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "Canvas.h"
#include "Camera.h"
#include "Model.h"

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
        return model = mdl::rotateX(degree);
    }

    mat4 rotateY(double degree) {
        mat4 model;
        return model = mdl::rotateY(degree);
    }

    mat4 rotateZ(double degree) {
        mat4 model;
        return model = mdl::rotateZ(degree);
    }

    mat4 transport(vec3 r) {
        mat4 model;
        return model = mdl::transport(r);
    }

    mat4 scale(vec3 ratio) {
        mat4 model;
        return model = mdl::scale(ratio);
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

        // for (int &i : frameBuf) i = 1;

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
    mdl::Model donut;
    std::vector<float> depthBuf;
    std::vector<int>   frameBuf;

    mat4 Model;
};