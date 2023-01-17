//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Bilgenur Çelik
//---Student Number: 150200063
//--------------------------//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    //TODO
    head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    //TODO

    // if empty, assign as head
    if(head == NULL){
        head = newnode;
    }
    else{
        // hold two pointers and insert between them.
        Node* fp = head;
        Node* sp = NULL;

        // until new value is smaller or string ended,
        while(fp->token.val <= newnode->token.val){
            sp = fp;
            fp = fp->next;

            if(fp == NULL) break;
        }

        if(sp != NULL)
            sp->next = newnode;
        // if adding to head;
        else{
            sp = newnode;
            head = newnode;
        }

        newnode->next = fp;
    }
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    //TODO

    // remove from head.
    Node* p = head;
    head = head->next;
    p->next = NULL;

    // return the seperated node.
    return p;
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    //TODO
    root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    //TODO
    deleteTree(root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    // if leaf return.
    if(node == NULL) return;

    // delete recursively.
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    return;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    //TODO

    // create a new node to put concatenation of two nodes.
    Node* concat = new Node;
    concat->token.val = temp1->token.val + temp2->token.val;
    concat->token.symbol = temp1->token.symbol + temp2->token.symbol;

    concat->left = temp1; // smaller one on left:
    concat->right = temp2; // larger one on right:

    return concat;
};


void Tree::printTree(Node* traverse, int level){

    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);
    if(traverse->right)
        printTree(traverse->right, level + 1);
};
