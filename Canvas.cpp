#include <cstdio>
#include "Canvas.h"
#include <cmath>
#include <iostream>
Canvas::Canvas(int width, int height)
{
	h = height;
	w = width;
	this->m = new char* [height];
	for (int i = 0; i < height; i++)
	{
		m[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			m[i][j] = ' ';
		}
	}
}
Canvas::~Canvas()
{
	for (int i = 0; i < h; i++)
	{
		delete[] m[i];
	}
	delete[] m;
}
void Canvas::DrawCircle(int x, int y, int ray, char ch)
{
    for (int i = 0; i < h; i++) 
    {
        for (int j = 0; j < w; j++) 
        {

            int dx = i - x;
            int dy = j - y;
            double distance = sqrt(dx * dx + dy * dy);

            if (abs(distance - ray) < 0.5)
            {
                m[i][j] = ch;
            }
        }
    }
}
void Canvas::FillCircle(int x, int y, int ray, char ch)
{
    for (int i = 0; i < h; i++) 
    {
        for (int j = 0; j < w; j++) 
        {

            int dx = i - x;
            int dy = j - y;
            double distance = sqrt(dx * dx + dy * dy);

            if (distance <= ray)
            {
                m[i][j] = ch;
            }
        }
    }
}
void Canvas::DrawRect(int left, int top, int right, int bottom, char ch)
{
    for (int i = top; i <=bottom; i++)
    {
            m[i][left] = ch;
            m[i][right] = ch;
    }
    for (int j = left; j <= right; j++)
    {
        m[top][j] = ch;
        m[bottom][j] = ch;
    }
}
void Canvas::FillRect(int left, int top, int right, int bottom, char ch)
{
    for (int i = 0; i < h; i++)
    {
        if (i > top && i < bottom)
        {
            for (int j = 0; j < w; j++)
            {
                if (j > left && j < right)
                    m[i][j] = ch;
            }
        }
    }
}
void Canvas::SetPoint(int x, int y, char ch)
{
    m[x][y] = ch;
}
void Canvas::DrawLine(int x1, int y1, int x2, int y2, char ch) {

    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        m[y1][x1] = ch;
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}
void Canvas::Print()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            std::cout << m[i][j] << ' ';
        std::cout << std::endl;
    }
}
void Canvas::Clear()
{
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            m[i][j] = ' ';
}