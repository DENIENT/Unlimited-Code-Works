#pragma once
#pragma once
#include <vector>
#include <fstream>
#include "�����Ʒ���.h"
//X,Y֮���ÿո�ָ�
class MultiPolygonLoader {
public:
    static std::vector<CustomShape> loadFromFile(const std::string& filename) {
        std::vector<CustomShape> shapes;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return shapes;
        }

        int polygonCount;//��ȡ�ļ��и����Ķ��������
        file >> polygonCount;

        for (int i = 0; i < polygonCount; ++i) {
            int vertexCount;//��ȡ��ǰ����εĶ�������
            file >> vertexCount;

            CustomShape shape;
            for (int j = 0; j < vertexCount; ++j) {
                double x, y;
                file >> x >> y;
                x *= 1000.0;  //��������
                y *= 1000.0;
                x += 100;
                y += 200;
                shape.addPoint(x, y);
            }
            shapes.push_back(shape);
        }

        file.close();
        return shapes;
    }
}; 
