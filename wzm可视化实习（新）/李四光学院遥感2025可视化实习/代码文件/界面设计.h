#pragma once
#include <graphics.h>
#include <cmath>
#include <vector>
#include <ctime>

void drawOrnamentalBorder() {
    // ��Լ��ɫ���߿�
    COLORREF borderColor = RGB(80, 80, 100); // ���ɫ

    // �����������͵ײ�ϸ��
    setlinecolor(borderColor);
    setlinestyle(PS_SOLID, 2);

    // ������
    line(0, 1, 1200, 1);

    // �ײ���
    line(0, 899, 1200, 899);
}

void drawDecorativeBackground() {
    // ��ɫ���䱳�������ϵ��½��
    for (int y = 0; y < 900; y++) {
        int darkness = 30 + y * 0.08;
        setlinecolor(RGB(darkness, darkness, darkness + 5));
        line(0, y, 1200, y);
    }

    // ��Ӽ����������
    setlinecolor(RGB(50, 50, 60));
    setlinestyle(PS_DOT, 1);

    // ˮƽ������
    for (int y = 100; y < 900; y += 50) {
        line(0, y, 1200, y);
    }

    // ��ֱ������
    for (int x = 100; x < 1200; x += 50) {
        line(x, 0, x, 900);
    }
}

void drawTitle() {
    // �����⣨����ԭλ�ú����ݣ�
    settextcolor(RGB(0, 180, 160)); // ����ɫ
    settextstyle(40, 0, _T("����"));
    outtextxy(420, 50, _T("��ά��ͼ���ӻ�"));

    // �����⣨����ԭλ�ú����ݣ�
    settextcolor(RGB(250, 0, 0)); // ǳ��ɫ
    settextstyle(20, 0, _T("����"));
    outtextxy(450, 100, _T("20231003644  ������"));


    // �����⣨����ԭλ�ú����ݣ�
    settextcolor(RGB(255, 0, 160)); // ����ɫ
    settextstyle(30, 0, _T("����"));
    outtextxy(750, 100, _T("�����ڿ���̨"));
}