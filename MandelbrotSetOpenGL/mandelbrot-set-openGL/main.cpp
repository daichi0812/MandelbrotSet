//
//  main.cpp
//  mandelbrot-set-openGL
//
//  Created by 堀田大智 on 2024/09/08.
//

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <complex>
#include <iostream>
using namespace std;

// 画面サイズ
const int WIDTH = 800;
const int HEIGHT = 800;
const int MAX_ITER = 1000;
// マンデルブロ集合の計算
int mandelbrot(complex<double>c){
    complex<double> z = 0.0;
    int n  = 0;;
    
    while(abs(z) < 2.0 && n < MAX_ITER){
        z = z * z + c;
        n++;
    }
    
    return n;
}

// 色を設定する関数
void setColor(int iter){
    if(iter == MAX_ITER){
        glColor3f(0, 0, 0); //発散しない場合は黒
    } else{
        float t = (float)iter / MAX_ITER;
        glColor3f(9 * (1 - t) * t * t * t, 30 * (1 - t) * (1 - t) * t * t, 15 * (1 - t) * (1 - t) * (1 - t) * t);
    }
}

// マンデルブロ集合を描画する関数
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POINTS);
    for(int px = 0; px < WIDTH; px++){
        for(int py = 0; py < HEIGHT; py++){
            //座標をマンデルブロ平面に変換
            double x = (px - WIDTH / 2.0) * 4.0 / WIDTH;
            double y = (py - HEIGHT / 2.0) * 4.0 / HEIGHT;
            
            complex<double> c(x, y);
            int iter  = mandelbrot(c);
            setColor(iter);
            glVertex2f(px, py);
        }
    }
    glEnd();
    glFlush();
}

// ウィンドウを初期化する関数
void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0); // 背景を白に設定
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Mandelbrot Set");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
