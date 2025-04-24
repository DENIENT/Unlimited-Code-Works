#include <cmath>
#include <graphics.h> 


void Line_DDA(int x_start, int y_start, int x_end, int y_end, COLORREF color)
{
    int x, y;                      
    float dx, dy;
    int steps;                      // �ܲ�������Ҫ���Ƶ����ص�����
    float xIncrement, yIncrement;    // ÿ��x��y���������
    float xtmp = 0.0, ytmp = 0.0;   // ������ʱ���������ھ�ȷ����

    x = x_start;
    y = y_start;

    // ����x��y������ܾ���
    dx = x_end - x_start;
    dy = y_end - y_start;

    // ȷ��������ȡx��y��������仯����
    if (fabs(dx) > fabs(dy)) {
        steps = fabs(dx);  
    }
    else {
        steps = fabs(dy); 
    }
    // ����ÿ��������
    xIncrement = dx / steps; 
    yIncrement = dy / steps; 

    // �������
    putpixel(x, y, color);

    xtmp = x;
    ytmp = y;

    // ѭ������ÿ���м��
    for (int i = 0; i < steps; i++)
    {
        // ������һ�����λ�ã��������㱣֤���ȣ�
        xtmp += xIncrement;
        ytmp += yIncrement;

        x = xtmp;  // ��ʽת��Ϊint���൱��ȡ����
        y = ytmp;

        // �ڼ������λ�û������ص�
        putpixel(x, y, color);
    }
}
