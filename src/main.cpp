#include <vector>
#include <iostream>
#include "Garbage_collector.h"

class A{
public: 
    int* a;
    A(){
        a = new int;
    }
};

int main(int argc,  char* argv[]) {
    gcInit();
    A* bb = new A;
    int* aa = new int;
    std::cout<<"---------------------\n";
    ObjectInfo.PrintObject();
    bb->a = nullptr;
    std::cout<<"---------------------\n";
    std::cout<<gc()<<"\n";
    return 0;
}