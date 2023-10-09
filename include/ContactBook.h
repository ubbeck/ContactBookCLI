#include <iostream>
#include "LinkedList.h"
#include "tracking_memory.h"

class ContactBook : public LinkedList<Contact>{
    public:
        Contact createContact();
        void loadData(std::string fileName);
        void writeData(std::string fileName);
        int numberContacts();
        Node<Contact>* filterByLetter(char letter, bool byName, bool bySurname);
        Node<Contact>* search(const std::string &searchTerm, bool byName, bool bySurname, bool byEmail);
        int getContactIndex(std::string name, std::string surname);
        int searchType();
        Node<Contact>* userInputToSearch(int op);
        bool addContact();
        int toUpdate();
        void modifyContactValues(Contact &contact);
        bool updateContact(); 
};

Contact ContactBook::createContact(){
    std::string name, surname, email;
    int phone;
    std::cout << "Name: ";
    std::cin.ignore();
    std::getline(std::cin, name, '\n');
    std::cout << "Surname: ";
    std::getline(std::cin, surname, '\n');
    std::cout << "Email: ";
    std::getline(std::cin, email, '\n');
    std::cout << "Phone: ";
    std::cin >> phone;
    Contact newContact(name, surname, email, phone);
    return newContact;
}

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

int ContactBook::numberContacts(){
    return length;
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

Node<Contact>* ContactBook::search(const std::string &searchTerm, bool byName, bool bySurname, bool byEmail){
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
        if(byEmail){
            match = match && (temp->value.getEmail() == searchTerm);
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
        while(temp != nullptr){
            if(temp->value.getName() == name && temp->value.getSurname() == surname) {return index;}
            temp = temp->next;
            index++;
        }
    }
    return -1;
}

int ContactBook::searchType(){
    int op = -1;
    std::cout << "Search by:\n";
    while(op < 0 || op > 3){
        std::cout << "1.Name\n";
        std::cout << "2.Surname\n";
        std::cout << "3.Email\n";
        std::cout << "0.Back\n";
        std::cout << " >> ";
        std::cin >> op;
    }
    return op;
}

Node<Contact>* ContactBook::userInputToSearch(int op){
    Node<Contact> *temp = nullptr;
    std::string aux;
    switch (op)
    {
    case 1:
    {
        std::cout << "Name: ";
        std::cin.ignore();
        std::getline(std::cin, aux, '\n');
        temp = search(aux, true, false, false);
        break;
    }
    case 2:
    {
        std::cout << "Surname: ";
        std::cin.ignore();
        std::getline(std::cin, aux, '\n');
        temp = search(aux, false, true, false);
        break;
    }
    case 3:
    {
        std::cout << "Email: ";
        std::cin.ignore();
        std::getline(std::cin, aux, '\n');
        temp = search(aux, false, false, true);
        break;
    }
    case 0:
        break;
    }
    return temp;
}

bool ContactBook::addContact(){
    try
    {
        Contact newContact = createContact();
        append(newContact);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

int ContactBook::toUpdate(){
    int op = -1;
    std::cout << "To update:\n";
    while(op < 0 || op > 4){
        std::cout << "1.Name\n";
        std::cout << "2.Surname\n";
        std::cout << "3.Email\n";
        std::cout << "4.Phone\n";
        std::cout << "0.Update\n";
        std::cout << " >> ";
        std::cin >> op;
    }
    return op;
}

void ContactBook::modifyContactValues(Contact &contact){
    bool updating = true;
    std::string aux;
    int num;
    while(updating){
        switch (toUpdate())
        {
        case 1:
        {
            std::cout << "Old value: " << contact.getName() << "\n";
            std::cout << "New value: ";
            std::cin.ignore();
            std::getline(std::cin, aux, '\n');
            contact.setName(aux);
            break;
        }
        case 2:
        {
            std::cout << "Old value: " << contact.getSurname() << "\n";
            std::cout << "New value: ";
            std::cin.ignore();
            std::getline(std::cin, aux, '\n');
            contact.setSurname(aux);
            break;
        }
        case 3:
        {
            std::cout << "Old value: " << contact.getEmail() << "\n";
            std::cout << "New value: ";
            std::cin.ignore();
            std::getline(std::cin, aux, '\n');
            contact.setEmail(aux);
            break;
        }
        case 4:
        {
            std::cout << "Old value: " << contact.getPhone() << "\n";
            std::cout << "New value: ";
            std::cin >> num;
            contact.setPhone(num);
            break;
        }
        case 0:
        {
            updating = false;
            break;
        }
        }
    }
}

bool ContactBook::updateContact(){
    //Search contact
    std::string name, surname;
    std::cout << "Contact to Modify\n";
    std::cout << "Name: ";
    std::cin >> name;
    std::cout <<"Surname: ";
    std::cin >> surname;
    int index = getContactIndex(name, surname);
    if(index == -1) {return false;} // Contact not found
    //Contact found
    Node<Contact> *temp = get(index);
    Contact contact(temp->value.getName(), temp->value.getSurname(), temp->value.getEmail(), temp->value.getPhone());
    modifyContactValues(contact);
    updateNode(contact, index);
    return true;
}