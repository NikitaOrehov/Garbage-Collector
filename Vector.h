#pragma once
#include <cstring>
#include <iostream>

struct Object
{
    void* Referense;
    size_t size;
    bool IsAlive = 0;
};





class Vector{
    Object** _array;
    size_t _real_size;
    size_t _size;
    size_t _max_size;

    void expansion(){
        _max_size *= 2;
        Object** p = (Object**)malloc(sizeof(Object*) * _max_size);
        for (int i = 0; i < _max_size; i++){
            p[i] = (Object*)malloc(sizeof(Object*));
        }
        std::memcpy(p, _array, _size * sizeof(Object*));
        free(_array);
        _array = p;
    }
public:
    Vector(size_t max_size = 2) : _max_size(max_size){
        std::cout<<"constructor Vector\n";
        _size = 0;
        _real_size = 0;
        _array = (Object**)malloc(sizeof(Object*) * _max_size);
        for (int i = 0; i < _max_size; i++){
            _array[i] = (Object*)malloc(sizeof(Object));
        }
    }

    size_t size() const {
        return _real_size;
    }

    void push_back(Object object){
        if (_size == _max_size){
            expansion();
        }
        _array[_size]->IsAlive = object.IsAlive;
        _array[_size]->Referense = object.Referense;
        _array[_size]->size = object.size;
        _real_size++;
        _size++;
    }

    void DeleteElem(int index){
        free(_array[index]->Referense);
        free(_array[index]);
        Object* o = (Object*)malloc(sizeof(Object*));
        o->Referense = nullptr;
        o->IsAlive = 0;
        o->size = 0;
        _array[index] = o;
        _real_size--;
    }

    bool FindReferense(void* ref){
        for (int i = 0; i < _real_size; i++){
            if (_array[i]->Referense == ref){
                return 1;
            }
        }
        return 0;
    }

    Object* FindObject(void* ref){
        for (int i = 0; i < _real_size; i++){
            if (_array[i]->Referense == ref){
                return _array[i];
            }
        }
    }

    Object* operator[](int index) {
        return _array[index];
    }

    void PrintObject(){
        for (int i = 0; i < _real_size; i++){
            if (_array[i]->Referense == nullptr){
                continue;
            }
            std::cout<<_array[i]->Referense<<"  "<<_array[i]->size<<"  "<<_array[i]->IsAlive<<"\n";
        }
        std::cout<<"\n";
    }

    ~Vector(){
        std::cout<<"destructor Vector\n";
        free(_array);
        std::cout<<"end destructor Vector\n";
    }

};//как пометить элементы при удалении и удалить их только во время расширения?