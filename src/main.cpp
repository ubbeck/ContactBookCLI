#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include "ContactBook.h"


const std::string DB = "db.txt";

int menu();

int main(){
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    ContactBook cb;
    cb.loadData(DB);

    bool active = true;
    while(active){
        switch (menu())
        {
        case 1:
        {
            if(cb.addContact()) {std::cout << "Contact added successfully\n";}
            else {std::cout << "Error adding new contact\n";}
            std::cout << std::endl;
            break;
        }
        case 2:
        {   
            int op = cb.searchType();
            Node<Contact> *result = cb.userInputToSearch(op);
            Node<Contact>::printNode(result);
            Node<Contact>::deleteNode(result);
            std::cout << std::endl;
            break;
        }
        case 3:
        {
            char letter = ' ';
            std::cout << "Letter: ";
            std::cin >> letter;
            Node<Contact> *result = cb.filterByLetter(letter, true, false);
            Node<Contact>::printNode(result);
            Node<Contact>::deleteNode(result);
            std::cout << std::endl;
            break;
        }
        case 4:
            if(cb.updateContact()) {std::cout << "DONE\n";}
            else {std::cout << "Contact not updated\n";}
            std::cout << std::endl;
            break;
        case 5:
            cb.printList();
            std::cout << "Contacts: " << cb.numberContacts() << "\n";
            std::cout << std::endl;
            break;
        case 6:
        {
            std::string f = "";
            std::cout << "File name: ";
            std::cin >> f;
            f = f + ".txt";
            cb.removeDuplicates();
            cb.writeData(f);
            std::cout << "DONE\n";
            std::cout << std::endl;
            break;
        }
        case 7:
        {
            std::string name, surname;
            std::cout << "Contact to Modify\n";
            std::cout << "Name: ";
            std::cin.ignore();
            std::getline(std::cin, name, '\n');
            std::cout <<"Surname: ";
            std::cin >> surname;
            int index = cb.getContactIndex(name, surname);
            cb.deleteNode(index);
            std::cout << "DONE\n";
            std::cout << std::endl;
            break;
        }
        case 8:
        {   
            cb.clear();
            std::cout << "List deleted\n";
            std::cout << std::endl;
            break;
        }
        case 0:
            std::cout << "Exit\n";
            active = false;
            break;
        }
    }
    return 0;
}

int menu(){
    int op = -1;
    do{
        std::cout << "**** MENU ****\n";
        std::cout << "1. Add\n";
        std::cout << "2. Search\n";
        std::cout << "3. Filter\n";
        std::cout << "4. Update\n";
        std::cout << "5. Print List\n";
        std::cout << "6. Export\n";
        std::cout << "7. Delete\n";
        std::cout << "8. Delete List\n";
        std::cout << "0. Exit\n";
        std::cout << " >> ";
        std::cin >> op;
    }while(op < 0 || op > 8);
    return op;
}