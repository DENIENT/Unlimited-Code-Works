#include <graphics.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <windows.h> // ��������
#include "�����Ʒ���.h"
#include "�ļ���ȡ.h"
#include "�Զ������.h"
#include "�������.h"

// ����̨������������
void getUserInput(int& b, int& f, int& p, int& patternType) {
    system("cls");  // ����

    // �������
    std::cout << "================================\n";
    std::cout << "     ͼ�β������ý���\n";
    std::cout << "================================\n\n";

    // ������ɫѡ��
    std::cout << "��ѡ��������ɫ��\n";
    std::cout << " [-1] �����\n [0] ��ɫ(BLACK)\n [1] ��ɫ(RED)\n [2] ��ɫ(GREEN)\n [3] ��ɫ(BLUE)\n";
    std::cout << "����ѡ��(-1-3): ";
    std::cin >> b;

    // ������ɫѡ��
    std::cout << "\n��ѡ�������ɫ��\n";
    std::cout << " [-1] �����\n[0] ǳ��ɫ(LIGHTGRAY)\n [1] ��ɫ(YELLOW)\n [2] ǳ��ɫ(LIGHTBLUE)\n";
    std::cout << "����ѡ��(-1-2): ";
    std::cin >> f;

    // �����ɫѡ��
    std::cout << "\n��ѡ�������ɫ��\n";
    std::cout << " [-1] �����\n[0] ��ɫ(BLUE)\n [1] ���ɫ(MAGENTA)\n [2] ��ɫ(CYAN)\n";
    std::cout << "����ѡ��(-1-2): ";
    std::cin >> p;

    // ͼ������ѡ��
    std::cout << "\n��ѡ��ͼ�����ͣ�\n";
    std::cout << " [-1] �����\n [0] �����Ʒ�������\n [1] ����ž������\n [2] ˮƽ�������\n [3] ��ֵ�������\n ";
    std::cout << "����ѡ��(-1-3): ";
    std::cin >> patternType;

    // ȷ����Ϣ
    std::cout << "\n����������ɣ����������ʼ����...\n";
}

int main() {
    // ��ʼ��ͼ�δ���
    initgraph(1200, 900);
    setbkcolor(WHITE);
    cleardevice();
    drawDecorativeBackground();
    drawOrnamentalBorder();
    drawTitle();
    auto shapes = MultiPolygonLoader::loadFromFile("C:\\Users\\86138\\Desktop\\20.txt");

    // ������ɫѡ��
    COLORREF borderColor = BLACK;
    COLORREF fillColor = LIGHTGRAY;
    COLORREF patternColor = BLUE;
    int patternType = -1;  // -1 ��ʾ��ͼ������ɨ�������

    // �Ľ��Ŀ���̨����
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

