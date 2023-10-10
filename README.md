## Project Overview

Small command line project to practice the implementation and application of the Linked List data structure in C++ language. Some programming techniques included:

- **Linked Lists**: Implementation of a generic linked list data structure from scratch

- **Object-Oriented Programming (OOP)**: Applying OOP principles to create structured and modular code

- **Generic programming**: using C++ templates, generic linked list implementation

- **Dynamic Memory Management**: Learning about memory allocation and deallocation

- **Operator Overloading**: Overloading operators for custom types

- **Data Persistence**: Implementing data persistence by reading and writing contact information to an external file, allowing to store and retrieve contacts between sessions.  

## Possible updates
- Replace external files with database
- Unit tests

## Build

The project has been developed in **VSCode** using the **MSVC** compiler.  
  
It has also been tested with the **MinGW** compiler version 12.2.0  
```bash
g++ -g -std=c++20 main.cpp -o main.exe
```  
The file `tracking_memory.h`, used to detect memory leaks, can be removed from the include headers if MSVC is not used.