#include <iostream>
#include "LinkedList.h"
#include "tracking_memory.h"

class ContactBook : public LinkedList<Contact>{
    public:
        void loadData(std::string fileName);
        void writeData(std::string fileName);
        Node<Contact>* filterByLetter(char letter, bool byName, bool bySurname);
        Node<Contact>* search(const std::string &searchTerm, bool byName, bool bySurname);
        int getContactIndex(std::string name, std::string surname); 
};

void ContactBook::loadData(std::string fileName){
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

void ContactBook::writeData(std::string fileName){
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

Node<Contact>* ContactBook::filterByLetter(char letter, bool byName, bool bySurname) {
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

Node<Contact>* ContactBook::search(const std::string &searchTerm, bool byName, bool bySurname){
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

int ContactBook::getContactIndex(std::string name, std::string surname){
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

bool LinkedList<Contact>::updateNode(Contact value, int index){
    bool ok = false;
    Node<Contact> *temp = get(index);
    if(temp != nullptr){
        temp->value = value;
        ok = true;
    }
    return ok;
}