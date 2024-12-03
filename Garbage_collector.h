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

    Object header = Object{.Referense = object, .size = size, .IsAlive = 0};
    ObjectInfo.push_back(header);

    return object;
}

std::vector<void *> getPointers(Object *object) {
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
  return result;
}

intptr_t *__rbp;

intptr_t *__rsp;

intptr_t *__stackBegin;

#define __READ_RBP() __asm__ volatile("movq %%rbp, %0" : "=r"(__rbp))
#define __READ_RSP() __asm__ volatile("movq %%rsp, %0" : "=r"(__rsp))

void gcInit() {
  __READ_RBP();
  __stackBegin = (intptr_t *)*__rbp;
}

std::vector<void *> getRoots() {
  std::vector<void *> result;
  // auto R = new Node{.name = 'H'};//???
  // gcInit();
  jmp_buf jb;
  setjmp(jb);

  __READ_RSP();
  auto rsp = (uint8_t *)__rsp;
  auto top = (uint8_t *)__stackBegin;

  while (rsp < top) {
    auto address = (void *)*(uintptr_t *)rsp;
    if (ObjectInfo.FindReferense(address) != 0) {
      result.emplace_back(address);
    }
    rsp++;
  }

  return result;
}

void mark() {
  std::vector<void*> worklist = getRoots();//4 объекта создаст
  while (!worklist.empty()) {
    void* o = worklist.back();
    worklist.pop_back();
    Object* object = ObjectInfo.FindObject(o);
    if (!object->IsAlive) {
      object->IsAlive = true;
      for (const auto &p : getPointers(object)) {
        worklist.push_back(p);
      }
    }
  }
}

void sweep() {
  for (int i = 0; i < ObjectInfo.size(); i++){
    if (ObjectInfo[i]->IsAlive == true){
      ObjectInfo[i]->IsAlive == false;
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

