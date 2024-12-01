#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <setjmp.h>

template <typename... T>
void print(const T &... t) {
  (void)std::initializer_list<int>{(std::cout << t << "", 0)...};
  std::cout << "\n";
}

struct Node;
struct Traceable;
struct ObjectHeader;

static std::map<Traceable *, ObjectHeader *> traceInfo;

struct ObjectHeader{
  bool marked;
  size_t size;
  static void *operator new(size_t size) {
    void *object = malloc(size);
    return object;
  }
};

template <typename T>
void printVector(std::vector<T> const &input) {
  print("\n{");
  for (int i = 0; i < input.size(); i++) {
    print("  ", input.at(i), ", ");
  }
  print("}\n");
}

struct Traceable {
  ObjectHeader *getHeader() { return traceInfo.at(this); }

  static void *operator new(size_t size) {
    void *object = malloc(size);

    auto header = new ObjectHeader{.marked = false, .size = size};
    traceInfo.insert(std::make_pair((Traceable *)object, header));

    return object;
  }
};

struct Node : public Traceable {
  char name;

  Node *left;
  Node *right;
};

void dump(const char *label) {
  print("\n------------------------------------------------");
  print(label);

  print("\n{");

  for (const auto &it : traceInfo) {
    auto node = reinterpret_cast<Node *>(it.first);

    print("  [", node->name, "] ", it.first, ": {.marked = ", it.second->marked,
          ", .size = ", it.second->size, "}, ");
  }

  print("}\n");
}

std::vector<Traceable *> getPointers(Traceable *object) {
  auto p = (uint8_t *)object;
  auto end = (p + object->getHeader()->size);
  std::vector<Traceable *> result;
  while (p < end) {
    auto address = (Traceable *)*(uintptr_t *)p;
    if (traceInfo.count(address) != 0) {
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

std::vector<Traceable *> getRoots() {
  std::vector<Traceable *> result;
  // auto R = new Node{.name = 'H'};//???
  // gcInit();
  jmp_buf jb;
  setjmp(jb);

  __READ_RSP();
  auto rsp = (uint8_t *)__rsp;
  auto top = (uint8_t *)__stackBegin;

  while (rsp < top) {
    auto address = (Traceable *)*(uintptr_t *)rsp;
    if (traceInfo.count(address) != 0) {
      result.emplace_back(address);
    }
    rsp++;
  }

  return result;
}

void mark() {
  auto worklist = getRoots();

  while (!worklist.empty()) {
    auto o = worklist.back();
    worklist.pop_back();
    auto header = o->getHeader();

    if (!header->marked) {
      header->marked = true;
      for (const auto &p : getPointers(o)) {
        worklist.push_back(p);
      }
    }
  }
}

void sweep() {
  auto it = traceInfo.cbegin();
  while (it != traceInfo.cend()) {
    if (it->second->marked) {
      it->second->marked = false;
      ++it;
    } else {
      it = traceInfo.erase(it);
      free(it->first);
    }
  }
}

void gc() {
  mark();
  dump("After mark:");

  sweep();
  dump("After sweep:");
}

