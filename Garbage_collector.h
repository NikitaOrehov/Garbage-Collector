#pragma once
#include "Vector.h"
#include <iostream>

class Garbage_Collector{
private:
    void Mark();
    void Sweep();
    Vector<Object> _AllObject;
public:
    static Garbage_Collector Collector;
    static void AddElement(void* reference){
        Object o;
        o.IsAlive = 0;
        o.Referense = reference;
        Collector._AllObject.push_back(o);
        if (Collector._AllObject.size() % 100 == 0){
            Collector.GC();
        }
    }
    
    static void DeleteElement(void* referense){
        for (int i = 0; i < Collector._AllObject.size(); i++){
            if (Collector._AllObject[i].Referense == referense){
                Collector._AllObject.DeleteElem(i);
                return;
            }
        }
        std::cout<<"error1\n";
    }

    Garbage_Collector(){
        std::cout<<"constructor Collector\n";
    }

    static void GC(){
        Collector._AllObject.DeleteGarbage();
    }

    static void PrintAll(){
        if (Collector._AllObject.size() == 0){
            std::cout<<"Vector empty\n";
        }
        for (int i = 0; i < Collector._AllObject.size(); i++){
            std::cout<<Collector._AllObject[i].Referense<<"\n";
        }
    }
};

void* operator new(size_t size){
    std::cout<<"operator new "<<size<<"\n";
    void* referense = malloc(size);
    if (!referense){
        throw std::bad_alloc();
    }
    Garbage_Collector::AddElement(referense);
    return referense;
}

void operator delete(void* referense){
    std::cout<<"operator delete\n";
    Garbage_Collector::DeleteElement(referense);
}

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

