#include <vector>
#include <iostream>
#include "Garbage_collector.h"

// void* operator new(size_t size){
//     void *object = malloc(size);

//     auto header = new ObjectHeader{.marked = false, .size = size};
//     traceInfo.insert(std::make_pair((Traceable *)object, header));

//     return object;
// }

class B: public Traceable{
public:
    int* _a;
    B(){
        _a = new int[15];
    }
};

class A: public Traceable{
public:
    B* _bb;
    A(){
        _bb = new B;
    }
};

int main(int argc, char const *argv[]) {
    gcInit();
    A* _aaaa = new A;
    _aaaa->_bb = nullptr;
    // auto A = createGraph();

    dump("Allocated graph:");

    // A->right = nullptr;

    gc();
    _aaaa->_bb = new B;
    return 0;
}