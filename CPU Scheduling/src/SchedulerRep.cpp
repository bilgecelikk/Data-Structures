/* @Author
Student Name: Bilgenur Çelik
Student ID : 150200063
Date: 26/10/2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    // privates:

    // arrange space for fiforep of three schedule:
    for(int i=0; i<3; i++){
        FIFORep* temp = new FIFORep();
        setProcessFIFO(temp, i);
    }


    this->mpRunningProcess = NULL;

    // publics:
    totalTime = 0;
    timeSliceCount = 0; // to 2 to 4 to 8 for different options
    pCpuObj = new CPURep();
}
SchedulerRep::~SchedulerRep()
{
    for(int i=0; i<3; i++){
        delete getProcessFIFO(i);
    }
    delete pCpuObj;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return this->mpProcessFIFO[index];
}

// use for initialization only
void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this->mpProcessFIFO[index] = fifo;
}


void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    if (p != NULL){
        // initialization of startTime of new process.
        if (p->startTime == -1)
            p->startTime = this->totalTime;
    }

    this->timeSliceCount = 0;
    this->mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    if (p == NULL)
        return;

    // add to whichever fifo
    string which_one = p->getProcessType();

    if (which_one == "A"){
        mpProcessFIFO[0]->queue(p);
    }
    else if (which_one == "B"){
        mpProcessFIFO[1]->queue(p);
    }
    else if (which_one == "C"){
        mpProcessFIFO[2]->queue(p);
    }
}

ProcessRep* SchedulerRep::popProcess()
{
    // return the dequed process, starting from A
    if (mpProcessFIFO[0]->getHead() != NULL){
        return mpProcessFIFO[0]->dequeue();
    }
    else if (mpProcessFIFO[1]->getHead() != NULL){
        return mpProcessFIFO[1]->dequeue();
    }
    else if (mpProcessFIFO[2]->getHead() != NULL){
        return mpProcessFIFO[2]->dequeue();
    }
    // otherwise null
    return NULL;
}

// if over the wanted timeslice return true, else false with this func
bool SchedulerRep::checkTimeSlice()
{
    if (getRunningProcess() == NULL)
        return false;

    string temp = getRunningProcess()->getProcessType();

    // for every level quantum was 2^n thus 2 4 and 8 are breakpoints for process.
    // we should put it back to its corresponding fifo if that breakpoint is reached.
    if (temp == "A") {
        if (timeSliceCount == 2) // eşitlik iş görür zaten aşmaya hiç izin vermemeli
            return true;
    }

    else if (temp == "B"){
        if (timeSliceCount == 4)
            return true;
    }

    else if (temp == "C") {
        if (timeSliceCount == 8)
            return true;
    }

    return false;
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
    // do one run in cpu
    return this->pCpuObj->runCPU(p, totalTime);
    // if the return here is a ProcessRep pointer it means its remaining time ended (keep it in mind!!)
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{
    //allocate memory for newly created process, and send it to schedule to do necessary handlement
    ProcessRep* add_process = new ProcessRep(type, id, arrivalTime, processTime);
    schedule(add_process);

}

// now, we can use null or newly created ProcessRep* p value.
void SchedulerRep::schedule(ProcessRep* p)
{
    // first of all we should send new process to its fifo anyways,
    if (p != NULL) {
        pushProcess(p);
    }

    //if there is no running process:
    if (getRunningProcess() == NULL) {
        // if fifo's contain any element to proceed, pop and send it to running process.
        setRunningProcess(popProcess());
    }

    // if breakpoint is reached,
    if (checkTimeSlice()) {
        // push it to its fifo
        pushProcess(getRunningProcess());
        // if we can pop and full the empty running process place, pop and get one pointer with popProcess()
        setRunningProcess(popProcess());
    }

    // now lets compare new proces with currently running one:
    if(p != NULL && getRunningProcess() != NULL){
        // change the running if new one is preffered
        if (getRunningProcess()->getProcessType() > p->getProcessType()) {
            pushProcess(getRunningProcess());
            setRunningProcess(popProcess()); // pop from fifos and of top priority new process will be achieved already.
        }
    }

    // increase both of them by one.
    totalTime++;
    timeSliceCount++;

    // finally send it to cpu if not empty and do one run. remaining time decreased.
    // if remaining time ended to not leaving running process empty get -if you can- a process from fifos.
    if (sendProcessToCPU(getRunningProcess()) != NULL) {
        setRunningProcess(popProcess());
    }
}
