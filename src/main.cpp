#include <stdio.h>
#include <iostream>
#include <math.h>
#include "Matrix.h"
#include "Renderer.h"
// #include "geometry.h"

using namespace std;

void testMatrix() {
    vec3 a(1, 2, 1);
    vec3 b = a;
    vec3 c(1, 0, 1);

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "a + b: " << a + b << endl;
    cout << "a - b: " << a - b << endl;
    cout << "a * b: " << a * b << endl;
    cout << "a / 2: " << a / 2 << endl;
    cout << "Proj(a, c): " << proj(a, 3*c) << endl;
    cout << "a.slice<2,3>: " << slice<2,3>(a, 1, 2) << endl;
    cout << "a x c: " << cross(a, c) << endl;
    cout << "(0,0,-1) x (0,1,0): " << cross(vec3(0,0,-1), vec3(0,1,0)) << endl;
    cout << "a embed: " << embed<4>(a) << endl;

    mat3 m0;
    m0.rows[0] = vec3(1,2,1);
    m0.rows[1] = vec3(1,0,1);
    m0.rows[2] = vec3(2,1,0);
    mat3 m1;
    m1.rows[0] = vec3(1,0,2);
    m1.rows[1] = vec3(1,0,1);
    m1.rows[2] = vec3(1,1,0);
    cout << "m0: \n" << m0;
    cout << "identity: \n" << mat4::identity();
    cout << "m0.transpose: \n" << m0.transpose();
    cout << "m0.det: \n" << m0.det() << endl;
    cout << "m0.invertTranspose: \n" << m0.invertTranspose();
    cout << "m0.invert: \n" << m0.invert();
    cout << "3 * m0: \n" << 3 * m0 << endl<< m0 * 3;
    cout << "m0 + m1: \n" << m0 + m1;
    cout << "m0 - m1: \n" << m0 - m1;
    cout << "m0 * m1: \n" << m0 * m1;
    cout << "m0 * a: \n" << m0 * a;
}

void testRenderer() {
    Renderer renderer;

    cout << "camera.camDir:   " << renderer.camera.camDir << endl;
    cout << "camera.camUp:    " << renderer.camera.camUp << endl;
    cout << "camera.camRight: " << renderer.camera.camRight << endl;
    cout << "camera.view: " << endl;
    cout << renderer.camera.view();
    cout << "camera.projection: " << endl;
    cout << renderer.camera.projection();

    mat4 model = renderer.donut.rotateZ(0);
    renderer.setModelMat(model);
    renderer.draw();
}

int main() {
    // testMatrix();
    testRenderer();

    system("pause");

    return 0;
}