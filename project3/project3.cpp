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
        CPUJob(); // Default constructor
        CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed, int memory_consumed); // Parameterized constructor
        ~CPUJob(); // Destructor
};

// Queue data structure (FiFo).
template <class DT>
class Queue {
    public:
        DT* JobPointer; // Pointer to a CPUJob
        Queue<DT>* next; // Pointer to the next node in the queue
};

// Class for storing and maintaining the CPUJob queue (FiFo).
template <class DT>
class NovelQueue {
    public:
        Queue<DT>* front; // Pointer to the front of the queue
        Queue<DT>** NodePtrs; // Array of queue node pointers
        int size; // Number of elements
        NovelQueue<DT>(); // Default constructor
        ~NovelQueue<DT>(); // Destructor
        void enqueue(CPUJob* newJob); // Method to add elements to the queue
        CPUJob* dequeue(); // Method to remove elements from the queue
        void modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed); // Method to modify the first CPUJob object in the queue
        void change(int job_id, int field_index, int new_value); // Change job values
        void promote(int job_id, int positions); // Change position of CPUJob within queue
        NovelQueue<DT>* reorder(int attribute_index); // Reorders the queue
        void display(); // Display method
        int count(); // Returns number of elements in queue
        void listJobs(); // Prints jobs within queue
};

// Main program for organizing and manipulating input for proper output.
int main() {
    int n; // Number of commands
    cin >> n; // Read in the number of commands

    NovelQueue<CPUJob*>* myNovelQueue = new NovelQueue<CPUJob*>(); // Instantiate a NovelQueue for CPUJob pointers

    char command; // Variable to store the command type

    // Job attribute declaration placeholders
    int job_id, priority, job_type, cpu_time_consumed, memory_consumed;

    // Job attribute modification placeholders
    int new_priority, new_job_type, new_cpu_time_consumed;
    int new_memory_consumed;
    int field_index, new_value;

    int positions; // Variable to store number of positions in the 'Promote' command
    int attribute_index; // Variable for the 'Reorder' command

    for (int i = 0; i < n; i++) {
        cin >> command; // Read in command type

        switch (command) {
            case 'A': {
                cin >> job_id >> priority >> job_type;
                cin >> cpu_time_consumed >> memory_consumed;
                // CPUJob* newJob = new CPUJob(job_id, priority, job_type, cpu_time_consumed, memory_consumed);
                // (*myNovelQueue).enqueue(newJob);
                break;
            }
            case 'R': {
                
            }
            case 'M': {
                
            }
            case 'C': {
                
            }
            case 'P': {
                
            }
            case 'O': {
                
            }
            case 'D': {
                
            }
            case 'N': {
                
            }
            case 'L': {
                
            }
            default:
                cout << "Invalid command" << endl;
        }
    }

    delete myNovelQueue; // Delete NovelQueue after program completion

    return 0; // End program
}
