#pragma once
#include <iostream>

class Allocator{
private:
    char* memory;
    char* start;
    char* end;
    char* correct;
public:
    Allocator(){
        std::cout<<"constructor Allocator\n";
        memory = (char*)malloc(10000);
        start = memory;
        end = memory + 10000;
        correct = start + 1;
    }
    void* GetMemory(size_t n){
        if (correct + n > end){
            throw "888888/n";
        }
        else{
            correct = correct + n;
            return correct - n;
        }
    }
};