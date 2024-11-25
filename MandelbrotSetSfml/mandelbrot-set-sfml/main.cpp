//
//  main.cpp
//  mandelbrot-set-sfml
//
//  Created by 堀田大智 on 2024/09/08.
//

// マンデルブロ集合 sfmlを使った図示

#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
const int MAX_ITER = 500;

// マンデルブロ集合
int mandelbrot_set(complex<double>c){
    complex<double> z(0.0, 0.0);
    int n = 0;
    while(abs(z) <= 2.0 && n < MAX_ITER){
        z = z * z + c;
        n++;
    }
    return n;
}

// 色を生成する関数
sf::Color getColor(int iter){
    if(iter ==  MAX_ITER){
        return sf::Color::Black; // 集合に含まれる点は黒にする
    }
    else{
        // 発散の速さによって色をかえる
        int r = (iter * 9) % 256;
        int g = (iter * 7) % 256;
        int b = (iter * 5) % 256;
        return sf::Color(r, g, b);
    }
}

int main(){
    // ウィンドウの作成
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelblot Set");

    // ピクセルごとに色を設定するためのテクスチャとスプライト
    sf::Image image;
    image.create(WIDTH, HEIGHT);
    sf::Texture texture;
    sf::Sprite sprite;

    // 描画領域の範囲を設定
//    double minReal = -2.0;
//    double maxReal = 2.0;
//    double minImag = -2.0;
//    double maxImag  = 2.0;
    double nR = 800;
    double nI = 800;
    double maxR = 2.0;
    double minR = -2.0;
    double maxI = 2.0;
    double minI = -2.0;
    double dR = (maxR - minR) / (double)nR;
    double dI = (maxI - minI) / (double)nI;

    // 各ピクセルごとにマンデルブロ集合を計算
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
//            double real = (maxReal - minReal) * x / WIDTH;
//            double imag = (maxImag - minImag) * y / HEIGHT;
            double real = minR + dR * (double)x;
            double imag = minI + dI * (double)y;
            complex<double> c(real, imag);

            int iter = mandelbrot_set(c);
            sf::Color color = getColor(iter);
            image.setPixel(x, y, color);
        }
    }

    // テクスチャとスプライトに設定
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    // ウィンドウが開いている間ループを実行
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

// How to Compile
// g++ ex3.cpp -o ex3 -lsfml-graphics -lsfml-window -lsfml-system
