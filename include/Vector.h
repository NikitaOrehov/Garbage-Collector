#pragma once
#include <cstring>
#include <iostream>



template <class T>
class Vector{
    T* _array;
    size_t _real_size;
    size_t _size;

    void expansion(){
        T* tmp = (T*)malloc(sizeof(T) * _size * 2);
        memcpy(tmp, _array, _size * sizeof(T));
        free(_array);
        _array = tmp;
        _size *= 2;
    }
public: 
    Vector(size_t size = 8) : _size(size), _real_size(0){
        _array = (T*)malloc(sizeof(T) * _size);
    }

    size_t size() const{ return _real_size;}

    void push_back(T elem){
        if (_real_size == _size) expansion();
        _array[_real_size++] = elem;
    }

    T& back(){ return _array[_real_size - 1];}

    void pop_back(){
        if (_real_size == 0) return;
        --_real_size;
    }

    bool empty(){ return _real_size == 0;}

    T& operator[](int index) {return _array[index];}

    ~Vector(){ free(_array);}
};