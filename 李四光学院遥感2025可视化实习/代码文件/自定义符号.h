#pragma once
#include <graphics.h>
#include <vector>

void drawHexagram(int x, int y, int size = 10, COLORREF color = BLACK) {
    setlinecolor(color);

    // 定义六棱星的六个顶点
    POINT p1 = { x, y - size };                  // 上顶点
    POINT p2 = { x + size, y - size / 2 };       // 右上顶点
    POINT p3 = { x + size, y + size / 2 };       // 右下顶点
    POINT p4 = { x, y + size };                  // 下顶点
    POINT p5 = { x - size, y + size / 2 };       // 左下顶点
    POINT p6 = { x - size, y - size / 2 };       // 左上顶点

    // 绘制六棱星的外部三角形
    line(p1.x, p1.y, p3.x, p3.y);  // 上 → 右下
    line(p3.x, p3.y, p5.x, p5.y);  // 右下 → 左下
    line(p5.x, p5.y, p1.x, p1.y);  // 左下 → 上

    // 绘制六棱星的内部三角形
    line(p2.x, p2.y, p4.x, p4.y);  // 右上 → 下
    line(p4.x, p4.y, p6.x, p6.y);  // 下 → 左上
    line(p6.x, p6.y, p2.x, p2.y);  // 左上 → 右上
}
