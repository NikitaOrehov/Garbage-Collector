#include <vector>
#include <iostream>
#include "Garbage_collector.h"

Garbage_Collector Garbage_Collector::Collector;

int main(){
    int* a = new int;
    *a = 3;
    delete a;
    std::cout<<"a: "<<*a<<"\n";
    int* b = new int[10];
    Garbage_Collector::PrintAll();
    b[0] = -3;
    b[1] = -4;
    delete [] b;
    b[1] = -2;
    std::cout<<"b= "<<b<<"\n";
    Garbage_Collector::PrintAll();
}