#include <iostream>
#include "Garbage_collector.h"
#include "base_table.h"
#include <string>

using namespace std;

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
    Print();
    bb->a = nullptr;
    std::cout<<gc()<<" end gc\n";
    Print();
    return 0;
}