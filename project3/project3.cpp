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
        int incrementalSearch(int key); // Performs an incremental search on the NodePtrs and returns the element of the key
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
    delete[] NodePtrs;
}
template <class DT>
int NovelQueue<DT>::enqueue(CPUJob* newJob) { // Enqueue method
    Queue<DT>** newArray = new Queue<DT>*[size + 1];  // Increase array size by 1
    for (int i = 0; i < size; i++) { // Copy over to newArray
        if (NodePtrs[i]->JobPointer->job_id == newJob->job_id) { // Check to see if newJob is already within NodePtrs
            return -1; // Return -1 so that we can show job is already within queue
        }
        newArray[i] = NodePtrs[i];
    }
    newArray[size] = new Queue<DT>(newJob); // Put newJob into array
    if (size == 0) { // Verifying whether front should be pointing to newJob
        front = newArray[size];
    }
    else { // If it doesn't go at the front then just put it at the end of queue
        newArray[size - 1]->next = newArray[size];
    }
    newArray[size]->next = nullptr; // Set the very end to nullptr
    delete[] NodePtrs; // Delete old NodePtrs array
    NodePtrs = newArray; // Copy new array into NodePtrs
    size++; // Increment size
    return 1; // Return number of nodes enqueued (you can only enqueue one at a time)
}   
template <class DT>
CPUJob* NovelQueue<DT>::dequeue() { // Dequeue method
    if (size == 0) // There is nothing to dequeue
        return nullptr;
    CPUJob* result = (*front).JobPointer; // Front element is going to be dequeued

    for (int i = 0; i < size - 1; i++) { // Move every element in array to the left one
        NodePtrs[i] = NodePtrs[i + 1];
    }
    size--; // Decrement size
    if (size > 0) { // Checking to see if there is any elements to make front point to
        front = NodePtrs[0];
    } else { // If there is no elements, front = NULL
        front = nullptr;
    }
    return result; // Return resulting dequeued element
}
template <class DT>
int NovelQueue<DT>::modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) { // Modify a job's variables based on its job_id
    int jobPos = incrementalSearch(job_id); // Find job to modify
    NodePtrs[jobPos]->JobPointer = new CPUJob(job_id, new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed); // Modify the CPUJob object
    return jobPos; // Return index of job within array
}
template <class DT>
int NovelQueue<DT>::change(int job_id, int field_index, int new_value) { // Change one specific variable within CPUJob based on the job_id and the field_index (desired variable to change)
    int jobPos = incrementalSearch(job_id); // Find job to modify
    if (jobPos == -1) { // If job is not found
        return -1;
    }
    switch (field_index) { // Switch/case with the variables to alter based on field_index
        case 1: { // Altering priority
            NodePtrs[jobPos]->JobPointer->priority = new_value;
            break;
        }
        case 2: { // Altering job_type
            NodePtrs[jobPos]->JobPointer->job_type = new_value;
            break;
        }
        case 3: { // Altering cpu_time_consumed
            NodePtrs[jobPos]->JobPointer->cpu_time_consumed = new_value;
            break;
        }
        case 4: { // Altering memory_consumed
            NodePtrs[jobPos]->JobPointer->memory_consumed = new_value;
            break;
        }
    }
    return jobPos; // Return index of job within array
}
template <class DT>
int NovelQueue<DT>::promote(int job_id, int positions) { // Promote a job within the queue
    int jobPos = incrementalSearch(job_id); // Find job to promote
    int newPos = jobPos - positions; // Find its new position within the array

    Queue<DT>** newArray = new Queue<DT>*[size]; // Create new array
    for (int i = 0, j = 0; i < size; i++, j++) { // Copy over NodePtrs to newArray
        if (i == newPos) { // Determine whether current index is newPos
            if (i == 0) {
                front = NodePtrs[jobPos]; // If job is now front of the queue make it front
            }
            newArray[i] = NodePtrs[jobPos]; // Move job to new position
            i++;
        }
        if (j == jobPos) { // Make sure we do not move the job to the newArray twice
            j++;
        }
        newArray[i] = NodePtrs[j]; // Copy current index of NodePtrs to newArray
    }
    NodePtrs = newArray; // Make NodePtrs = newArray
    return newPos; // Return new position within array
}
template <class DT>
void NovelQueue<DT>::reorder(int attribute_index) { // Reorder the queue based on an attribute

    Queue<DT>** newArray = new Queue<DT>*[size]; // Create a temporary newArray

    // In every switch/case is its own sorting algorithm based on the attribute to be sorted by
    switch (attribute_index) {
        case 1: { // Sort by job_id (no need to account for duplicates)
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->job_id < NodePtrs[index]->JobPointer->job_id) {
                        index = j;
                    }
                }
                newArray[i] = NodePtrs[index];
                Queue<DT>* temp = NodePtrs[i];
                NodePtrs[i] = NodePtrs[index];
                NodePtrs[index] = temp;
            }
            break;
        }
        case 2: { // Sort by priority (Stable sort)
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->priority < NodePtrs[index]->JobPointer->priority ||
                        (NodePtrs[j]->JobPointer->priority == NodePtrs[index]->JobPointer->priority &&
                        NodePtrs[j]->JobPointer->job_id < NodePtrs[index]->JobPointer->job_id)) {
                        index = j;
                    }
                }
                newArray[i] = NodePtrs[index];
                Queue<DT>* temp = NodePtrs[i];
                NodePtrs[i] = NodePtrs[index];
                NodePtrs[index] = temp;
            }
            break;
        }
        case 3: { // Sort by job_type (Stable sort)
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->job_type < NodePtrs[index]->JobPointer->job_type ||
                        (NodePtrs[j]->JobPointer->job_type == NodePtrs[index]->JobPointer->job_type &&
                        NodePtrs[j]->JobPointer->job_id < NodePtrs[index]->JobPointer->job_id)) {
                        index = j;
                    }
                }
                newArray[i] = NodePtrs[index];
                Queue<DT>* temp = NodePtrs[i];
                NodePtrs[i] = NodePtrs[index];
                NodePtrs[index] = temp;
            }
            break;
        }
        case 4: { // Sort by cpu_time_consumed (Stable sort)
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->cpu_time_consumed < NodePtrs[index]->JobPointer->cpu_time_consumed ||
                        (NodePtrs[j]->JobPointer->cpu_time_consumed == NodePtrs[index]->JobPointer->cpu_time_consumed &&
                        NodePtrs[j]->JobPointer->job_id < NodePtrs[index]->JobPointer->job_id)) {
                        index = j;
                    }
                }
                newArray[i] = NodePtrs[index];
                Queue<DT>* temp = NodePtrs[i];
                NodePtrs[i] = NodePtrs[index];
                NodePtrs[index] = temp;
            }
            break;
        }
        case 5: { // Sort by memory_consumed (Stable sort)
            for (int i = 0; i < size; i++) {
                int index = i;
                for (int j = i + 1; j < size; j++) {
                    if (NodePtrs[j]->JobPointer->memory_consumed < NodePtrs[index]->JobPointer->memory_consumed ||
                        (NodePtrs[j]->JobPointer->memory_consumed == NodePtrs[index]->JobPointer->memory_consumed &&
                        NodePtrs[j]->JobPointer->job_id < NodePtrs[index]->JobPointer->job_id)) {
                        index = j;
                    }
                }
                newArray[i] = NodePtrs[index];
                Queue<DT>* temp = NodePtrs[i];
                NodePtrs[i] = NodePtrs[index];
                NodePtrs[index] = temp;
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
    for (int i = 0; i < size; i++) { // Displays all nodes within NodePtrs
        NodePtrs[i]->JobPointer->display();
    }
}
template <class DT>
int NovelQueue<DT>::count() {
    return size; // Return size of NodePtrs
}
template <class DT>
int NovelQueue<DT>::binarySearch(int key) { // Performs a binary search on NodePtrs and returns the index of the key
    int L = 0;
    int R = size - 1;
    while (L <= R) {
        int mid = (L+R) / 2;
        if (NodePtrs[mid]->JobPointer->job_id == key) {
            return mid; // Returns index when found
        }
        if (NodePtrs[mid]->JobPointer->job_id < key) {
            L = mid + 1;
        }
        else {
            R = mid - 1;
        }
    }
    return -1; // Returns -1 if unfound
}
template <class DT>
int NovelQueue<DT>::incrementalSearch(int key) { // Performs an incremental search on NodePtrs and returns index of the key
    for (int i = 0; i < size; i++) {
        if (NodePtrs[i]->JobPointer->job_id == key) {
            return i; // Returns index when found
        }
    }

    return -1; // Returns -1 if unfound
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
                if (jobsAdded < 1) { // Determine if job is already within queue (does not get added)
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
                int pos = myNovelQueue->modify(job_id, priority, job_type, cpu_time_consumed, memory_consumed); // Changes job's priority, job_type, cpu_time_consumed, and memory_consumed. Returns index within queue
                cout << "Modified Job ID " << job_id << ":" << endl;
                myNovelQueue->NodePtrs[pos]->JobPointer->display(); // Print modified job
                cout << "Jobs after modification:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break;
            }
            case 'C': {
                cin >> job_id >> field_index >> new_value; // Takes input to modify a specific field of a CPUJob object
                int pos = myNovelQueue->change(job_id, field_index, new_value); // Changes job's field_index with new_value and returns index within queue
                if (pos == -1) { // Determine if job was found within queue
                    cout << "Job with ID " << job_id << " not found in the queue." << endl;
                    break;
                }
                cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":" << endl;
                myNovelQueue->NodePtrs[pos]->JobPointer->display(); // Print changed job
                cout << "Jobs after changing field:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break;
            }
            case 'P': {
                cin >> job_id >> positions; // Takes input to promote a certain job within the queue
                int pos = myNovelQueue->promote(job_id, positions); // Promotes job within queue and returns index of job
                if (pos != -1) { // Determines if job was actually found within queue
                    cout << "Promoted Job ID " << job_id << " by " << positions << " Position(s):" << endl;
                    myNovelQueue->NodePtrs[pos]->JobPointer->display(); // Print promoted job
                    cout << "Jobs after promotion:" << endl;
                    myNovelQueue->display(); // Uses display() method to print all nodes in queue
                    break;
                }
                else { // If job not found do nothing
                    break;
                }
            }
            case 'O': {
                cin >> attribute_index; // Takes input to determine which field to reorder the queue by
                myNovelQueue->reorder(attribute_index); // Reorders queue nodes based on attribute index
                cout << "Reordered Queue by attribute " << attribute_index << ":" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break;
            }
            case 'D': { // Displays all jobs within queue
                cout << "Displaying all jobs in the queue:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break;
            }
            case 'N': { // Prints number of nodes in the queue
                int size = myNovelQueue->count(); // Grabs amount of nodes in queue
                cout << "Number of elements in the queue: " << size << endl;
                break;
            }
            case 'L': { // Lists jobs sorted by job IDs
                myNovelQueue->reorder(1); // Reorders queue based on field 1 (job_ID)
                cout << "List of jobs sorted by job IDs:" << endl;
                myNovelQueue->display(); // Uses display() method to print all nodes in queue
                break;
            }
            default: // Default case for undefined commands
                cout << "Invalid command" << endl;
        }
    }

    delete myNovelQueue; // Delete NovelQueue after program completion

    return 0; // End program
}

/*
LLM Documentation:
    Prompt and Suggestion 1: My prompt was me sending my reorder method to ChatGPT along with my output and asking why it is not working.
    Rationale 1: I specifically used this prompt because I had no idea why my output was incorrectly ordering the nodes within the queue.
    Incremental Development 1: The prompt allowed me to realize that I needed to implement a stable sort algorithm.
        The stable sorting algorithm I made functioned similar to mine, it just made it so that it sorts while also keeping the original order in mind.

    Prompt and Suggestion 2: My prompt was asking what a segmentation error was and why I kept getting them.
    Rationale 2: I used this prompt because I kept getting segmentation errors throughout my code and I didn't completely understand what they meant.
    Incremental Development 2: I used the knowledge I got from ChatGPT to not only fix my current segmentation errors, but also make sure I do not make anymore.
*/

/*
Debugging and Testing Plan:
    Specific Test 1: The first test I conducted was verifying that the for loops in my main method were successfully reading in and directing all of the 
        information as intended by printing out all of the information that I was reading in.
    Issue and Resolution 1: There was only a few cin issues, but I resolved them quickly.
    Verification 1: After using cout commands in my main to determine whether or not I am taking in exactly what I need to, I began to actually assign these 
        inputs to variables. I then tested to make sure this was completed properly by using display() methods that I created.

    Specific Test 2: My second test was testing to see if my reorder method was functioning as intended. I tested this by simply just running the program with the inputs and seeing
        what would output.
    Issue and Resolution 2: I encountered the issue of my reorder method not functioning as intended. It would just order explicitly by the attribute to be ordered by and wouldn't account
        at all the position in the queue the node is. I fixed this by asking ChatGPT what was wrong and then it gave me the idea to use a stable sort algorithm. So I made and implemented one.
    Verification 2: This worked spectacularly and allowed my output files to be identical to the output files given on canvas.
*/