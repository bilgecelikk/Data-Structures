//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Bilgenur Çelik
//---Student Number: 150200063
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-----------Reads the key from text file--------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};

//---------Sorts the key in an alpabetic order---------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};


//-------Finds the frequency of the characters---------//
void Huffman::findFrequency(){

    sortKey();

    // with two pointers find how many of each character there are.
    // i : start    j : end
    int i = 0, j = 0;
    int size = sortedKey.size();

    while(1){
        j++;
        if(j == size || sortedKey[j] != sortedKey[i]){
            Node* created = new Node;

            created->token.symbol = sortedKey[i];
            created->token.val = j-i;       // val means how many of same char.
            created->next = NULL;           // init.

            //cout << created->token.symbol << " " << created->token.val << endl;

            // send the created node into the queue
            queue.enque(created);

            i = j; // reassign i.

            // break if end of string.
            if(j==size)
                break;
        }
    }
};
//-----------------------------------------------------//

/*
// This function was helpful to verify that queue is set perfectly.
void printqueue(Node* temp){
    while(temp!=NULL){
        cout << temp->token.symbol<< "  " << temp->token.val;
        temp = temp->next;
    }
}
*/
//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
void Huffman::createHuffmanTree(){

    findFrequency();

    while(queue.head->next != NULL){
        //printqueue(queue.head);

        // firstly take the first two nodes in pq.
        Node* temp1 = queue.dequeue();
        Node* temp2 = queue.dequeue();

        Node* con = huffmanTree.mergeNodes(temp1, temp2);

        // merge them and send to pq, untill there is one node.
        queue.enque(con);
    }
    // Now queue has only one node. This node contains
    // all the other nodes in its left or right, thus head to out tree.
    huffmanTree.root = queue.dequeue();

    // queue is emptied.
};
//-----------------------------------------------------//


//---------------Prints the Huffman Tree---------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};


/* This helper backtrack function recursively creates the temp string.
temp string is returning after reaching to a leaf.
Thus, temp contains a binary way to reach that leaf. */
void backtrack(char tokenChar, Node* traverse, string &tokenBinary, string temp = ""){
    if(traverse == NULL)
        return;
    // if it is a leaf node and it's char is the wanted char.
    else if(traverse->left == NULL && traverse->right == NULL && (traverse->token.symbol)[0] == tokenChar)
        tokenBinary = temp; // Requested string is set to tokenBinary.

    // traverse both to the left and to the right.
    backtrack(tokenChar, traverse->left, tokenBinary,  temp + "0");
    backtrack(tokenChar, traverse->right, tokenBinary, temp + "1");
}
//-------------Finds and returns the binary------------//
//---value to given character with backtrack()s help---//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary = ""){
    //TODO
    backtrack(tokenChar, traverse, tokenBinary);
    return tokenBinary;
};
//-----------------------------------------------------//



//--------------Encodes the given password-------------//
void Huffman::encodePassword(string password){
    //TODO

    // Initialize before change.
    encodedBinaryPassword = "";
    encodedValPassword= "";

    // for every character traverse the tree. Find a string of that binary way.
    for(char c : password){
        string bin = getTokenBinary(c, huffmanTree.root);

        // add the binary way to encodedBinaryPassword
        encodedBinaryPassword += bin;
        // add the char value of the way's size, which is the depth, to encodedValPassword.
        encodedValPassword += (bin.size() + '0');
    }
};



//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO
    decodedPassword = "";
    int j = 0;
    int size = encodedValPassword.size();
    for (int i = 0; i < size; i++) {
        // Every time take encodedValPassword[i] times encodedBinaryPassword substring.
        int value = int(encodedValPassword[i] - '0');
        string encoded_token = encodedBinaryPassword.substr(j, value);

        // send the substing to decode.
        decodeToken(encoded_token);

        j += value;
    }
    /* Example:
        11111   0000    ...01101110101011110000011000101111011100101110000
        5       4       ...53544354455
    */
};



//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
void Huffman::decodeToken(string encodedToken){
    // Now, we will traverse as the given substring encodedToken:
    Node* traverse = huffmanTree.root;

    for(char c : encodedToken){
        if(c == '1')
            traverse = traverse->right;
        else
            traverse = traverse->left;
    }

    // add the found string
    decodedPassword += traverse->token.symbol;
};



//-------------Prints the decoded password-------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};
