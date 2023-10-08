#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "tracking_memory.h"

#include "contact.h"

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

    static void printNode(Node<T> *node){
        Node<T> *temp = node;
        while(temp != nullptr){
            std::cout << temp->value;
            temp = temp->next;
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    static void deleteNode(Node<T> *node){
        Node<T> *runner = node;
        while(node != nullptr){
            node = node->next;
            delete runner;
            runner = node;
        }
    }
};

template<typename T>
class LinkedList{

    private:
        Node<T> *head;
        Node<T> *tail;
        int length;

        Node<T>* get(int index){
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

        void deleteLast(){
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

        void deleteFirst(){
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
    
    public:

        LinkedList(){
            head = nullptr;
            tail = nullptr;
            length = 0;
        }

        LinkedList(const T &value){
            Node<T> *newNode = new Node(value);
            head = newNode;
            tail = newNode;
            length = 1;
        }

        ~LinkedList(){
            Node<T> *temp = head;
            while(head != nullptr){
                head = head->next;
                delete temp;
                temp = head;
            }
        }

        void printList(){
            Node<T> *temp = head;
            while(temp != nullptr){
                std::cout << temp->value << "\n";
                temp = temp->next;
            }
            std::cout << "Length: " << length << "\n";
            std::cout << "\n";
        }

        void append(T value){
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

        void deleteNode(int index){
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

        void removeDuplicates(){
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

        bool updateNode(T value, int index){
            bool ok = false;
            Node<T> *temp = get(index);
            if(temp != nullptr){
                temp->value = value;
                ok = true;
            }
            return ok;
        }

        void loadData(std::string fileName);
        void writeData(std::string fileName);
        Node<T>* filterByLetter(char letter, bool byName, bool bySurname);
        Node<T>* search(const std::string &searchTerm, bool byName, bool bySurname);
        int getContactIndex(std::string name, std::string surname);
};

template<>
void LinkedList<Contact>::loadData(std::string fileName){
    std::ifstream file;
    char sentinel = ' ', aux;

    file.open(fileName);

    if(file.is_open()){
        while(sentinel != '0'){
            Contact contact = Contact::loadContact(file);
            append(contact);
            file.get(aux);
            file.get(sentinel);
        }
        file.close();
    }
}

template<>
void LinkedList<Contact>::writeData(std::string fileName){
    std::ofstream file;
    Node<Contact> *temp = head;
    file.open(fileName);

    while(temp != nullptr){
        Contact::writeContact(file, temp->value);
        file << "\n";
        if(temp->next != nullptr) {file << "\n";}
        temp = temp->next;
    }
    file << "0";
    file.close();
}

template<>
Node<Contact>* LinkedList<Contact>::filterByLetter(char letter, bool byName, bool bySurname) {
    Node<Contact> *newList = nullptr;
    Node<Contact> *lastNode = nullptr;
    Node<Contact> *temp = head;
    bool match = true;

    while (temp != nullptr) {
        if (byName) {
            match = match && (temp->value.getName()[0] == letter);
        }
        if(bySurname){
            match = match && (temp->value.getSurname()[0] == letter);
        }
        if(match){
            Node<Contact> *newNode = new Node<Contact>(temp->value);
            if(newList == nullptr){
                newList = newNode;
                lastNode = newNode;
            }
            else{
                lastNode->next = newNode;
                lastNode = lastNode->next;
            }
        }
        temp = temp->next;
        match = true;
    }
    return newList;
}

template<>
Node<Contact>* LinkedList<Contact>::search(const std::string &searchTerm, bool byName, bool bySurname){
    Node<Contact> *newList = nullptr;
    Node<Contact> *lastNode = nullptr;
    Node<Contact> *temp = head;
    bool match = true;

    while(temp != nullptr){
        if(byName){
            match = match && (temp->value.getName() == searchTerm);
        }
        if(bySurname){
            match = match && (temp->value.getSurname() == searchTerm);
        }
        if(match){
            Node<Contact> *newNode = new Node<Contact>(temp->value);
            if (newList == nullptr) {
                newList = newNode;
                lastNode = newNode;
            } else {
                lastNode->next = newNode;
                lastNode = newNode;
            }
        }
        temp = temp->next;
        match = true;
    }
    return newList;
}

template<>
int LinkedList<Contact>::getContactIndex(std::string name, std::string surname){
    int index = -1;
    if(length == 0) {return -1;}
    else if(length == 1) {return 0;}
    else{
        Node<Contact> *temp = head;
        index = 0;
        while(temp->value.getName() != name && temp->value.getSurname() != surname){
            temp = temp->next;
            index++;
        }
    }
    return index;
}

template<>
bool LinkedList<Contact>::updateNode(Contact value, int index){
    bool ok = false;
    Node<Contact> *temp = get(index);
    if(temp != nullptr){
        temp->value = value;
        ok = true;
    }
    return ok;
}

#endif //LINKED_LIST_H