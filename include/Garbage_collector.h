#pragma once
#include <iostream>
#include <memory>
#include <map>
#include "Vector.h"
#include <setjmp.h>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include "base_table.h"
#include <vector>


HashMap AllObject;

void* operator new(size_t size){
    void* ref = (void*)malloc(size);
    Object* object = static_cast<Object*>(malloc(sizeof(Object)));
    object->size = size;
    object->IsAlive = 0;
    AllObject.insert(ref, object);
    return ref;
}

void* operator new[](size_t size){
    void* ref = malloc(size);
    Object* object = static_cast<Object*>(malloc(sizeof(Object)));
    object->size = size;
    object->IsAlive = 0;
    AllObject.insert(ref, object);
    return ref;
}


void operator delete(void* ref, size_t size){
    AllObject.remove(ref);
}

void operator delete[](void* ref, size_t size){
    AllObject.remove(ref);
}

void Print(){
    std::cout<<AllObject<<"\n";
}
  
Vector<void*> getPointers(void* referense, Object* object) {
  auto start = (uint8_t *)referense;
  auto end = (start + object->size);
  Vector<void *> result;
  while (start < end) {
    auto address = (void *)*(uintptr_t *)start;
    if (AllObject.find(address)) {
      result.push_back(address);
    }
    start += 4;
  }
  return result;
}

intptr_t *__rbp;

intptr_t *__rsp;

intptr_t *__stackBegin;

#define __READ_RBP() __asm__ volatile("movq %%rbp,  %0" :  "=r"(__rbp))
#define __READ_RSP() __asm__ volatile("movq %%rsp,  %0" :  "=r"(__rsp))

void gcInit() {
  __READ_RBP();
  __stackBegin = (intptr_t *)*__rbp;
}

Vector<void *> getRoots() {
  jmp_buf jb;
  // if (setjmp(jb) == 0) {
  //   return {};
  // }

  __READ_RSP();
  auto rsp = (uint8_t *)__rsp;
  auto top = (uint8_t *)__stackBegin;
  Vector<void*> result;
  while (rsp < top) {
    auto address = (void *)*(uintptr_t *)rsp;
    if (AllObject.find(address)) {
      bool status = false;
      for (int i = 0; i < result.size(); i++){
        if (result[i] == address){
          status = true;
          break;
        }
      }
      if (!status){
        result.push_back(address);
      }
    }
    rsp++;
  }

  return result;
}

void mark() {
  Vector<void*> worklist = getRoots();

  // std::cout<<"start worklist---------------------\n";
  // std::cout<<"size:  "<<worklist.size()<<"\n";
  // for (int i = 0; i < worklist.size(); i++){
  //   std::cout<<worklist[i]<<"\n";
  // }
  // std::cout<<"end worklist---------------------\n\n";

  while (!worklist.empty()) {
    void* address = worklist.back();
    worklist.pop_back();
    Object* obj = AllObject.find(address);
    if (!obj->IsAlive) {
      obj->IsAlive = true;
      Vector<void*> pointer = getPointers(address, obj);
      for (int i = 0; i < pointer.size(); i++) {
        worklist.push_back(pointer[i]);
      }
    }
  }
}

int sweep() {
  return AllObject.sweep();
}

int gc() {
  mark();
  return sweep();
}
