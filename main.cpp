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

int main() {
    gcInit();
    A* bb = new A;
    int* aa = new int;
    std::vector<int> ccc;
    ccc.push_back(1);
    ccc.push_back(1);
    std::cout<<"---------------------\n";
    ObjectInfo.PrintObject();
    bb->a = nullptr;
    std::cout<<"---------------------\n";
    gc();
    return 0;
}