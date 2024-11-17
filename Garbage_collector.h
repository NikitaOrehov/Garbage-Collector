#pragma once
#include <vector>
#include "Allocator.h"
#include <iostream>

struct Object
{
    void* Referense;
    bool IsAlive = 0;
};

class Garbage_Collector{
private:
    static std::vector<Object> _AllObject;
    static Allocator _allocator;
    void Mark();
    void Sweep();
public:
    static int count;
    Garbage_Collector(){
        std::cout<<"constructor Collector\n";
    }

    void GC();

    friend void* operator new(size_t n){
        std::cout<<"operator new  size = "<<n<<"\n";
        count++;
        Object o;
        o.IsAlive = 0;
        o.Referense = malloc(n);
        // _AllObject.push_back(o);
        // o.Referense = _allocator.GetMemory(n);
        _AllObject.push_back(o);
        return o.Referense;
    }

    friend void operator delete(void* ptr, size_t n){
        std::cout<<"operator delete"<<"\n";
        free(ptr);
    }

    friend void* operator new[](size_t n);

    friend void operator delete[](void* ptr);

    void PrintAllObject(){
        for (int i = 0; i < _AllObject.size(); i++){
            std::cout<<_AllObject[i].Referense<<" ";
        }
        std::cout<<"\n";
    }
};