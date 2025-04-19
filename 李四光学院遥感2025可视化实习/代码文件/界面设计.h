#pragma once
#include <graphics.h>
#include <cmath>
#include <vector>
#include <ctime>

void drawOrnamentalBorder() {
    // 简约暗色调边框
    COLORREF borderColor = RGB(80, 80, 100); // 深灰色

    // 仅保留顶部和底部细线
    setlinecolor(borderColor);
    setlinestyle(PS_SOLID, 2);

    // 顶部线
    line(0, 1, 1200, 1);

    // 底部线
    line(0, 899, 1200, 899);
}

void drawDecorativeBackground() {
    // 暗色渐变背景（从上到下渐深）
    for (int y = 0; y < 900; y++) {
        int darkness = 30 + y * 0.08;
        setlinecolor(RGB(darkness, darkness, darkness + 5));
        line(0, y, 1200, y);
    }

    // 添加极简的网格线
    setlinecolor(RGB(50, 50, 60));
    setlinestyle(PS_DOT, 1);

    // 水平网格线
    for (int y = 100; y < 900; y += 50) {
        line(0, y, 1200, y);
    }

    // 垂直网格线
    for (int x = 100; x < 1200; x += 50) {
        line(x, 0, x, 900);
    }
}

void drawTitle() {
    // 主标题（保持原位置和内容）
    settextcolor(RGB(0, 180, 160)); // 青绿色
    settextstyle(40, 0, _T("楷体"));
    outtextxy(420, 50, _T("二维地图可视化"));

    // 副标题（保持原位置和内容）
    settextcolor(RGB(250, 0, 0)); // 浅灰色
    settextstyle(20, 0, _T("宋体"));
    outtextxy(450, 100, _T("20231003644  王子明"));


    // 主标题（保持原位置和内容）
    settextcolor(RGB(255, 0, 160)); // 青绿色
    settextstyle(30, 0, _T("楷体"));
    outtextxy(750, 100, _T("操作在控制台"));
}