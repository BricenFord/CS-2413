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
        int enqueue(CPUJob* newJob); // Method to add elements to the queue
        CPUJob* dequeue(); // Method to remove elements from the queue
        int modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed); // Method to modify the first CPUJob object in the queue
        int change(int job_id, int field_index, int new_value); // Change job values
        int promote(int job_id, int positions); // Move CPUJob higher in the queue based on the given positions value
        void reorder(int attribute_index); // Reorders the queue
        void display(); // Display method
        int count(); // Returns number of elements in queue
        void listJobs(); // Prints jobs within queue
        int binarySearch(int key); // Performs a binary search on the NodePtrs and returns the element of the key
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
int NovelQueue<DT>::enqueue(CPUJob* newJob) { // Enqueue method
    Queue<DT>** newArray = new Queue<DT>*[size + 1];  // Increase array size by 1
    for (int i = 0; i < size; i++) { // Copy over to newArray
        if (NodePtrs[i]->JobPointer->job_id == newJob->job_id) {
            return 0;
        }
        newArray[i] = NodePtrs[i];
    }
    newArray[size] = new Queue<DT>(newJob); // Put newJob into array
    if (size == 0) { // Verifying whether front should be pointing to newJob
        front = newArray[size];
    }
    else {
        newArray[size - 1]->next = newArray[size];
    }
    newArray[size]->next = nullptr;
    delete[] NodePtrs; // Delete old NodePtrs array
    NodePtrs = newArray; // Copy new array into NodePtrs
    size++; // Increment size
    return 1;
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
int NovelQueue<DT>::modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    // use binary search to find job id
    // change current information to new information
    int jobPos = binarySearch(job_id);
    NodePtrs[jobPos]->JobPointer = new CPUJob(job_id, new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed);
    return jobPos;
}
template <class DT>
int NovelQueue<DT>::change(int job_id, int field_index, int new_value) {
    int jobPos = binarySearch(job_id);
    if (jobPos == -1) {
        return -1;
    }
    switch (field_index) {
        case 1: {
            NodePtrs[jobPos]->JobPointer->priority = new_value;
            break;
        }
        case 2: {
            NodePtrs[jobPos]->JobPointer->job_type = new_value;
            break;
        }
        case 3: {
            NodePtrs[jobPos]->JobPointer->cpu_time_consumed = new_value;
            break;
        }
        case 4: {
            NodePtrs[jobPos]->JobPointer->memory_consumed = new_value;
            break;
        }
    }
    return jobPos;
}
template <class DT>
int NovelQueue<DT>::promote(int job_id, int positions) {
    // Find the job position using binary search
    int jobPos = binarySearch(job_id);
    int newPos = jobPos - positions;

    Queue<DT>** newArray = new Queue<DT>*[size];
    for (int i = 0, j = 0; i < size; i++, j++) {
        if (i == newPos) {
            if (i == 0) {
                front = NodePtrs[jobPos];
            }
            newArray[i] = NodePtrs[jobPos];
            i++;
        }
        if (j == jobPos) {
            j++;
        }
        newArray[i] = NodePtrs[j];
    }
    NodePtrs = newArray;
    return newPos;
}
template <class DT>
void NovelQueue<DT>::reorder(int attribute_index) {
    Queue<DT>** newArray = new Queue<DT>*[size];

    switch (attribute_index) {
        case 1: { // Sort by job_id
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->job_id < NodePtrs[index]->JobPointer->job_id) {
                        index = j;
                    }
                }
                // Swap
                newArray[i] = NodePtrs[index];
                if (i != index) {
                    Queue<DT>* temp = NodePtrs[i];
                    NodePtrs[i] = NodePtrs[index];
                    NodePtrs[index] = temp;
                }
            }
            break;
        }
        case 2: { // Sort by priority
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->priority < NodePtrs[index]->JobPointer->priority) {
                        index = j;
                    }
                }
                // Swap
                newArray[i] = NodePtrs[index];
                if (i != index) {
                    Queue<DT>* temp = NodePtrs[i];
                    NodePtrs[i] = NodePtrs[index];
                    NodePtrs[index] = temp;
                }
            }
            break;
        }
        case 3: { // Sort by job_type
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->job_type < NodePtrs[index]->JobPointer->job_type) {
                        index = j;
                    }
                }
                // Swap
                newArray[i] = NodePtrs[index];
                if (i != index) {
                    Queue<DT>* temp = NodePtrs[i];
                    NodePtrs[i] = NodePtrs[index];
                    NodePtrs[index] = temp;
                }
            }
            break;
        }
        case 4: { // Sort by cpu_time_consumed
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->cpu_time_consumed < NodePtrs[index]->JobPointer->cpu_time_consumed) {
                        index = j;
                    }
                }
                // Swap
                newArray[i] = NodePtrs[index];
                if (i != index) {
                    Queue<DT>* temp = NodePtrs[i];
                    NodePtrs[i] = NodePtrs[index];
                    NodePtrs[index] = temp;
                }
            }
            break;
        }
        case 5: { // Sort by memory_consumed
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->memory_consumed < NodePtrs[index]->JobPointer->memory_consumed) {
                        index = j;
                    }
                }
                // Swap
                newArray[i] = NodePtrs[index];
                if (i != index) {
                    Queue<DT>* temp = NodePtrs[i];
                    NodePtrs[i] = NodePtrs[index];
                    NodePtrs[index] = temp;
                }
            }
            break;
        }
    }

    // Reassign NodePtrs to the sorted array
    delete[] NodePtrs; // Free the old array
    NodePtrs = newArray;
}
template <class DT>
void NovelQueue<DT>::display() { // Increments through NodePtrs printing all nodes
    // if (size > -1) {
    //     NodePtrs[0]->JobPointer->display();
    // }
    // for (int i = 0; i < size - 1; i++) {
    //     NodePtrs[i]->next->JobPointer->display();
    // }
    for (int i = 0; i < size; i++) {
        NodePtrs[i]->JobPointer->display();
    }
}
template <class DT>
int NovelQueue<DT>::count() {
    return size;
}
template <class DT>
void NovelQueue<DT>::listJobs() {
    // to be implemented !!!
}
template <class DT>
int NovelQueue<DT>::binarySearch(int key) { // Performs a binary search on the NodePtrs and returns the element of the key
    int L = 0;
    int R = size - 1;
    while (L <= R) {
        int mid = (L+R) / 2;
        if (NodePtrs[mid]->JobPointer->job_id == key) {
            return mid;
        }
        if (NodePtrs[mid]->JobPointer->job_id < key) {
            L = mid + 1;
        }
        else {
            R = mid - 1;
        }
    }
    return -1;
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
                int jobsAdded = (*myNovelQueue).enqueue(newJob); // Adds this newJob to the queue
                if (jobsAdded < 1) {
                    cout << "Job ID " << newJob->job_id << " already exists!" << endl;
                    break;
                }
                cout << "Enqueued Job: " << endl;
                myNovelQueue->NodePtrs[((myNovelQueue->size) - 1)]->JobPointer->display(); // Prints enqueued job
                
                cout << "Jobs after enqueue:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break; // End case
            }
            case 'R': { // Command to remove a CPUJob from queue (dequeue)
                CPUJob* removedJob = (*myNovelQueue).dequeue(); // Create placeholder for dequeue'd job
                if (removedJob) { // Determines whether dequeue() returns anything
                    cout << "Dequeued Job: " << endl;
                    (*removedJob).display(); // Prints removedJob
                    delete removedJob; // Deletes removedJob to free up memory
                }
                cout << "Jobs after dequeue:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break; // End case
            }
            case 'M': {
                cin >> job_id >> priority >> job_type >> cpu_time_consumed >> memory_consumed; // Takes input to modify a CPUJob object
                int pos = myNovelQueue->modify(job_id, priority, job_type, cpu_time_consumed, memory_consumed);
                cout << "Modified Job ID " << job_id << ":" << endl;
                myNovelQueue->NodePtrs[pos]->JobPointer->display();
                cout << "Jobs after modification:" << endl;
                myNovelQueue->display();
                break;
            }
            case 'C': {
                cin >> job_id >> field_index >> new_value;
                int pos = myNovelQueue->change(job_id, field_index, new_value);
                if (pos == -1) {
                    cout << "Job with ID " << job_id << " not found in the queue." << endl;
                    break;
                }
                cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":" << endl;
                myNovelQueue->NodePtrs[pos]->JobPointer->display();
                cout << "Jobs after changing field:" << endl;
                myNovelQueue->display();
                break;
            }
            case 'P': {
                cin >> job_id >> positions;
                int pos = myNovelQueue->promote(job_id, positions);
                if (pos != -1) {
                    cout << "Promoted Job ID " << job_id << " by " << positions << " Position(s):" << endl;
                }
                else {}
                myNovelQueue->NodePtrs[pos]->JobPointer->display();
                cout << "Jobs after promotion:" << endl;
                myNovelQueue->display();
                break;
            }
            case 'O': {
                cin >> attribute_index;
                myNovelQueue->reorder(attribute_index);
                cout << "Reordered Queue by attribute " << attribute_index << ":" << endl;
                myNovelQueue->display();
                break;
            }
            case 'D': {
                cout << "Displaying all jobs in the queue:" << endl;
                myNovelQueue->display();
                break;
            }
            case 'N': {
                int size = myNovelQueue->count();
                cout << "Number of elements in the queue: " << size << endl;
                break;
            }
            case 'L': {
                myNovelQueue->reorder(1);
                cout << "List of jobs sorted by job IDs:" << endl;
                myNovelQueue->display();
                break;
            }
            default:
                cout << "Invalid command" << endl;
        }
    }

    // delete myNovelQueue; // Delete NovelQueue after program completion

    return 0; // End program
}
