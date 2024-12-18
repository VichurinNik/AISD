#include"Image.h"
#include<Windows.h>

//�������� ����������
template <typename T>
void drawFilledCircle(int cx, int cy, int radius, T fillValue, Image<short>& img)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y)
    {
        // ������ �������������� ����� ��� ���������� ���������� ����� �����
        drawHorizontalLine(cx - x, cy - y, 2 * x + 1, fillValue,img);
        drawHorizontalLine(cx - x, cy + y, 2 * x + 1, fillValue,img);
        drawHorizontalLine(cx - y, cy - x, 2 * y + 1, fillValue,img);
        drawHorizontalLine(cx - y, cy + x, 2 * y + 1, fillValue,img);

        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// ������� ��� ��������� �������������� �����
template <typename T>
void drawHorizontalLine(int x1, int y, int length, T value, Image<short>& img)
{
    for (int x = x1; x < x1 + length; ++x) {
        /*setPixel(x, y, value);*/
        img(y, x) = value;
    }
}


//�����



int main() {
    // ������ ������������� � ����� char
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //���������� ������������ ���������� �����������
    //������ ������ operator!
    /*Image<short> img3(5, 5, true);
    cout << img3 << endl;
    cout << img3.getFillRatio() << endl;
    cout << !img3 << endl;*/

   // ��������� ������ ������� �������
   /* Image<short> img1(2, 2, true);
    Image<short> img2(3, 3, true);
    cout << img1 << endl;
    cout << img2 << endl;
    Image<short> img3= img1*img2;
     cout << img3.getFillRatio() << endl;
    cout << img3 << endl;*/
    
    // �������� ������ ������� �������
  /* Image<short> img1(2, 2, true);
   Image<short> img2(3, 3, true);
   cout << img1 << endl;
   cout << img2 << endl;
   Image<short> img3= img1+img2;
    cout << img3.getFillRatio() << endl;
   cout << img3 << endl;*/

    //����� �����
    Image<int> img2(100, 100, false);
    drawFilledCircle(50, 50, 30, 5, img2);
    img2.PixelImage(img2);

    return 0;
};