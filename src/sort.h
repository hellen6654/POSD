#include <random>
#include <iostream>
#include "shape.h"

template <class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator first, 
                RandomAccessIterator last, 
                Compare comp)
{

    int size = (last - first);
    int end = size-1;
    if (first < last-1)
    {
        int pivot = Partition(first,0,end,comp);
        quickSort(first, first + pivot, comp);
        quickSort(first + pivot + 1, last, comp);
    }
}

template <class RandomAccessIterator, class Compare>
int Partition(RandomAccessIterator arr,int start,int end,Compare comp)
{
    RandomAccessIterator pivot = arr+end;
    int i = start -1;
    for (int j = 0; j < end; j++)
    {
        if (comp(*(arr+j),*pivot))
        {
            i++;
            swap(arr+i,arr+j);
        }
        
    }
    i++;
    swap(arr+i,arr+end);
    return i;
}

template <class RandomAccessIterator>
void swap(RandomAccessIterator a, RandomAccessIterator b)
{
    auto temp= *a;
    *a = *b;
    *b = temp;
}

bool areaAscendingCompare(Shape *a, Shape *b)
{
    return a->area() < b->area();
};

bool areaDescendingCompare(Shape *a, Shape *b)
{
    return a->area() > b->area();
};

bool perimeterAscendingCompare(Shape *a, Shape *b)
{
    return a->perimeter() < b->perimeter();
};

bool perimeterDescendingCompare(Shape *a, Shape *b)
{
    return a->perimeter() > b->perimeter();
};

class AscendingCompare
{
public:
    AscendingCompare(std::string feature) : _feature(feature) {}
    bool operator()(Shape *a, Shape *b)
    {
        if (_feature == "Area")
            return a->area() < b->area();
        else
            return a->perimeter() < b->perimeter();
    }

private:
    std::string _feature;
};

class DescendingCompare
{
public:
    DescendingCompare(std::string feature) : _feature(feature) {}
    bool operator()(Shape *a, Shape *b)
    {
        if (_feature == "Area")
            return a->area() > b->area();
        else
            return a->perimeter() > b->perimeter();
    }

private:
    std::string _feature;
};
