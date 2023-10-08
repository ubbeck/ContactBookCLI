#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "LinkedList.h"

#include <fstream>

const std::string DB = "db.txt";

int main(){
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    LinkedList<Contact> myList;

    myList.loadData(DB);

    myList.printList();

    return 0;
}