#pragma once
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"自定义符号.h"
#include "定义点.h"
#include "数值微分算法.h"
using namespace std;



// 表示一个自定义图形
class CustomShape {
private:
    std::vector<Point> outline;      // 存储形状轮廓的顶点坐标
    std::vector<POINT> easyxPoints;  // 转换为EasyX库所需的POINT格式的点集

    // 使用扫描线算法填充形状内部
    void scanLineFill(COLORREF fillColor) {
        if (outline.empty()) return;  // 如果轮廓点集为空则直接返回

        // 1. 计算多边形的Y轴范围（最小/最大Y值）
        int minY = outline[0].y, maxY = outline[0].y;
        for (const auto& p : outline) {
            minY = min(minY, p.y);  // 更新最小Y值
            maxY = max(maxY, p.y);  // 更新最大Y值
        }

        // 设置填充颜色
        setfillcolor(fillColor);

        // 2. 逐行处理每条扫描线（从minY到maxY）
        for (int y = minY; y <= maxY; ++y) {
            std::vector<int> intersections;  // 存储当前扫描线与边的交点X坐标

            // 3. 计算当前扫描线与所有边的交点
            for (size_t i = 0; i < outline.size(); ++i) {
                size_t j = (i + 1) % outline.size();  // 获取下一点（闭合多边形）
                Point p1 = outline[i], p2 = outline[j];

                // 确保p1在上方（y值较小）
                if (p1.y > p2.y) std::swap(p1, p2);

                // 检查当前扫描线是否与边相交
                if (y >= p1.y && y < p2.y && p1.y != p2.y) {
                    // 计算交点X坐标（使用直线方程插值）
                    int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                    intersections.push_back(x);
                }
            }

            // 4. 对交点按X坐标排序
            std::sort(intersections.begin(), intersections.end());

            // 5. 在相邻交点对之间绘制填充线段
            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int x1 = intersections[i];
                int x2 = intersections[i + 1];
                // 绘制实心水平线段（填充两个交点之间的区域）
                solidrectangle(x1, y, x2, y);
            }
        }
    }


    bool isCircleInside(int x, int y, int size) {
        double radius = 1.12 * size; // 计算圆的半径

        // 定义圆的边界点的角度采样（可以增加采样点以提高精度）
        const int sampleCount = 12; // 采样点数量
        for (int i = 0; i < sampleCount; ++i) {
            double angle = 2 * 3.14159265358979323846 * i / sampleCount; // 角度
            int sampleX = x + static_cast<int>(radius * cos(angle));    // 计算边界点的 x 坐标
            int sampleY = y + static_cast<int>(radius * sin(angle));    // 计算边界点的 y 坐标

            // 检查边界点是否在图形内部
            if (!isInside(sampleX, sampleY)) {
                return false; // 如果有任意一个点不在图形内部，则返回 false
            }
        }

        return true; // 所有边界点都在图形内部，返回 true
    }

    void staggeredFill(COLORREF fillColor, int size = 15) {
        if (outline.empty()) return;

        int minX = outline[0].x, maxX = outline[0].x;
        int minY = outline[0].y, maxY = outline[0].y;
        for (const auto& p : outline) {
            minX = min(minX, p.x);
            maxX = max(maxX, p.x);
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }

        setlinecolor(fillColor);
        setfillcolor(fillColor);

        int stepX = size * 2;
        int stepY = size * 2;
        bool stagger = false;

        for (int y = minY; y <= maxY; y += stepY) {
            stagger = !stagger;
            for (int x = minX + (stagger ? stepX / 2 : 0); x <= maxX; x += stepX) {
                // 检查圆是否完全在图形内部
                if (isCircleInside(x, y, size)) {
                    drawHexagram(x, y, size, fillColor);
                }
            }
        }
    }

    void rectangleFill(COLORREF fillColor, int size = 15) {
        if (outline.empty()) return;

        int minX = outline[0].x, maxX = outline[0].x;
        int minY = outline[0].y, maxY = outline[0].y;
        for (const auto& p : outline) {
            minX = min(minX, p.x);
            maxX = max(maxX, p.x);
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }

        setlinecolor(fillColor);
        setfillcolor(fillColor);

        int step = size * 2;

        for (int y = minY; y <= maxY; y += step) {
            for (int x = minX; x <= maxX; x += step) {
                if (isCircleInside(x, y, size)) {
                    drawHexagram(x, y, size, fillColor);
                }
            }
        }
    }

   
    void horizontalDashedLineFill(COLORREF fillColor, int spacing, int dashLength, int lineSpacing) {
        if (outline.empty()) return;

        // 获取图形边界
        int minX = outline[0].x, maxX = outline[0].x;
        int minY = outline[0].y, maxY = outline[0].y;
        for (const auto& p : outline) {
            minX = min(minX, p.x);
            maxX = max(maxX, p.x);
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }

        setlinecolor(fillColor);

        for (int y = minY; y <= maxY; y += spacing) {
            std::vector<int> intersections;

            // 计算线与多边形的交点
            for (size_t i = 0; i < outline.size(); ++i) {
                size_t j = (i + 1) % outline.size();
                Point p1 = outline[i], p2 = outline[j];

                if (p1.y > p2.y) swap(p1, p2);

                if (y > p1.y && y <= p2.y && p1.y != p2.y) {
                    // 计算交点x坐标
                    int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                    intersections.push_back(x);
                }
            }

            // 对交点排序
            sort(intersections.begin(), intersections.end());

            // 绘制交点之间的虚线
            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int x1 = max(intersections[i], minX); // 确保起点不小于边界
                int x2 = min(intersections[i + 1], maxX); // 确保终点不大于边界

                // 绘制短线段来模拟虚线
                for (int x = x1; x < x2; x += dashLength + lineSpacing) {
                    int segmentEnd = min(x + dashLength, x2); // 确保线段不超出边界
                    line(x, y, segmentEnd, y);
                }
            }
        }
    }

    // 竖直虚线填充功能
    void verticalDashedLineFill(COLORREF fillColor, int spacing, int dashLength, int lineSpacing) {
        if (outline.empty()) return;

        // 获取图形边界
        int minX = outline[0].x, maxX = outline[0].x;
        int minY = outline[0].y, maxY = outline[0].y;
        for (const auto& p : outline) {
            minX = min(minX, p.x);
            maxX = max(maxX, p.x);
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }

        setlinecolor(fillColor);

        for (int x = minX; x <= maxX; x += spacing) {
            std::vector<int> intersections;

            // 计算线与多边形的交点
            for (size_t i = 0; i < outline.size(); ++i) {
                size_t j = (i + 1) % outline.size();
                Point p1 = outline[i], p2 = outline[j];

                if (p1.x > p2.x) swap(p1, p2);

                if (x > p1.x && x <= p2.x && p1.x != p2.x) {
                    // 计算交点y坐标
                    int y = p1.y + (x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
                    intersections.push_back(y);
                }
            }

            // 对交点排序
            sort(intersections.begin(), intersections.end());

            // 绘制交点之间的虚线
            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int y1 = max(intersections[i], minY); // 确保起点不小于边界
                int y2 = min(intersections[i + 1], maxY); // 确保终点不大于边界

                // 绘制短线段来模拟虚线
                for (int y = y1; y < y2; y += dashLength + lineSpacing) {
                    int segmentEnd = min(y + dashLength, y2); // 确保线段不超出边界
                    line(x, y, x, segmentEnd);
                }
            }
        }
    }

public:
    // 判断点是否在图形内部
    bool isInside(int x, int y) const {
        if (outline.size() < 3) return false;
        int count = 0;
        for (size_t i = 0; i < outline.size(); ++i) {
            size_t j = (i + 1) % outline.size();
            const Point& p1 = outline[i];
            const Point& p2 = outline[j];
            if ((p1.y > y) != (p2.y > y)) {
                int intersectX = (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
                if (p1.y == p2.y && p1.y == y) {
                    if (x >= min(p1.x, p2.x) && x <= max(p1.x, p2.x)) return true;
                }
                if (x <= intersectX) count++;
            }
        }
        return count % 2 == 1;
    }

    void addPoint(double x, double y) {
        outline.emplace_back(static_cast<int>(x), static_cast<int>(y));
        easyxPoints.push_back({ static_cast<int>(x), static_cast<int>(y) });
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filename << std::endl;
            return false;
        }
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss(line);
            int x, y;
            if (!(iss >> x >> y)) {
                std::cerr << "文件格式错误: " << line << std::endl;
                return false;
            }
            addPoint(x, y);
        }
        file.close();
        return true;
    }

    void draw(COLORREF borderColor, COLORREF fillColor,COLORREF patterncolor, int fillType = 0) {
        if (outline.size() < 2) return;
        scanLineFill(patterncolor);


        setlinecolor(borderColor);
        for (size_t i = 0; i < outline.size(); ++i) {
            const auto& p1 = outline[i];
            const auto& p2 = outline[(i + 1) % outline.size()];
            Line_DDA(p1.x, p1.y, p2.x, p2.y, borderColor);
        }
        switch (fillType) {       
        case 0: staggeredFill(fillColor); break;
        case 1: rectangleFill(fillColor); break;       
        case 2: horizontalDashedLineFill(fillColor, 10, 8, 5); break;      
        case 3: verticalDashedLineFill(fillColor, 10, 8, 5); break;       
        }
    }
};

