//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Bilgenur Çelik
//---Student Number: 150200063
//--------------------------//

#ifndef _structs
#define _structs

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//-------------Token Class To Store Character Info-------------//
class Token{
    public:
        string symbol;
        int val = 0;
};

//-------------Node Class for Priority Queue and Tree-------------//
class Node{
    public:
        Token token;
        Node *next;
        Node *left;
        Node *right;
};

//-------------Priority Queue Class-------------//
class PriorityQueue{
    public:
        Node *head;
        PriorityQueue();
        void enque(Node*);
        Node* dequeue();
};

//-------------Tree Class-------------//
class Tree{
    public:
        Node *root;
        Tree();
        ~Tree();
        void deleteTree(Node*);
        Node* mergeNodes(Node*, Node*);
        void printTree(Node*, int);
};

#endif
