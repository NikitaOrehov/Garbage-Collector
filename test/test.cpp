#include <iostream>
#include <vector>
#include <string>
#include "Garbage_collector.h"

class A{
public:
    int* a;
    int* b;
    A(size_t size = 10){
        a = Mynew<int>(size);
        b = Mynew<int>(size);
    }
};

void test0_1(){
    int* a = Mynew<int>(20);
    int* b = Mynew<int>(20);
}

void test1_1(){
    A a;
}

void test2_1(){
    int* a = Mynew<int>(20);
    int* b = Mynew<int>(20);
    A c;
}

void test5_1(){
    std::vector<int> a;
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
}






void test0(){
    test0_1();
    std::cout<<"test0: "<<gc()<<"\n";
}

void test1(){
    test1_1();
    std::cout<<"test1: "<<gc()<<"\n";
}

void test2(){//не хочет очищяться с первого раза
    test2_1();
    std::cout<<"test2: "<<gc()<<"\n";
}

void test3(){
    A* a = Mynew<A>();
    Mydelete(a);
    std::cout<<"test3: "<<gc()<<"\n";
}

void test4(){//?
    A* a = Mynew<A>();
    a = nullptr;
    std::cout<<"test4: "<<gc()<<"\n";
}

void test5(){
    A a;
    a.b = nullptr;
    std::cout<<"test5: "<<gc()<<"\n";
}

void test6(){
    test5_1();
    std::cout<<"test6: "<<gc()<<"\n";
}

void test7(size_t size){
    for (int i = 0; i < size; i++){
        int* a = Mynew<int>(20);
    }
}

int main(){
    gcInit();
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7(200);
    int* aaa = Mynew<int>();
    *aaa = 5;
    std::cout<<"test7: "<<gc()<<"\n";
    return 0;
}