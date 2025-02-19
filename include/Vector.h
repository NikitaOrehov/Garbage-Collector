#pragma once
#include <cstring>
#include <iostream>

struct Object
{
    void* Referense;
    size_t size = 0;
    bool IsAlive = 0;
};

class Vector{
    Object** _array;
    size_t _real_size;
    size_t _size;
    size_t _max_size;

    void expansion();
public: 
    Vector(size_t max_size = 2);
    size_t size() const ;
    void push_back(Object object);
    void DeleteElem(int index);
    void DeleteElem(void* ref);
    bool FindReferense(void* ref);
    Object* FindObject(void* ref);
    Object* operator[](int index);
    void PrintObject();
    ~Vector();

};//как пометить элементы при удалении и удалить их только во время расширения?