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

    // HashMap<void*, int> hm;
    // hm.insert(new int, 2);
    // std::cout<<hm<<"\n";

    gcInit();
    A* bb = new A;
    std::cout<<"point 1\n";
    int* aa = new int;
    std::cout<<"point 2\n";
    Print();
    std::cout<<"point 3\n";
    bb->a = nullptr;
    std::cout<<"point 4\n";
    std::cout<<gc()<<"\n";
    std::cout<<"point 5\n";
    return 0;



    // List<string, int> ls;
    // ls.push_back("one", 1);
    // ls.push_back("five", 5);
    // ls.push_back("six", 6);
    // std::cout<<ls<<"\n";
    // ls.remove("six");
    // ls.remove("five");
    // std::cout<<ls<<"\n";
}