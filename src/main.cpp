#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include "ContactBook.h"


const std::string DB = "db.txt";

int main(){
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ContactBook cb;

    cb.loadData("db.txt");

    cb.printList();

    cb.deleteNode(24);

    cb.printList();

    return 0;
}