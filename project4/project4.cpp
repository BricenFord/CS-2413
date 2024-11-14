/*
Project Description:
This project's objective is to implement a Multiway Search Tree (M-Tree) using efficient insertion, deletion, and search operations by splitting a sorted
array recursively and using the split values for tree navigation.
*/

#include <iostream>
#include <vector>
using namespace std;

template <class DT>
/* Write NotFoundException exception for removal */
class MTree {
    protected:
        int M; // Maximum number of children per node
        vector<DT> values; // Values stored in the node
        vector<MTree*> children; // Pointers to child MTrees
    public:
        MTree(int M);
        ~MTree();
        bool isLeaf() const; // Check if the current node is a leaf
        void insert(const DT& value); // Insert a value into the MTree
        void split_node(); // Split the node if it exceeds capacity
        MTree* find_child(const DT& value); // Find child
        bool search(const DT& value); // Search for a value in the MTree
        void remove(const DT& value); // Delete a value from the MTree
        void buildTree(vector<DT>& input_values); // Build the tree
        vector<DT> collect_values(); // Collect values from all leaf nodes
        bool find(DT& value); // Determine if a value is within the tree
};
template <class DT>
MTree<DT>::MTree(int M) { //
    (*this).M = M;
}
template <class DT>
MTree<DT>::~MTree() { //
    //
}
template <class DT>
bool MTree<DT>::isLeaf() const {
    if (children.size() < 1) {
        return true;
    }
    return false;
}
template <class DT>
void MTree<DT>::insert(const DT& value) {
    //
}
template <class DT>
void MTree<DT>::split_node() {
    //
}
template <class DT>
MTree<DT>* MTree<DT>::find_child(const DT& value) {
    //
    return nullptr;
}
template <class DT>
bool MTree<DT>::search(const DT& value) {
    //
    return false;
}
template <class DT>
void MTree<DT>::remove(const DT& value) {
    //
}
template <class DT>
void MTree<DT>::buildTree(vector<DT>& input_values) {
    if (input_values.size() <= M - 1) {
        values = input_values;
        return;
    }
    else {
        int D = input_values.size() / M;
        for (int i = 0; i < M; i++) {
            int start = D * i;
            //cout << "start: " << start << " - ";
            int end;
            if (i == M - 1) {
                end = input_values.size() -1;
                //cout << "end: " << end << endl;
            }
            else {
                end = start + D - 1;
                //cout << "end: " << end << endl;
                values.push_back(input_values[end]);
            }
            vector<DT> child_values(input_values.begin() + start, input_values.begin() + end + 1);
            MTree<DT>* child = new MTree<DT>(M);
            child->buildTree(child_values);
            children.push_back(child);
        }
    }
}
template <class DT>
vector<DT> MTree<DT>::collect_values() {
    vector<DT> result;

    for (int i = 0; i < M; i++) {
        if (children[i]->isLeaf()) {
            int value;
            for (int j = 0; j < children[i]->values.size(); j++) {
                value = children[i]->values[j];
                result.push_back(value);
            }
        }
        else {
            vector<DT> result2 = children[i]->collect_values();
            for (int j = 0; j < result2.size(); j++) {
                result.push_back(result2[j]);
            }
        }
    }

    return result;
}
template <class DT>
bool MTree<DT>::find(DT& value) {
    
    for (int i = 0; i < M; i++) {
        if (children[i]->isLeaf()) {
            int x;
            for (int j = 0; j < children[i]->values.size(); j++) {
                x = children[i]->values[j];
                if (x == value) {
                    return true;
                }
            }
        }
        else {
            if (children[i]->find(value)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int n = 0; // Amount of values within initial array
    int MValue;
    int numCommands;
    char command;
    int value;

    vector<int> mySortedValues(n); // Create vector with size of the number of values

    cin >> n; // Read in number of values
    for (int i = 0; i < n; i++) {
        int input;
        cin >> input;
        mySortedValues.push_back(input);
    }

    cin >> MValue; // Read in the MValue
    MTree<int>* myTree = new MTree<int>(MValue); // Create MTree with MValue

    (*myTree).buildTree(mySortedValues); // Create tree with sorted values list

    cin >> numCommands; // Read in number of commands
    for (int i = 0; i < numCommands; i++) { // Increment through all commands
        cin >> command;
        cout << command << endl;
        switch (command) { // Switch/case to determine what each command does
            case 'I': { // Insert
                cin >> value;
                break;
            }
            case 'R': { // Remove
                cin >> value;
                break;
            }
            case 'F': { // Find
                cin >> value;
                bool isFound = myTree->find(value);
                if (isFound) {
                    cout << "The element with value = " << value << " was found." << endl;
                }
                else {
                    cout << "The value " << value << " was not found" << endl; // THIS WILL CHANGE I DO NOT KNOW WHAT THE PROPER OUTPUT IS FOR THIS CASE !!!
                }
                break;
            }
            case 'B': { // Rebuild Tree
                //vector<int> myValues = (*myTree).collect_values();
                //(*myTree).buildTree(myValues);
                break;
            }
            default: { // Invalid command
                cout << "Invalid command!" << endl;
                break;
            }
        }
    }

    cout << "Final list: ";
    vector<int> finalList = myTree->collect_values();
    for (int i = 0; i < finalList.size(); i++) {
        cout << finalList[i];
        if (i < finalList.size() - 1) {
            cout << " ";
        }
    }

    delete myTree;
    return 0;
}

/*
LLM Documentation:
*/

/*
Debugging and Testing Plan:
    Specific Test 1: After creating a for loop to read in all of the values to be inserted into the mySortedValues vector, I then created another for loop to print all of these values to 
        test and see if everything is functioning as intended before moving on.
    Issues and Resolutions 1: There was no issues
    Verification 1: I combined the output from the console with the input files to verify that all of the numbers are being read in correctly.

    Specific Test 2:
    Issues and Resolutions 2:
    Verification 2:
*/