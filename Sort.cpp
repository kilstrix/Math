#define _CRT_SECURE_NO_WARNINGS
#include "Sort.h"
#include <initializer_list>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdarg>
#include <vector>
#include <cstring>
Sort::Sort(int number_of_elements, int min, int max) 
{
    size = number_of_elements;
    elements = new int[size];
    for (int i = 0; i < size; i++) {
        elements[i] = rand() % (max - min + 1) + min;
    }
}

Sort::Sort(int* ext_vector, int number_of_elements) 
{
    size = number_of_elements;
    elements = new int[size];
    for (int i = 0; i < size; i++) {
        elements[i] = ext_vector[i];
    }
}

Sort::Sort(int count, ...) 
{
    size = count;
    elements = new int[size];
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        elements[i] = va_arg(args, int);
    }
    va_end(args);
}

Sort::Sort(char* c) 
{
    elements = new int[strlen(c)];
    int nr_curent = 0;
    char* p = strtok(c, ",");
    int idx = 0;
    while (p) 
    {
        nr_curent = 0;
        for (int i = 0; i < strlen(p); i++)
            nr_curent = nr_curent * 10 + p[i] - '0';
        elements[idx] = nr_curent;
        idx++;
        p = strtok(NULL, ",");
    }
    size = idx;
}

Sort::Sort(std::initializer_list<int> init) 
{
    size = init.size();
    elements = new int[size];
    int i = 0;
    for (auto it = init.begin(); it != init.end(); ++it)
        elements[i++] = *it;
}

Sort::~Sort() 
{
    delete[] elements;
}

void Sort::Print() 
{   
    for (int i = 0; i < size; i++)
        std::cout << elements[i] << " ";
    std::cout << std::endl;
}

int Sort::GetElementFromIndex(int index)
{
    return elements[index];
}

int Sort::GetElementsCount()
{
    return size;
}

void Sort::QuickSort(bool ascendent)
{
    if (ascendent)
        quickSort1(0, size - 1);
    else
        quickSort2(0, size - 1);
}

void Sort::quickSort1(int st, int dr)
{
    if (st < dr)
    {
        int m = (st + dr) / 2;
        int aux = elements[st];
        elements[st] = elements[m];
        elements[m] = aux;
        int i = st, j = dr, d = 0;
        while (i < j)
        {
            if (elements[i] > elements[j])
            {
                aux = elements[i];
                elements[i] = elements[j];
                elements[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        quickSort1(st, i - 1);
        quickSort1(i + 1, dr);
    }
}

void Sort::quickSort2(int st, int dr)
{
    if (st < dr)
    {
        int m = (st + dr) / 2;
        int aux = elements[st];
        elements[st] = elements[m];
        elements[m] = aux;
        int i = st, j = dr, d = 0;
        while (i < j)
        {
            if (elements[i] < elements[j])
            {
                aux = elements[i];
                elements[i] = elements[j];
                elements[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        quickSort2(st, i - 1);
        quickSort2(i + 1, dr);
    }
}

void Sort::InsertSort(bool ascendant)
{
    if (ascendant == true)
        for (int i = 1; i < size; i++)
        {
            int x = elements[i];
            int p = i - 1;
            while (p >= 0 && elements[p] > x)
                elements[p + 1] = elements[p], p--;
            elements[p + 1] = x;
        }
    else
    {
        for (int i = 1; i < size; i++) {
            int key = elements[i];
            int j = i - 1;
            while (j >= 0 && elements[j] < key) {
                elements[j + 1] = elements[j];
                j--;
            }
            elements[j + 1] = key;
        }
    }
}

void Sort::BubbleSort(bool ascendent)
{
    if (ascendent == true)
    {
        bool sortat;
        int m = size;
        do
        {
            sortat = true;
            int p = m;
            for (int i = 0; i < p - 1; i++)
                if (elements[i] > elements[i + 1])
                {
                    int aux = elements[i];
                    elements[i] = elements[i + 1];
                    elements[i + 1] = aux;
                    sortat = false;
                    m = i + 1;
                }
        } while (!sortat);
    }
    else
    {
        bool sortat;
        int m = size;
        do
        {
            sortat = true;
            int p = m;
            for (int i = 0; i < p - 1; i++)
                if (elements[i] < elements[i + 1])
                {
                    int aux = elements[i];
                    elements[i] = elements[i + 1];
                    elements[i + 1] = aux;
                    sortat = false;
                    m = i + 1;
                }
        } while (!sortat);
    }
}

