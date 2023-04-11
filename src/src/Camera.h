#pragma once

#include "Matrix.h"
#include "Canvas.h"

class Camera {
public:
    Camera() { init(); }

    void init() {
        camPos   = vec4(0, 0, 10, 1);
        camDir   = vec3(0, 0, -1);
        camUp    = vec3(0, 1,  0);
        camRight = cross(camDir, camUp);
        n = -0.5;
        f = -50;
        fov = 45;
        aspectRatio = 1;
    }

    void setPos(vec3 position) {
        camPos = embed<4>(position);
    }

    mat4 view() {
        mat4 view, Tview, Rview;
        Tview = {{{1, 0, 0, -camPos.x}, 
                  {0, 1, 0, -camPos.y}, 
                  {0, 0, 1, -camPos.z}, 
                  {0, 0, 0,         1}}};
        Rview = {{{camRight.x, camRight.y, camRight.w, 0},
                  {   camUp.x,    camUp.y,    camUp.w, 0},
                  { -camDir.x,  -camDir.y,  -camDir.w, 0},
                  {         0,          0,          0, 1}}};
        return view = Rview*Tview;
    }

    mat4 projection() {
        mat4 projection, perspective, orthogonal;
        float width, height;
        height = -2*n*tan(fov/2);
        width  = height*aspectRatio;

        perspective = {{{n, 0,   0,    0},
                        {0, n,   0,    0},
                        {0, 0, n+f, -n*f},
                        {0, 0,   1,    0}}};

        mat4 i = {{{2/width,        0,       0, 0},
                   {      0, 2/height,       0, 0},
                   {      0,        0, 2/(n-f), 0},
                   {      0,        0,       0, 1}}};

        mat4 j = {{{1, 0, 0,        0},
                   {0, 1, 0,        0},
                   {0, 0, 1, -(n+f)/2},
                   {0, 0, 0,        1}}};

        orthogonal = i * j;

        return projection = orthogonal * perspective;
    }

public:
    vec4 camPos;
    vec3 camDir, camUp, camRight;
    float fov, aspectRatio;
    float n, f;
};