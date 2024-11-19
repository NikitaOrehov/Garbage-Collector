#include <vector>
#include <iostream>
#include "Garbage_collector.h"

Garbage_Collector Garbage_Collector::Collector;
Allocator Garbage_Collector::_Allocator;
std::vector<Object> Garbage_Collector::_AllObject;
int Garbage_Collector::count = 0;

int main(){
    int* a = new int;
    *a = 3;
    delete a;
    int* b = new int[10];
    int* c = new int[10];
    Garbage_Collector::PrintAll();
    delete [] b;
    Garbage_Collector::PrintAll();
}