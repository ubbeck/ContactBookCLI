#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "contact.h"
#include "tracking_memory.h"

template<typename T>
class Node{
    public:
        T value;
        Node *next;
    
        Node(){
            next = nullptr;
        }

        Node(const T &value){
            this->value = value;
            next = nullptr;
        }

        static void printNode(Node<T> *node);
        static void deleteNode(Node<T> *node);
};

template<typename T>
void Node<T>::printNode(Node<T> *node){
    Node<T> *temp = node;
    while(temp != nullptr){
        std::cout << temp->value;
        temp = temp->next;
        std::cout << "\n";
    }
    std::cout << "\n";
}

template<typename T>
void Node<T>::deleteNode(Node<T> *node){
    Node<T> *runner = node;
    while(node != nullptr){
        node = node->next;
        delete runner;
        runner = node;
    }
}

template<typename T>
class LinkedList{

    protected:
        Node<T> *head;
        Node<T> *tail;
        int length;

        Node<T>* get(int index);
        void deleteLast();
        void deleteFirst();
    
    public:
        LinkedList();
        LinkedList(const T &value);
        ~LinkedList();
        void printList();
        void append(T value);
        void deleteNode(int index);
        void removeDuplicates();
        bool updateNode(T value, int index);
};

/* ------------------------ PROTECTED METHODS ------------------------ */
template<typename T>
Node<T>* LinkedList<T>::get(int index){
    Node<T> *temp = nullptr;
    if(index < 0 || index >= length) {return temp;}
    else{
        temp = head;
        for(int i = 0; i < index; i++){
            temp = temp->next;
        }
    }
    return temp;
}

template<typename T>
void LinkedList<T>::deleteLast(){
    Node<T> *temp = head;
    if(length == 0) {return;}
    else if(length == 1){
        head = nullptr;
        tail = nullptr;
    }
    else{
        Node<T> *pre = head;
        while(temp->next != nullptr){
            pre = temp;
            temp = temp->next;
        }
        tail = pre;
        pre->next = nullptr;
    }
    delete temp;
    length--;
}

template<typename T>
void LinkedList<T>::deleteFirst(){
    if(length == 0) {return;}
    Node<T> *temp = head;
    if(length == 1){
        head = nullptr;
        tail = nullptr;
        temp->next = nullptr;
    }
    else{
        head = head->next;
        temp->next = nullptr;
    }
    delete temp;
    length--;
}

/* ------------------------ PUBLIC METHODS ------------------------ */
template<typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const T &value){
    Node<T> *newNode = new Node(value);
    head = newNode;
    tail = newNode;
    length = 1;
}

template<typename T>
LinkedList<T>::~LinkedList(){
    Node<T> *temp = head;
    while(head != nullptr){
        head = head->next;
        delete temp;
        temp = head;
    }
}

template<typename T>
void LinkedList<T>::printList(){
    Node<T> *temp = head;
    while(temp != nullptr){
        std::cout << temp->value << "\n";
        temp = temp->next;
    }
    std::cout << "Length: " << length << "\n";
    std::cout << "\n";
}

template<typename T>
void LinkedList<T>::append(T value){
    Node<T> *newNode = new Node<T>(value);
    if(length == 0){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}

template<typename T>
void LinkedList<T>::deleteNode(int index){
    if(index < 0 || index >= length) {return;}
    if(index == 0) {return deleteFirst();}
    if (index == length - 1) {return deleteLast();}

    Node<T> *prev = get(index - 1);
    Node<T> *temp = prev->next;

    prev->next = temp->next;
    temp->next = nullptr;
    delete temp;
    length--; 
}

template<typename T>
void LinkedList<T>::removeDuplicates(){
    if(head == nullptr || length == 1) {return;}
    Node<T> *current = head;
    Node<T> *runner = head;
    Node<T> *toRemove = nullptr;
    while(current != nullptr && current->next != nullptr){
        runner = current;
        while(runner != nullptr && runner->next != nullptr){
            if(runner->next->value == current->value){
                toRemove = runner->next;
                runner->next = runner->next->next;
                toRemove->next = nullptr;
                delete toRemove;
                length--;
            }
            runner = runner->next;
        }
        current = current->next;
    }
}

template<typename T>
bool LinkedList<T>::updateNode(T value, int index){
    bool ok = false;
    Node<T> *temp = get(index);
    if(temp != nullptr){
        temp->value = value;
        ok = true;
    }
    return ok;
}

#endif //LINKED_LIST_H