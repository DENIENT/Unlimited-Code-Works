#include <cmath>
#include <graphics.h> 


void Line_DDA(int x_start, int y_start, int x_end, int y_end, COLORREF color)
{
    int x, y;                      
    float dx, dy;
    int steps;                      // 总步数（需要绘制的像素点数）
    float xIncrement, yIncrement;    // 每步x和y方向的增量
    float xtmp = 0.0, ytmp = 0.0;   // 浮点临时变量，用于精确计算

    x = x_start;
    y = y_start;

    // 计算x和y方向的总距离
    dx = x_end - x_start;
    dy = y_end - y_start;

    // 确定步数（取x或y方向的最大变化量）
    if (fabs(dx) > fabs(dy)) {
        steps = fabs(dx);  
    }
    else {
        steps = fabs(dy); 
    }
    // 计算每步的增量
    xIncrement = dx / steps; 
    yIncrement = dy / steps; 

    // 绘制起点
    putpixel(x, y, color);

    xtmp = x;
    ytmp = y;

    // 循环绘制每个中间点
    for (int i = 0; i < steps; i++)
    {
        // 计算下一个点的位置（浮点运算保证精度）
        xtmp += xIncrement;
        ytmp += yIncrement;

        x = xtmp;  // 隐式转换为int（相当于取整）
        y = ytmp;

        // 在计算出的位置绘制像素点
        putpixel(x, y, color);
    }
}
