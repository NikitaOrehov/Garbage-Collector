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
    void Mark();
    void Sweep();
public:
    static Garbage_Collector Collector;
    static int count;
    static std::vector<Object> _AllObject;
    static Allocator _Allocator;
    static void AddElement(void* reference){
        Object o;
        o.IsAlive = 0;
        o.Referense = reference;
        Collector._AllObject.push_back(o);
    }
    
    static void DeleteElement(void* referense){
        for (auto i = _AllObject.begin(); i != _AllObject.end(); i++){
            if (i->Referense == referense){
                _AllObject.erase(i);
                return;
            }
        }
        std::cerr << "Warning: Attempt to unregister unregistered pointer: " << referense << std::endl;
    }

    Garbage_Collector(){
        std::cout<<"constructor Collector\n";
    }

    void GC(){

    }

    static void PrintAll(){
        for (int i = 0; i < Collector._AllObject.size(); i++){
            std::cout<<_AllObject[i].Referense<<"\n";
        }
    }
};

// void* operator new(size_t size){
//     std::cout<<"operator new "<<size<<"\n";
//     void* referense = malloc(size);
//     if (!referense){
//         throw std::bad_alloc();
//     }
//     Garbage_Collector::AddElement(referense);
//     return referense;
// }

// void operator delete(void* referense){
//     std::cout<<"operator delete\n";
//     Garbage_Collector::DeleteElement(referense);
// }

void* operator new[](size_t size){
    std::cout<<"operator new[] :"<<size<<"\n";
    void* referense = malloc(size);
    if (!referense){
        throw std::bad_alloc();
    }
    Garbage_Collector::AddElement(referense);
    return referense;
}

void operator delete[](void* ptr){
    std::cout << "operator delete[] called\n";
    Garbage_Collector::DeleteElement(ptr);
    free(ptr);
}

// #define new new(__FILE__)

