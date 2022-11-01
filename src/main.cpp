#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include "Matrix.h"
#include "Renderer.h"

using namespace std;

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

//隐藏光标函数
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1,0};//第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

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
    Renderer r;

    cout << "camera.camDir:   " << r.camera.camDir << endl;
    cout << "camera.camUp:    " << r.camera.camUp << endl;
    cout << "camera.camRight: " << r.camera.camRight << endl;
    cout << "camera.view: " << endl;
    cout << r.camera.view();
    cout << "camera.projection: " << endl;
    cout << r.camera.projection();
    

    mat4 model = r.rotateY(120);
    r.setModelMat(model);
    r.draw();
}

int main() {

    Renderer r;

    system("mode con: cols=100 lines=50");
    HideCursor();
    for (;;) {
        for (float i = 0; i < 360; i += 20) {
            system("cls");
            mat4 model = r.rotateZ(i)*r.rotateX(i);
            r.setModelMat(model);
            r.draw();
        }
    }

    return 0;
}