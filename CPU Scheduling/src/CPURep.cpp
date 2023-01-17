/* @Author
Student Name: Bilgenur Çelik
Student ID : 150200063
Date: 26/10/2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    // open space for finished process fiforep:
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    delete getFinishedProcess();
}



/*It execute the process by subtracting one from remainingTime. If process finishes, it add
to mFinishedProcess.*/
ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{

    // if ProcessRep came as NULL
    if(p == NULL)
        return NULL;

    // else
    // decrease rem.time
    p->remainingTime--;
    if (p->remainingTime == 0){ // if process is finished.
        p->endTime = time; // set the endtime
        getFinishedProcess()->queue(p);
        return p; // return finished processrep* for later usage.
    }

    // if process is not finished:
    return NULL;
}


FIFORep* CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    this->mFinishedProcess = finishedProcess;
}
