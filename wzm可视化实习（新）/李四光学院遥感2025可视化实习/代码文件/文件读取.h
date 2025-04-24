#pragma once
#pragma once
#include <vector>
#include <fstream>
#include "填充绘制方法.h"
//X,Y之间拿空格分隔
class MultiPolygonLoader {
public:
    static std::vector<CustomShape> loadFromFile(const std::string& filename) {
        std::vector<CustomShape> shapes;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return shapes;
        }

        int polygonCount;//读取文件中给出的多边形数量
        file >> polygonCount;

        for (int i = 0; i < polygonCount; ++i) {
            int vertexCount;//读取当前多边形的顶点数量
            file >> vertexCount;

            CustomShape shape;
            for (int j = 0; j < vertexCount; ++j) {
                double x, y;
                file >> x >> y;
                x *= 1000.0;  //坐标缩放
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
