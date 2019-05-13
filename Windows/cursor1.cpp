// マウスカーソルが円を描く
// g++ -lws2_32 -o cursor1 cursor1.cpp
#include <windows.h>
#include <stdio.h>
#include <math.h>


#include <iostream>

int main() {
	double r = 100;
    double center = 500;
    DWORD wait = 10;

    // 現在のマウスカーソル位置を取得
    {
        POINT po;
        GetCursorPos(&po);
        std::cout << po.x << "," << po.y << std::endl;
    }

    // 現在の位置で左クリック -> VisualStudio でビルドしないと動かなかった
    // {
    //     INPUT input = { INPUT_MOUSE, 0, 0, MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP };
    //     SendInput(1, &input, sizeof(INPUT));
    // }
    
    for (double x = 0.0; x < 10.0; x += 0.05) {
        SetCursorPos( (int)(r * cos(x) + center), 
                      (int)(r * sin(x) + center) );
        Sleep(wait);
    }
	
    return 0;
}
