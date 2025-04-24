#pragma once
#include <graphics.h>
#include <vector>

void drawHexagram(int x, int y, int size = 10, COLORREF color = BLACK) {
    setlinecolor(color);

    // ���������ǵ���������
    POINT p1 = { x, y - size };                  // �϶���
    POINT p2 = { x + size, y - size / 2 };       // ���϶���
    POINT p3 = { x + size, y + size / 2 };       // ���¶���
    POINT p4 = { x, y + size };                  // �¶���
    POINT p5 = { x - size, y + size / 2 };       // ���¶���
    POINT p6 = { x - size, y - size / 2 };       // ���϶���

    // ���������ǵ��ⲿ������
    line(p1.x, p1.y, p3.x, p3.y);  // �� �� ����
    line(p3.x, p3.y, p5.x, p5.y);  // ���� �� ����
    line(p5.x, p5.y, p1.x, p1.y);  // ���� �� ��

    // ���������ǵ��ڲ�������
    line(p2.x, p2.y, p4.x, p4.y);  // ���� �� ��
    line(p4.x, p4.y, p6.x, p6.y);  // �� �� ����
    line(p6.x, p6.y, p2.x, p2.y);  // ���� �� ����
}
