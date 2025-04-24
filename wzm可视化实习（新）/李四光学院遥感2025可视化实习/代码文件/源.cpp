#include <graphics.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <windows.h> // 用于清屏
#include "填充绘制方法.h"
#include "文件读取.h"
#include "自定义符号.h"
#include "界面设计.h"

// 控制台交互界面美化
void getUserInput(int& b, int& f, int& p, int& patternType) {
    system("cls");  // 清屏

    // 界面标题
    std::cout << "================================\n";
    std::cout << "     图形参数设置界面\n";
    std::cout << "================================\n\n";

    // 轮廓颜色选择
    std::cout << "请选择轮廓颜色：\n";
    std::cout << " [-1] 不填充\n [0] 黑色(BLACK)\n [1] 红色(RED)\n [2] 绿色(GREEN)\n [3] 蓝色(BLUE)\n";
    std::cout << "输入选择(-1-3): ";
    std::cin >> b;

    // 符号颜色选择
    std::cout << "\n请选择符号颜色：\n";
    std::cout << " [-1] 不填充\n[0] 浅灰色(LIGHTGRAY)\n [1] 黄色(YELLOW)\n [2] 浅蓝色(LIGHTBLUE)\n";
    std::cout << "输入选择(-1-2): ";
    std::cin >> f;

    // 填充颜色选择
    std::cout << "\n请选择填充颜色：\n";
    std::cout << " [-1] 不填充\n[0] 蓝色(BLUE)\n [1] 洋红色(MAGENTA)\n [2] 青色(CYAN)\n";
    std::cout << "输入选择(-1-2): ";
    std::cin >> p;

    // 图案类型选择
    std::cout << "\n请选择图案类型：\n";
    std::cout << " [-1] 不填充\n [0] 点符号品字形填充\n [1] 点符号矩形填充\n [2] 水平虚线填充\n [3] 数值虚线填充\n ";
    std::cout << "输入选择(-1-3): ";
    std::cin >> patternType;

    // 确认信息
    std::cout << "\n参数设置完成！按任意键开始绘制...\n";
}

int main() {
    // 初始化图形窗口
    initgraph(1200, 900);
    setbkcolor(WHITE);
    cleardevice();
    drawDecorativeBackground();
    drawOrnamentalBorder();
    drawTitle();
    auto shapes = MultiPolygonLoader::loadFromFile("C:\\Users\\86138\\Desktop\\20.txt");

    // 控制颜色选择
    COLORREF borderColor = BLACK;
    COLORREF fillColor = LIGHTGRAY;
    COLORREF patternColor = BLUE;
    int patternType = -1;  // -1 表示无图案，仅扫描线填充

    // 改进的控制台交互
    int b, f, p;
    getUserInput(b, f, p, patternType);

    COLORREF borderColors[] = { BLACK, RED, GREEN, BLUE };
    COLORREF fillColors[] = { LIGHTGRAY, YELLOW, LIGHTBLUE };
    COLORREF patternColors[] = { BLUE, MAGENTA, CYAN };

    borderColor = borderColors[b % 4];
    fillColor = fillColors[f % 3];
    patternColor = patternColors[p % 3];

    for (auto& shape : shapes) {
        shape.draw(borderColor, fillColor, patternColor, patternType);
    }

    _getch();
    closegraph();
    return 0;
}

