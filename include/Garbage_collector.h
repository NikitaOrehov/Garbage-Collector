// #pragma once
// #include <iostream>
// #include <memory>
// #include <map>
// #include "Vector.h"
// #include <setjmp.h>
// #include <unordered_map>
// #include <iterator>
// #include <algorithm>
// #include "base_table.h"
// #include <vector>

// struct Object
// {
//     size_t size = 0;
//     bool IsAlive = 0;
// };

// std::unordered_map<void*, Object*> AllObject;
// HashMap AllObject;

// template<class T>
// T* Mynew(size_t size = 1) {
//     T a = T();
//     void *object = malloc(size * sizeof(T));
//     //std::cout<<"operator new "<<size * sizeof(T)<<" "<<object<<"\n";
//     AllObject[object] = new Object {.size = size * sizeof(T), .IsAlive = 0};
//     return (T*)object;
// }

// void Mydelete(void* ref){//?
//     AllObject.erase(ref);
//     free(ref);
// }




// void Print(){
//   std::cout<<"---------------------\n";
//     for (const auto& p : AllObject){
//         std::cout<<p.first<<" "<<p.second->size<<"\n";
//     }
//     std::cout<<"---------------------\n";
// }

// std::vector<void *> getPointers(void* referense, Object* object) {
//   auto start = (uint8_t *)referense;
//   auto end = (start + object->size);
//   std::vector<void *> result;
//   while (start < end) {
//     auto address = (void *)*(uintptr_t *)start;
//     if (AllObject.find(address) != AllObject.end()) {
//       result.emplace_back(address);
//     }
//     start++;
//   }
//   return result;
// }

// intptr_t *__rbp;

// intptr_t *__rsp;

// intptr_t *__stackBegin;

// #define __READ_RBP() __asm__ volatile("movq %%rbp,  %0" :  "=r"(__rbp))
// #define __READ_RSP() __asm__ volatile("movq %%rsp,  %0" :  "=r"(__rsp))

// void gcInit() {
//   __READ_RBP();
//   __stackBegin = (intptr_t *)*__rbp;
// }

// Vector<void *> getRoots() {
//   jmp_buf jb;
//   // if (setjmp(jb) == 0) {
//   //   return {};
//   // }

//   __READ_RSP();
//   auto rsp = (uint8_t *)__rsp;
//   auto top = (uint8_t *)__stackBegin;
//   // std::vector<void *> result;
//   Vector<void*> result;
//   while (rsp < top) {
//     auto address = (void *)*(uintptr_t *)rsp;
//     if (AllObject.find(address) != AllObject.end()) {
//       bool status = false;
//       for (int i = 0; i < result.size(); i++){
//         if (result[i] == address){
//           status = true;
//           break;
//         }
//       }
//       if (!status){
//         result.push_back(address);
//       }
//     }
//     rsp++;
//   }

//   return result;
// }

// void mark() {
//   Vector<void*> worklist = getRoots();
//   for (int i = 0; i < worklist.size(); i++){//исправляет ошибку, но замедляет.
//       if (AllObject.find(worklist[i]) == AllObject.end()) {
//           worklist[i] = nullptr;
//       }
//   }

//   std::cout<<"start worklist---------------------\n";
//   std::cout<<"size:  "<<worklist.size()<<"\n";
//   for (int i = 0; i < worklist.size(); i++){
//     std::cout<<worklist[i]<<"\n";
//   }
//   std::cout<<"end worklist---------------------\n";

//   while (!worklist.empty()) {
//     void* address = worklist.back();
//     worklist.pop_back();
//     auto it = AllObject.find(address);
//     if (!it->second->IsAlive) {
//       it->second->IsAlive = true;
//       for (const auto &p :  getPointers(it->first, it->second)) {
//         worklist.push_back(p);
//       }
//     }
//   }
// }

// int sweep() {
//   int count = 0;
//   auto p = AllObject.begin();
//   auto end = AllObject.end();
//   while (p != end){
//     if (p->second->IsAlive == true){
//       p->second->IsAlive = false;
//       count += p->second->size;
//       p++;
//     }
//     else{
//       Object* ob = p->second;
//       void* ref = p->first;
//       p = AllObject.erase(p);
//       free(ob);
//       free(ref);
//     }
//   }
//   return count;
// }

// int gc() {
//   mark();
//   return sweep();
// }








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

// struct Object
// {
//     size_t size = 0;
//     bool IsAlive = 0;
// };

HashMap AllObject;

// template<class T>
// T* Mynew(size_t size = 1) {
//     T a = T();
//     void *object = malloc(size * sizeof(T));
//     //std::cout<<"operator new "<<size * sizeof(T)<<" "<<object<<"\n";
//     AllObject[object] = new Object {.size = size * sizeof(T), .IsAlive = 0};
//     return (T*)object;
// }

// void Mydelete(void* ref){//?
//     AllObject.erase(ref);
//     free(ref);
// }

void* operator new(size_t size){
    std::cout<< "start operator new\n";
    void* ref = (void*)malloc(size);
    Object object = Object {.size = size, .IsAlive = 0};   
    object.size = size;
    object.IsAlive = 0;
    AllObject.insert(ref, object);
    std::cout<< "end operator new\n";
    return ref;
}
//Object* object = (Object*)malloc(sizeof(Object));  
void* operator new[](size_t size){
  std::cout<< "start operator new[]\n";
    void* ref = malloc(size);
    Object object = Object {.size = size, .IsAlive = 0};     
    object.size = size;
    object.IsAlive = 0;
    AllObject.insert(ref, object);
    std::cout<< "end operator new[]\n";
    return ref;
}


void operator delete(void* ref, size_t size){
    
}

void operator delete[](void* ref, size_t size){
  
}



void Print(){
    std::cout<<AllObject<<"\n";
}
  

std::vector<void *> getPointers(void* referense, Object* object) {
  auto start = (uint8_t *)referense;
  auto end = (start + object->size);
  std::vector<void *> result;
  while (start < end) {
    auto address = (void *)*(uintptr_t *)start;
    if (AllObject.find(address)) {
      result.emplace_back(address);
    }
    start++;
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
  // std::vector<void *> result;
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
  for (int i = 0; i < worklist.size(); i++){//исправляет ошибку, но замедляет.
      if (!AllObject.find(worklist[i])) {
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
    void* address = worklist.back();
    worklist.pop_back();
    Object* obj = AllObject.find(address);
    if (!obj->IsAlive) {
      obj->IsAlive = true;
      for (const auto &p :  getPointers(address, obj)) {
        worklist.push_back(p);
      }
    }
  }
}

int sweep() {
  int count = 0;
  // auto p = AllObject.begin();
  // auto end = AllObject.end();
  // while (p != end){
  //   if (p->second->IsAlive == true){
  //     p->second->IsAlive = false;
  //     count += p->second->size;
  //     p++;
  //   }
  //   else{
  //     Object* ob = p->second;
  //     void* ref = p->first;
  //     p = AllObject.erase(p);
  //     free(ob);
  //     free(ref);
  //   }
  // }

  return AllObject.sweep();
}

int gc() {
  mark();
  std::cout<<"after mark\n";
  Print();
  return sweep();
}
