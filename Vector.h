#pragma once
#include <cstring>


template <class T>
class Vector{
    T* _array;
    size_t _size;
    size_t _max_size;

    void expansion(){
        _max_size *= 2;
        T* p = (T*)malloc(sizeof(T) * _max_size);
        std::memcpy(p, _array, _size * sizeof(T));
        _array = p;
        free(p);
    }
public:
    Vector(size_t max_size = 2) : _max_size(max_size){
        std::cout<<"constructor Vector\n";
        _array = (T*)malloc(sizeof(T) * _max_size);
        _size = 0;
    }

    size_t size() const {
        return _size;
    }

    void push_back(T object){
        if (_size == _max_size){
            expansion();
        }
        _array[_size] = object;
        _size++;
    }

    void DeleteElem(int index){
        for (int i = index - 1; i < _size - 1; i++){
            _array[i] = _array[i + 1];
        }
        _size--;
    }

    T operator[](int index) {
        return _array[index];
    }

    ~Vector(){
        std::cout<<"destructor Vector\n";
        free(_array);
        std::cout<<"end destructor Vector\n";
    }

};//как пометить элементы при удалении и удалить их только во время расширения?