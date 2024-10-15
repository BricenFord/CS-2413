/* 
Project Description:
This project's objective is to implement a novel templated queue data structure called NovelQueue in C++. 
This queue will simulate a CPU scheduling system, managing a collection of CPU jobs and their execution characteristics.
*/

#include <iostream>
#include <string>

using namespace std;

// Class for holding each individual CPU task.
class CPUJob {
    public:
        int job_id; // Unique identifier for the job
        int priority; // Priority level of the job (1-10)
        int job_type; // Job type (1-10)
        int cpu_time_consumed; // Total memory consumed
};

// Queue data structure (FiFo).
template <class DT>
class Queue {
    public:
        DT* JobPointer; // Pointer to a CPUJob
        Queue<DT>* next; // Pointer to the next node in the queue
};

// Class for storing and maintaining the CPUJob queue.
template <class DT>
class NovelQueue {
    public:
        Queue<DT>* front; // Pointer to the front of the queue
        Queue<DT>** NodePtrs; // Array of queue node pointers
        int size; // Number of elements
};

// Main program for organizing and manipulating input for proper output.
int main() {

    return 0; // End program
}
