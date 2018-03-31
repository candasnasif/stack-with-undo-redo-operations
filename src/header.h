/*
 * header.h
 *
 *  Created on: 12 Kas 2015
 *      Author: Candas
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <sstream>
using namespace std;
#ifndef HEADER_H_
#define HEADER_H_

class Stack {
    string ar[100]; // type of data in stack
    int n; // number of elements in stack

public:
    Stack();
    void push(string);
    void pop();
    string top();
    bool empty();
    bool full();
    int size();
};

/********************************/
Stack::Stack()
{
    n = 0; // says no elements in array
}
/********************************/
string Stack::top()
{
    return ar[n];
}
bool Stack::empty()
{
    return (n == 0); // evaluates ==0 for true and != 0 for false
}
/********************************/
bool Stack::full()
{
    return (n == 100); // or use symbolic constant
}
/********************************/
void Stack::push(string c)
{
    if (n == 100)
        return; // stack is full
    // insert onto stack
    ar[n + 1] = c; // or optional ar[n++] = c
    n++;
}
/*********************************/
void Stack::pop()
{
    if (empty())
        return;
    n--;
}

struct LinkedList {

    int link;
    char* data;
    char* type;
};
string Convert(double x)
{
    std::ostringstream strs;
    strs << x;
    std::string sonuc = strs.str();
    return sonuc;
}
int Count_Line()
{
    string line;
    int count = 0;
    string file_name = "candas.txt";
    ifstream myfile("example.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            count++;
        }
        myfile.close();
    }
    return 2 * count;
}
char* Convert_Char(string x)
{
    char* y = new char[x.length() + 1];
    strcpy(y, x.c_str());
    return y;
}
char* type(char* data)
{
    if (string(data).find("\"") != std::string::npos) {
        return Convert_Char("STRING");
    }
    else if (string(data).find(".") != std::string::npos) {
        return Convert_Char("DOUBLE");
    }

    else
        return Convert_Char("INTEGER");
}
char* str_split(string line)
{

    string second = line.substr(4);
    char* final = new char[second.length() + 1];
    strcpy(final, second.c_str());
    return final;
}

string ADD(LinkedList list[], int head)
{
    string newelement;
    if (list[head].type == "INTEGER"
        && list[list[head].link].type == "DOUBLE") {
        newelement = Convert(
            atoi(list[head].data) + atof(list[list[head].link].data));
    }
    else if (list[head].type == "DOUBLE"
        && list[list[head].link].type == "INTEGER") {
        newelement = Convert(
            atof(list[head].data) + atoi(list[list[head].link].data));
    }
    else if (list[head].type == "INTEGER"
        && list[list[head].link].type == "INTEGER") {
        newelement = Convert(
            atoi(list[head].data) + atoi(list[list[head].link].data));
    }
    else if (list[head].type == "STRING"
        && list[list[head].link].type == "INTEGER") {
        newelement = string(list[head].data)
            + string(list[list[head].link].data);
        newelement = "\"" + newelement + "\"";
    }
    else if (list[head].type == "STRING"
        && list[list[head].link].type == "DOUBLE") {
        newelement = string(list[head].data)
            + string(list[list[head].link].data);
        newelement = "\"" + newelement + "\"";
    }
    else if (list[head].type == "STRING"
        && list[list[head].link].type == "INTEGER") {
        newelement = string(list[head].data)
            + string(list[list[head].link].data);
        newelement = "\"" + newelement + "\"";
    }
    else if (list[head].type == "DOUBLE"
        && list[list[head].link].type == "STRING") {
        newelement = string(list[head].data)
            + string(list[list[head].link].data);
        newelement = "\"" + newelement + "\"";
    }
    else if (list[head].type == "INTEGER"
        && list[list[head].link].type == "STRING") {
        newelement = string(list[head].data)
            + string(list[list[head].link].data);
        newelement = "\"" + newelement + "\"";
    }
    else if (list[head].type == "STRING"
        && list[list[head].link].type == "STRING") {
        newelement = string(list[head].data)
            + string(list[list[head].link].data);
        newelement = "\"" + newelement + "\"";
    }
    return newelement;
}
int PUT(LinkedList list[], char* data, char* type, int head)
{

    list[head + 1].data = data;
    list[head + 1].link = head + 2;
    list[head + 1].type = type;
    head = head + 1;

    return head;
}
int PUT_UNDO(LinkedList list[], int head)
{
    head = head - 1;
    return head;
}
int PUT_REDO(LinkedList list[], int head)
{
    head = head + 1;
    ;
    return head;
}

int DELETE_UNDO(LinkedList list[], int rear)
{
    rear = rear - 1;
    return rear;
}
int DELETE_REDO(LinkedList list[], int rear)
{
    rear = rear + 1;
    return rear;
}
int DELETE(LinkedList list[], int rear)
{
    if (list[rear].data != "candas") {
        rear = list[rear].link;
    }
    return rear;
}

void PRINT(LinkedList list[], int head, int rear, std::ostream& output)
{
    int i = rear;
    while (i < head + 1) {
        output << list[i].data;
        i = i + 1;
    }
    output << "\n";
}
int character(string x)
{
    char* charx = Convert_Char(x);
    int i = 0;
    int result = 0;
    for (i = 0; i < x.size(); i++) {
        if (isalpha(charx[i]))
            result = 1;
    }
    return result;
}
void Operations(LinkedList list[], string input_file, string output_file)
{

    int head = 4;
    int rear = 5;
    Stack undo;
    Stack redo;
    Stack redo_undo;
    string line;
    ofstream output;
    output.open(Convert_Char(output_file), ios::out | ios::trunc);
    ifstream myfile(Convert_Char(input_file));
    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            if (line.find("PUT") != std::string::npos) {
                if (type(str_split(line)) == "STRING") {
                    string input = string(str_split(line)).substr(1, string(str_split(line)).size() - 2);
                    char* input_char = new char[input.length() + 1];
                    strcpy(input_char, input.c_str());
                    head = PUT(list, input_char, type(str_split(line)), head);
                    output << "A STRING ADDED TO COLLECTION\n";
                    undo.push(line);
                }
                else if (character(str_split(line)) == 1) {
                    output << "UNKNOWN COMMAND OR DATA TYPE\n";
                }
                else {
                    head = PUT(list, str_split(line), type(str_split(line)),
                        head);
                    if (type(str_split(line)) == "INTEGER")
                        output << "AN " << type(str_split(line))
                               << " ADDED TO COLLECTION\n";
                    else
                        output << "A " << type(str_split(line))
                               << " ADDED TO COLLECTION\n";
                    undo.push(line);
                }
            }

            else if (line == "DELETE") {
                if (list[rear].data != "candas") {
                    output << "A " << list[rear].type << " DELETED\n";
                    rear = DELETE(list, rear);
                    undo.push(line);
                }
                else
                    output << "DELETION IGNORED";
            }
            else if (line == "ADD") {
                if (list[rear].data != "candas"
                    && list[rear + 1].data != "candas") {
                    string newelement = ADD(list, rear);
                    char* element_type = type(Convert_Char(newelement));
                    char* element;
                    if (newelement.find("\"") != std::string::npos) {
                        element = Convert_Char(
                            newelement.substr(1, newelement.size() - 2));
                    }
                    else
                        element = Convert_Char(newelement);
                    head = PUT(list, element, element_type, head);

                    if (list[rear].type == "INTEGER")
                        output << "AN " << list[rear].type << " ADDED TO A"
                               << list[rear + 1].type << " AND NEW "
                               << element_type << " PUT END OF COLLECTION\n";
                    else if (list[rear + 1].type == "INTEGER")
                        output << "A " << list[rear].type << " ADDED TO AN "
                               << list[rear + 1].type << " AND NEW "
                               << element_type << " PUT END OF COLLECTION\n";
                    else if (list[rear].type == "INTEGER"
                        && list[rear + 1].type == "INTEGER")
                        output << "AN " << list[rear].type << " ADDED TO AN"
                               << list[rear + 1].type
                               << " AND NEW INTEGER PUT END OF COLLECTION\n";
                    else {
                        output << "A " << list[rear].type << " ADDED TO A"
                               << list[rear + 1].type
                               << " AND NEW STRING PUT END OF COLLECTION\n";
                    }
                    rear = rear + 2;
                    undo.push(line);
                }
                else
                    output << "ADDITION IGNORED\n";
            }
            else if (line == "PRINT") {
                PRINT(list, head, rear, output);
            }
            else if (line == "UNDO") {
                if (!undo.empty()) {
                    if (undo.top().find("PUT") != std::string::npos) {
                        head = PUT_UNDO(list, head);
                        redo.push(undo.top());

                        if (undo.top().find("REDO") != std::string::npos) {
                            output << "REDO REVERSED\n";
                        }
                        else
                            output << "PUTTING REVERSED\n";
                        undo.pop();
                    }
                    else if (undo.top().find("DELETE") != std::string::npos) {
                        rear = DELETE_UNDO(list, rear);
                        redo.push(undo.top());

                        if (undo.top().find("REDO") != std::string::npos) {
                            output << "REDO REVERSED\n";
                        }
                        else
                            output << "DELETION REVERSED\n";
                        undo.pop();
                    }
                    else if (undo.top().find("ADD") != std::string::npos) {
                        head = head - 1;
                        rear = rear - 2;
                        redo.push(undo.top());

                        if (undo.top().find("REDO") != std::string::npos) {
                            output << "REDO REVERSED\n";
                        }
                        else
                            output << "ADDITION REVERSED\n";
                        undo.pop();
                    }
                }
            }
            else if (line == "REDO") {
                if (!redo.empty() && (redo_undo.top() == "UNDO" || redo_undo.top() == "REDO")) {
                    if (redo.top().find("PUT") != std::string::npos) {
                        head = PUT_REDO(list, head);
                        undo.push("REDO" + redo.top());
                        redo.pop();
                        output << "UNDO REVERSED\n";
                    }
                    else if (redo.top() == "DELETE") {
                        rear = DELETE_REDO(list, rear);
                        undo.push("REDO" + redo.top());
                        redo.pop();
                        output << "UNDO REVERSED\n";
                    }
                    else if (redo.top() == "ADD") {
                        output << "UNDO REVERSED\n";
                        head = head + 1;
                        rear = rear + 2;
                        undo.push("REDO" + redo.top());
                        redo.pop();
                    }
                }
                else
                    output << "REDO IGNORED\n";
            }
            if (line != "PRINT")
                redo_undo.push(line);
        }
        output.close();
        myfile.close();
    }
}

void create_LinkedList(string input, string output)
{
    LinkedList list[Count_Line()];
    int i;
    for (i = 0; i < Count_Line(); i++) {
        list[i].link = i + 1;
        list[i].data = Convert_Char("candas");
    }
    Operations(list, input, output);
}

#endif /* HEADER_H_ */
