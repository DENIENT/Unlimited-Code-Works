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
#include"�Զ������.h"
#include "�����.h"
#include "��ֵ΢���㷨.h"
using namespace std;



// ��ʾһ���Զ���ͼ��
class CustomShape {
private:
    std::vector<Point> outline;      // �洢��״�����Ķ�������
    std::vector<POINT> easyxPoints;  // ת��ΪEasyX�������POINT��ʽ�ĵ㼯

    // ʹ��ɨ�����㷨�����״�ڲ�
    void scanLineFill(COLORREF fillColor) {
        if (outline.empty()) return;  // ��������㼯Ϊ����ֱ�ӷ���

        // 1. �������ε�Y�᷶Χ����С/���Yֵ��
        int minY = outline[0].y, maxY = outline[0].y;
        for (const auto& p : outline) {
            minY = min(minY, p.y);  // ������СYֵ
            maxY = max(maxY, p.y);  // �������Yֵ
        }

        // ���������ɫ
        setfillcolor(fillColor);

        // 2. ���д���ÿ��ɨ���ߣ���minY��maxY��
        for (int y = minY; y <= maxY; ++y) {
            std::vector<int> intersections;  // �洢��ǰɨ������ߵĽ���X����

            // 3. ���㵱ǰɨ���������бߵĽ���
            for (size_t i = 0; i < outline.size(); ++i) {
                size_t j = (i + 1) % outline.size();  // ��ȡ��һ�㣨�պ϶���Σ�
                Point p1 = outline[i], p2 = outline[j];

                // ȷ��p1���Ϸ���yֵ��С��
                if (p1.y > p2.y) std::swap(p1, p2);

                // ��鵱ǰɨ�����Ƿ�����ཻ
                if (y >= p1.y && y < p2.y && p1.y != p2.y) {
                    // ���㽻��X���꣨ʹ��ֱ�߷��̲�ֵ��
                    int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                    intersections.push_back(x);
                }
            }

            // 4. �Խ��㰴X��������
            std::sort(intersections.begin(), intersections.end());

            // 5. �����ڽ����֮���������߶�
            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int x1 = intersections[i];
                int x2 = intersections[i + 1];
                // ����ʵ��ˮƽ�߶Σ������������֮�������
                solidrectangle(x1, y, x2, y);
            }
        }
    }


    bool isCircleInside(int x, int y, int size) {
        double radius = 1.12 * size; // ����Բ�İ뾶

        // ����Բ�ı߽��ĽǶȲ������������Ӳ���������߾��ȣ�
        const int sampleCount = 12; // ����������
        for (int i = 0; i < sampleCount; ++i) {
            double angle = 2 * 3.14159265358979323846 * i / sampleCount; // �Ƕ�
            int sampleX = x + static_cast<int>(radius * cos(angle));    // ����߽��� x ����
            int sampleY = y + static_cast<int>(radius * sin(angle));    // ����߽��� y ����

            // ���߽���Ƿ���ͼ���ڲ�
            if (!isInside(sampleX, sampleY)) {
                return false; // ���������һ���㲻��ͼ���ڲ����򷵻� false
            }
        }

        return true; // ���б߽�㶼��ͼ���ڲ������� true
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
                // ���Բ�Ƿ���ȫ��ͼ���ڲ�
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

        // ��ȡͼ�α߽�
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

            // �����������εĽ���
            for (size_t i = 0; i < outline.size(); ++i) {
                size_t j = (i + 1) % outline.size();
                Point p1 = outline[i], p2 = outline[j];

                if (p1.y > p2.y) swap(p1, p2);

                if (y > p1.y && y <= p2.y && p1.y != p2.y) {
                    // ���㽻��x����
                    int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                    intersections.push_back(x);
                }
            }

            // �Խ�������
            sort(intersections.begin(), intersections.end());

            // ���ƽ���֮�������
            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int x1 = max(intersections[i], minX); // ȷ����㲻С�ڱ߽�
                int x2 = min(intersections[i + 1], maxX); // ȷ���յ㲻���ڱ߽�

                // ���ƶ��߶���ģ������
                for (int x = x1; x < x2; x += dashLength + lineSpacing) {
                    int segmentEnd = min(x + dashLength, x2); // ȷ���߶β������߽�
                    line(x, y, segmentEnd, y);
                }
            }
        }
    }

    // ��ֱ������书��
    void verticalDashedLineFill(COLORREF fillColor, int spacing, int dashLength, int lineSpacing) {
        if (outline.empty()) return;

        // ��ȡͼ�α߽�
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

            // �����������εĽ���
            for (size_t i = 0; i < outline.size(); ++i) {
                size_t j = (i + 1) % outline.size();
                Point p1 = outline[i], p2 = outline[j];

                if (p1.x > p2.x) swap(p1, p2);

                if (x > p1.x && x <= p2.x && p1.x != p2.x) {
                    // ���㽻��y����
                    int y = p1.y + (x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
                    intersections.push_back(y);
                }
            }

            // �Խ�������
            sort(intersections.begin(), intersections.end());

            // ���ƽ���֮�������
            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int y1 = max(intersections[i], minY); // ȷ����㲻С�ڱ߽�
                int y2 = min(intersections[i + 1], maxY); // ȷ���յ㲻���ڱ߽�

                // ���ƶ��߶���ģ������
                for (int y = y1; y < y2; y += dashLength + lineSpacing) {
                    int segmentEnd = min(y + dashLength, y2); // ȷ���߶β������߽�
                    line(x, y, x, segmentEnd);
                }
            }
        }
    }

public:
    // �жϵ��Ƿ���ͼ���ڲ�
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
            std::cerr << "�޷����ļ�: " << filename << std::endl;
            return false;
        }
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss(line);
            int x, y;
            if (!(iss >> x >> y)) {
                std::cerr << "�ļ���ʽ����: " << line << std::endl;
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

