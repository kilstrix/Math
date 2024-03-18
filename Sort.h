#pragma once
#include <vector>
#include <initializer_list>
class Sort
{
	private:
    int* elements;
    int size;
public:
    Sort(int number_of_elements, int min, int max);
    Sort(int* ext_vector, int number_of_elements);
    Sort(int count, ...);
    Sort(char* ext_vector2);
    Sort(std::initializer_list<int> init);
    ~Sort();
    void InsertSort(bool ascendent = false);
    void QuickSort(bool ascendent = false);
    void quickSort1(int st, int dr);
    void quickSort2(int st, int dr);
    void BubbleSort(bool ascendent = false);
    void Print();
    int  GetElementsCount();
    int  GetElementFromIndex(int index);
};

