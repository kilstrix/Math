#include "Canvas.h"
#include <iostream>

int main()
{
    Canvas canvas(30, 20);

    canvas.DrawLine(0, 0, 10, 10, '*');
    canvas.Print();
    canvas.Clear();
    canvas.SetPoint(18, 8, '+');
    canvas.Print();
    canvas.Clear();
    canvas.DrawRect(1,2,4,6,'+');
    canvas.FillRect(1, 2, 4, 6, '!');
    canvas.Print();
    canvas.Clear();
    canvas.DrawCircle(6, 6, 3, '+');
    canvas.FillCircle(6, 6, 3, '!');
    canvas.Print();

    return 0;
}