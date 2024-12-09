#pragma once
#include <iostream>
#include <memory>
#include <map>
#include "Vector.h"
#include <vector>
#include <setjmp.h>

Vector ObjectInfo;

void *operator new(size_t size) {
    void *object = malloc(size);
    std::cout<<"operator new "<<object<<"\n";

    Object header = Object{.Referense = object,  .size = size,  .IsAlive = 0};
    ObjectInfo.push_back(header);

    return object;
}

void *operator new[](size_t size) {
    void *object = malloc(size);
    std::cout<<"operator new[]"<<object<<"\n";

    Object header = Object{.Referense = object,  .size = size,  .IsAlive = 0};
    ObjectInfo.push_back(header);

    return object;
}

void operator delete(void* ref){
    std::cout<<"operator delete "<<ref<<"\n";
    ObjectInfo.DeleteElem(ref);
}

void operator delete[](void* ref){
    std::cout<<"operator delete[]" <<ref<<"\n";
    ObjectInfo.DeleteElem(ref);
}

std::vector<void *> getPointers(Object *object) {
  // std::cout<<"referense:  "<<object->Referense<<"  size:  "<<object->size<<"\n";
  auto p = (uint8_t *)object->Referense;
  auto end = (p + object->size);
  std::vector<void *> result;
  while (p < end) {
    auto address = (void *)*(uintptr_t *)p;
    if (ObjectInfo.FindReferense(address) != 0) {
      result.emplace_back(address);
    }
    p++;
  }
  
  // for (int i = 0; i < result.size(); i++){
  //     // std::cout<<"getPointer ref: "<<result[i]<<"\n";
  // }
  // std::cout<<"end getPointer\n";
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

std::vector<void *> getRoots() {
  jmp_buf jb;
//   if (setjmp(jb) == 0) {
//     return {};
//   }

  __READ_RSP();
  auto rsp = (uint8_t *)__rsp;
  auto top = (uint8_t *)__stackBegin;
  std::vector<void *> result;
  while (rsp < top) {
    auto address = (void *)*(uintptr_t *)rsp;
    if (ObjectInfo.FindReferense(address) != 0) {
      bool status = false;
      for (int i = 0; i < result.size(); i++){
        if (result[i] == address){
          status = true;
          break;
        }
      }
      if (!status){
        result.emplace_back(address);
      }
    }
    rsp++;
  }

  return result;
}

void mark() {
  std::vector<void*> worklist = getRoots();
  for (int i = 0; i < worklist.size(); i++){
      if (ObjectInfo.FindReferense(worklist[i]) == 0){
          worklist[i] = nullptr;
      }
  }
  std::cout<<"start worklist---------------------\n";
  std::cout<<"size:  "<<worklist.size()<<"\n";
  for (int i = 0; i < worklist.size(); i++){
    std::cout<<worklist[i]<<"\n";
  }
  std::cout<<"end worklist---------------------\n";
  while (!worklist.empty()) {
    void* o = worklist.back();
    worklist.pop_back();
    Object* object = ObjectInfo.FindObject(o);
    bool b = object->IsAlive;
    if (!object->IsAlive) {
      object->IsAlive = true;
      for (const auto &p :  getPointers(object)) {
        worklist.push_back(p);
      }
    }
  }
}

void sweep() {
  for (int i = 0; i < ObjectInfo.size(); i++){
    if (ObjectInfo[i]->IsAlive == true){
      ObjectInfo[i]->IsAlive = false;
    }
    else{
      ObjectInfo.DeleteElem(i);
    }
  }
}

void gc() {
  mark();
  std::cout<<"after mark -----------------------\n";
  ObjectInfo.PrintObject();
  std::cout<<"after sweep -----------------------\n";
  sweep();
  ObjectInfo.PrintObject();
}
