#include <vector>
#include <iostream>
#include "Garbage_collector.h"

Garbage_Collector a;
Allocator Garbage_Collector::_allocator;
std::vector<Object> Garbage_Collector::_AllObject;
int Garbage_Collector::count = 0;

int main(){
    int* b = new int;
    double* c = new double;
    int* e = new int;
    *b = 2;
    *c = 3;
    *e = 4;
    std::cout<<"b = "<<*b<<"\n";
    std::cout<<"c = "<<*c<<"\n";
    std::cout<<"e = "<<*e<<"\n";
    delete b;
    delete e;
    delete c;
    std::cout<<a.count<<"\n";
}