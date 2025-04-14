#pragma once
#include <iostream>
#include <cstdint>
#include "Vector.h"


struct Object
	{
    	size_t size = 0;
    	bool IsAlive = 0;
		friend std::ostream& operator<<(std::ostream& os, Object& obj){
			std::cout<<"("<<obj.size<<", "<<obj.IsAlive<<")";
			return os;
		}
	};

struct record{
    void* key;
    Object* data;
    record(void* k, Object* d){
        key = k;
        data = d;
    }
    record(const record& rec) = delete;
    record operator=(const record& rec) = delete;
    ~record(){
        free(key);
        free(data);
    }
};

struct Node{
    record* data;
    Node* next;
    ~Node(){
        data->~record(); 
    }
};

struct ListIterator{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = record;
    using pointer = record*;
    using reference = record&;
    ListIterator(Node* node): _node(node){};
    const reference operator*()const{return *_node->data;}
    const pointer operator->(){return _node->data;}
    ListIterator operator++(int){
        ListIterator tmp=*this;
        ++(*this);
        return tmp;
    }
    ListIterator& operator++(){
        _node = _node->next;
        return *this;
    }
    friend bool operator==(const ListIterator& a,const ListIterator& b){
        return a._node==b._node;
    }
    friend bool operator!=(const ListIterator& a,const ListIterator& b){
		bool status = a._node != b._node;
        return status;
    }

private:
    Node* _node;
};



class List{
private:
    Node* _head;
    Node* _tail;
public:
    List(){
        _head = nullptr;
		_tail = nullptr;
    }
    
    void push_back(void* key, Object* data) {
		Node* node = static_cast<Node*>(malloc(sizeof(Node)));
        node->data = (record*)malloc(sizeof(record));
        node->data->key = key;
        node->data->data = data;
		node->next = nullptr;
        if (_head == nullptr){
            _head = node;
            _tail = node;
        }
        else{
            _tail->next = node;
            _tail = _tail->next;
        }
    }

	void remove(void* value) {
        Node* current = _head;
        Node* previous = nullptr;

        while (current) {
            if (current->data->key == value) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    _head = current->next;
                }
                if (current == _tail) {
                    _tail = previous;
                }
                free(current);
                return;
            }
            previous = current;
            current = current->next;
        }
    }

	int sweep(){
		int count = 0;
        int test = 0;
		Node* current = _head;
		Node* previous = nullptr;
		while(current){
			if (!current->data->data->IsAlive){
				if (previous)previous->next = current->next;
				else _head = current->next;
				if (current == _tail){
					_tail = previous;
                    current->~Node();
					return count;
				}
				Node* tmp = current;
				current = current->next;
				tmp->~Node();
                test++;
				continue;
			}
            current->data->data->IsAlive = 0;
			count += current->data->data->size;
			previous = current;
			current = current->next;
		}
		return count;
	}

	Object* contains(void* value){
		for (auto it = begin(); it != end(); it++){
			if (it->key == value){
				return it->data;
			}
		}
		return nullptr;
	}

	bool empty() { return _head == nullptr;}

    ListIterator begin(){
        return ListIterator(_head);
    }

    ListIterator end(){
        return ListIterator(nullptr);
    }

    friend std::ostream& operator<<(std::ostream& os, List& f){
        Node* tmp = f._head;
        while (tmp != nullptr){
            std::cout<<tmp->data->key <<" " << *tmp->data->data << " | ";
            tmp = tmp->next;
        }
		return os;
    }
};


class HashMap{
private:
	Vector<List> table;
	size_t size = 1024;

	size_t hash(const void* key) {
        return reinterpret_cast<uintptr_t>(key) % size;
    }
public:
	HashMap() : table(1024){}
	
	void insert(void* key, Object* data){
		size_t index = hash(key);
		table[index].push_back(key, data);
	}

	void remove(void* key){
		size_t index = hash(key);
		table[index].remove(key);
	}

	Object* find(void* key){
		size_t index = hash(key);
		return table[index].contains(key);
	}

	int sweep(){
		int count = 0;
		for (int i = 0; i < size; i++){
			count += table[i].sweep();
		}
		return count;
	}

	friend std::ostream& operator<<(std::ostream& os, HashMap& h){
        std::cout<<"\n";
        for (int i = 0; i < h.size; i++){
			if (h.table[i].empty()) continue;
			std::cout<<"count: "<<i<<" ";
			std::cout<<" | " << h.table[i] << "\n";
		}
		return os;
    }
};












	// void pop_back(T data){
    //     Node<T>* prev=_head;
    //     Node<T>* next_node;
    //     for(auto lit=begin();lit!=end();lit++){
    //         if(lit==begin()){
    //             if(*lit==data){
    //                 _head=_head->Next;
    //                 return ;
    //             }
    //         }
    //         else{
    //             if(*lit==data){
    //                 if(lit==_tail){
    //                     _tail=prev;
    //                     return ;
    //                 }
    //                 else{
    //                     next_node=prev->Next->Next;
    //                     prev->Next=next_node;
    //                     if(lit==_tail)
    //                         _tail=prev;
    //                     return ;
    //                 }
    //             }
    //             prev=prev->Next;

    //         }
    //     }
    //     std::cout<<"the object you want to delete is not in the queue"<<std::endl;   
    // }

	// bool find(T data){
    //     for(auto lit=begin();lit!=end();lit++){
    //         if(*lit==data)
    //             return true;
    //     }
    //     return false;
    // }






// #ifndef BASE_TABLE_H
// #define BASE_TABLE_H

// #include <string>
// #include <stdexcept>
// #include <vector>

// using namespace std;

// const size_t max_fill = 1000;

// template<class T, class B>
// class Base_table
// {
// protected:
// 	struct record
// 	{
// 		T key;
// 		B data;
// 	};
// 	size_t Fill;
// public:
// 	virtual const B& find(const T& name) const = 0;
// 	virtual bool insert(const T& name, const B& obj) = 0;
// 	virtual bool delete_rec(const T& name) = 0;
// 	virtual bool isEmpty() const = 0;
// 	virtual ~Base_table() = default;
// };

// #endif