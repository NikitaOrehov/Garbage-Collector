#pragma once
#include <cstring>

struct Object
{
    void* Referense;
    bool IsAlive = 0;
};

template <class T>
class Vector{
    T* _array;
    size_t _real_size;
    size_t _size;
    size_t _max_size;

    void expansion(){
        _max_size *= 2;
        T* p = (T*)malloc(sizeof(T) * _max_size);
        std::memcpy(p, _array, _size * sizeof(T));
        free(_array);
        _array = p;
    }
public:
    Vector(size_t max_size = 2) : _max_size(max_size){
        std::cout<<"constructor Vector\n";
        _array = (T*)malloc(sizeof(T) * _max_size);
        _size = 0;
        _real_size = 0;
    }

    size_t size() const {
        return _size;
    }

    void push_back(T object){
        if (_size == _max_size){
            expansion();
        }
        _array[_size] = object;
        _real_size++;
        _size++;
    }

    void DeleteElem(int index){
        Object o;
        o.Referense = nullptr;
        o.IsAlive = 0;
        _array[index] = o;
        _real_size--;
    }

    void DeleteGarbage(){
        T* p = (T*)malloc(sizeof(T) * _real_size * 2);
        int count = 0;
        for (int i = 0; i < _size; i++){
            if (_array[i].Referense != nullptr){// && _array[i].IsAlive == 1
                p[count] = _array[i];
                count++;
            }
        }
        _max_size = _real_size * 2;
        _real_size = count;
        _size = count;
        free(_array);
        _array = p;
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