//============================================================================
// Name        : HW2.cpp
// Author      : Candas Nasif
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "header.h"
using namespace std;

int main(int argc, char* argv[])
{
    string input = argv[1];
    string output = argv[2];
    create_LinkedList(input, output);
    return 0;
}
