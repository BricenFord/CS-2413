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
        int cpu_time_consumed; // CPU time consumed from performing job
        int memory_consumed; // Total memory consumed (from job)
        CPUJob(); // Default constructor
        CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed, int memory_consumed); // Parameterized constructor
        CPUJob(CPUJob& copy); // Copy constructor
        ~CPUJob(); // Destructor
        void display(); // Display method
};
CPUJob::CPUJob() {} // Default constructor
CPUJob::CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed, int memory_consumed) { // Parameterized constructor
    (*this).job_id = job_id;
    (*this).priority = priority;
    (*this).job_type = job_type;
    (*this).cpu_time_consumed = cpu_time_consumed;
    (*this).memory_consumed = memory_consumed;
}
CPUJob::CPUJob(CPUJob& copy) { // Copy constructor
    (*this).job_id = copy.job_id;
    (*this).priority = copy.priority;
    (*this).job_type = copy.job_type;
    (*this).cpu_time_consumed = copy.cpu_time_consumed;
    (*this).memory_consumed = copy.memory_consumed;
}
CPUJob::~CPUJob() {} // Destructor
void CPUJob::display() { // Display method
    cout << "Job ID: " << job_id << ", Priority: " << priority << ", Job Type: " << job_type << ", CPU Time Consumed: " << cpu_time_consumed << ", Memory Consumed: " << memory_consumed << endl;
}

// Queue data structure (FiFo).
template <class DT>
class Queue {
    public:
        DT JobPointer; // Pointer to a CPUJob
        Queue<DT>* next; // Pointer to the next node in the queue
        Queue(){} // Default constructor
        Queue(DT CPUJob); // Create a new queue object with a CPUJob object
};

template <class DT>
Queue<DT>::Queue(DT CPUJob) { // Create a new queue object with a given CPUJob object
    JobPointer = CPUJob;
}

// Class for storing and maintaining the CPUJob queue (FiFo).
template <class DT>
class NovelQueue {
    public:
        Queue<DT>* front; // Pointer to the front of the queue
        Queue<DT>** NodePtrs; // Array of queue node pointers
        int size; // Number of elements
        NovelQueue(); // Default constructor
        ~NovelQueue(); // Destructor
        void enqueue(CPUJob* newJob); // Method to add elements to the queue
        CPUJob* dequeue(); // Method to remove elements from the queue
        void modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed); // Method to modify the first CPUJob object in the queue
        void change(int job_id, int field_index, int new_value); // Change job values
        void promote(int job_id, int positions); // Move CPUJob higher in the queue based on the given positions value
        NovelQueue<DT>* reorder(int attribute_index); // Reorders the queue
        void display(); // Display method
        int count(); // Returns number of elements in queue
        void listJobs(); // Prints jobs within queue
};
template <class DT>
NovelQueue<DT>::NovelQueue() { // Default constructor
    front = new Queue<DT>();
    size = 0; // initialized at 0, as queue starts empty
    NodePtrs = new Queue<DT>*[size];
}
template <class DT>
NovelQueue<DT>::~NovelQueue() { // Destructor
    delete front;
    for (int i = 0; i < size; i++) {
        delete NodePtrs[i];
    }
    delete[] NodePtrs;
}
template <class DT>
void NovelQueue<DT>::enqueue(CPUJob* newJob) { // Enqueue method

    Queue<DT>** newArray = new Queue<DT>*[size + 1];  // Increase array size by 1
    for (int i = 0; i < size; i++) { // Copy over to newArray
        newArray[i] = NodePtrs[i];
    }
    newArray[size] = new Queue<DT>(newJob); // Put newJob into array
    if (size == 0) { // Verifying whether front should be pointing to newJob
        front = newArray[size];
    }
    delete[] NodePtrs; // Delete old NodePtrs array
    NodePtrs = newArray; // Copy new array into NodePtrs
    size++; // Increment size
}   
template <class DT>
CPUJob* NovelQueue<DT>::dequeue() { // Dequeue method
    if (size == 0) // There is nothing to dequeue
        return NULL;
    CPUJob* result = (*front).JobPointer; // Front element is going to be dequeued

    for (int i = 0; i < size - 1; i++) { // Move every element in array to the left one
        NodePtrs[i] = NodePtrs[i + 1];
    }
    size--; // Decrement size
    if (size > 0) { // Checking to see if there is any elements to make front point to
        front = NodePtrs[0];
    } else { // If there is no elements, front = NULL
        front = NULL;
    }
    return result; // Return resulting dequeued element
}
template <class DT>
void NovelQueue<DT>::modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    // to be implemented !!!
}
template <class DT>
void NovelQueue<DT>::change(int job_id, int field_index, int new_value) {
    // to be implemented !!!
}
template <class DT>
void NovelQueue<DT>::promote(int job_id, int positions) {
    // to be implemented !!!
}
template <class DT>
NovelQueue<DT>* NovelQueue<DT>::reorder(int attribute_index) {
    // to be implemented !!!
}
template <class DT>
void NovelQueue<DT>::display() { // Increments through NodePtrs printing all nodes
    for (int i = 0; i < size; i++) {
        NodePtrs[i]->JobPointer->display();
    }
}
template <class DT>
int NovelQueue<DT>::count() {
    // to be implemented !!!
}
template <class DT>
void NovelQueue<DT>::listJobs() {
    // to be implemented !!!
}

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

        // Here we are parsing through the commands to determine which one should be performed based on the command type
        switch (command) {
            case 'A': { // Command to add a new CPUJob to queue (enqueue)
                cin >> job_id >> priority >> job_type >> cpu_time_consumed >> memory_consumed; // Takes input to initialize new CPUJob object
                CPUJob* newJob = new CPUJob(job_id, priority, job_type, cpu_time_consumed, memory_consumed); // Creates new CPUJob object from input
                (*myNovelQueue).enqueue(newJob); // Adds this newJob to the queue
                cout << "Enqueued Job:" << endl;
                myNovelQueue->NodePtrs[((myNovelQueue->size) - 1)]->JobPointer->display(); // Prints enqueued job
                
                cout << "Jobs after enqueue:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break; // End case
            }
            case 'R': { // Command to remove a CPUJob from queue (dequeue)
                CPUJob* removedJob = (*myNovelQueue).dequeue(); // Create placeholder for dequeue'd job
                if (removedJob) { // Determines whether dequeue() returns anything
                    cout << "Dequeued Job:" << endl;
                    (*removedJob).display(); // Prints removedJob
                    delete removedJob; // Deletes removedJob to free up memory
                }
                cout << "Jobs after dequeue:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break; // End case
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

    // delete myNovelQueue; // Delete NovelQueue after program completion

    return 0; // End program
}
