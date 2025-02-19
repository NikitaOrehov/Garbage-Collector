#include "Vector.h"

void Vector::expansion(){
    _max_size *= 2;
    Object** p = (Object**)malloc(sizeof(Object*) * _max_size);
    for (int i = 0; i < _max_size; i++){
        p[i] = (Object*)malloc(sizeof(Object));
    }
    _real_size = 0;
    for (int i = 0; i < _size; i++){
        if (_array[i]->Referense == nullptr){
            free(_array[i]);
            continue;
        }
        p[_real_size] = _array[i];
        _real_size++;
    }
    _size = _real_size;
    free(_array);
    _array = p;
}

Vector::Vector(size_t max_size) :  _max_size(max_size){
    std::cout<<"constructor Vector\n";
    _size = 0;
    _real_size = 0;
    _array = (Object**)malloc(sizeof(Object*) * _max_size);
    for (int i = 0; i < _max_size; i++){
        _array[i] = (Object*)malloc(sizeof(Object));
    }
}

size_t Vector::size() const {
    return _size;
}

void Vector::push_back(Object object){
    if (_size == _max_size){
        expansion();
    }
    _array[_size]->IsAlive = object.IsAlive;
    _array[_size]->Referense = object.Referense;
    _array[_size]->size = object.size;
    _real_size++;
    _size++;
}

void Vector::DeleteElem(int index){
    std::cout<<"delete elem\n";
    void* j = _array[index]->Referense;
    free(_array[index]->Referense);
    _array[index]->Referense = nullptr;
    _real_size--;
    free(_array[index]);
    Object* o = (Object*)malloc(sizeof(Object));
    o->Referense = nullptr;
    o->IsAlive = 0;
    o->size = 0;
    _array[index] = o;
}

void Vector::DeleteElem(void* ref){
    std::cout<<"delete elem\n";
    for (int i = 0; i < _size; i++){
        if (ref == _array[i]->Referense){
            free(_array[i]->Referense);
            _array[i]->Referense = nullptr;
            _real_size--;
            free(_array[i]);
            Object* o = (Object*)malloc(sizeof(Object));
            o->Referense = nullptr;
            o->IsAlive = 0;
            o->size = 0;
            _array[i] = o;
        }
    }
}

bool Vector::FindReferense(void* ref){
    if (ref == nullptr){
        return false;
    }
    for (int i = 0; i < _size; i++){
        if (_array[i]->Referense == ref){
            return true;
        }
    }
    return false;
}

Object* Vector::FindObject(void* ref){
    for (int i = 0; i < _size; i++){
        if (_array[i]->Referense == ref){
            return _array[i];
        }
    }
    return nullptr;
}

Object* Vector::operator[](int index) {
    return _array[index];
}

void Vector::PrintObject(){
    for (int i = 0; i < _size; i++){
        if (_array[i]->Referense == nullptr){
            continue;
        }
        std::cout<<_array[i]->Referense<<"  "<<_array[i]->size<<"  "<<_array[i]->IsAlive<<"\n";
    }
    std::cout<<"\n";
}

Vector::~Vector(){
    std::cout<<"destructor Vector\n";
    for (int i = 0; i < _size; i++){
        free(_array[i]);
    }
    free(_array);
    std::cout<<"end destructor Vector\n";
}