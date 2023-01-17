/* @Author
Student Name: Bilgenur Çelik
Student ID : 150200063
Date: 26/10/2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    this->mpHead = head;
    this->mpTail = this->mpHead;
}


FIFORep::~FIFORep()
{
    ProcessRep* temp = getHead();
    while(temp!=NULL){
        ProcessRep* temp2 = temp;
        temp = temp->getNext();
        temp2->setNext(NULL);
        delete temp2;
    }
}

void FIFORep::setHead(ProcessRep* head)
{
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    this->mpTail = tail;
    //this->mpTail->setNext(NULL); xxxx
}

ProcessRep* FIFORep::getTail()
{
    return this->mpTail;
}


// The function add a process to the tail of the queue.
void FIFORep::queue(ProcessRep* p)
{
    if (getHead() == NULL){
        setHead(p);
        setTail(p);
    }
    else {
        this->mpTail->setNext(p);
        setTail(p);
        getTail()->setNext(NULL);
    }
}


// The function remove a process from the tail of the queue and returns it.
ProcessRep* FIFORep::dequeue()
{
      ProcessRep* temp = getHead();
    // if we are sure that there is only one element
    if (getHead() == getTail()) {
        setHead(NULL);
        setTail(NULL);
        return temp;
    }

    setHead(this->mpHead->getNext());
    return temp;
}

//The function search a process by id and returns it if it exist otherwise returns NULL.
ProcessRep* FIFORep::searchID(int id)
{
    ProcessRep* ptr = this->getHead(); // heaad can be null but unimportant and handeled here
    while ((ptr != NULL) && (ptr->getProcessID() != id))
        ptr = ptr->getNext();

    return ptr;
}


void FIFORep::printFIFO()
{
    // head to taiiil
    ProcessRep* ptr = getHead();

    if (ptr == NULL){
        return;
    }

    while (ptr != getTail()){
        cout << ptr->getProcessType() << ptr->getProcessID() << " " << ptr->startTime << " " << ptr->endTime << " ";
        ptr = ptr->getNext();
    }
    cout << ptr->getProcessType() << ptr->getProcessID() << " " << ptr->startTime << " " << ptr->endTime << " ";

    /*
    while (ptr != NULL){
        cout << ptr->getProcessType() << ptr->getProcessID() << " " << ptr->startTime << " " << ptr->endTime << " ";
        ptr = ptr->getNext();
    }*/
}
