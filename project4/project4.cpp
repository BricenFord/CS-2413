/*
Project Description:
This project's objective is to implement a Multiway Search Tree (M-Tree) using efficient insertion, deletion, and search operations by splitting a sorted
array recursively and using the split values for tree navigation.
*/

#include <iostream>
#include <vector>
using namespace std;

class NotFoundException { // Exception thrown when tasked to remove a value, but it is not found.
    public:
        const char* what() const {
            return "Value not found.";
        }
};

template <class DT>
class MTree {
    protected:
        int M; // Maximum number of children per node
        vector<DT> values; // Values stored in the node
        vector<MTree*> children; // Pointers to child MTrees
    public:
        MTree(int M); // MTree constructor given M value
        ~MTree(); // MTree destructor
        bool isLeaf() const; // Check if the current node is a leaf
        bool insert(DT& value); // Insert a value into the MTree
        void split_node(); // Split the node if it exceeds capacity
        MTree* find_child(const DT& value); // Find child
        bool search(const DT& value); // Search for a value in the MTree
        void remove(const DT& value); // Delete a value from the MTree
        void buildTree(vector<DT>& input_values); // Build the tree
        vector<DT> collect_values(); // Collect values from all leaf nodes
        bool find(DT& value); // Determine if a value is within the tree
};
template <class DT>
MTree<DT>::MTree(int M) { // MTree constructor given M value
    (*this).M = M;
}
template <class DT>
MTree<DT>::~MTree() { // MTree destructor
    for (int i = 0; i < children.size(); i++) { // Deletes all children's children recursively
        delete children[i];
    }

    children.clear();
}
template <class DT>
bool MTree<DT>::isLeaf() const { // Check if the current node is a leaf
    if (children.size() < 1) { // Uses the size of the nodes children vector
        return true; // If node has less than 1 children (mostly equivalent to 0) return true
    }
    return false; // If node has greater than or equal to 1 children then it is not a leaf node
}
template <class DT>
bool MTree<DT>::insert(DT& value) { // Insert a value into the MTree
    if (find(value)) { // Determines if value is already within MTree
        return false; // Returns false to verify the value was not inserted
    }
    vector<DT> temp = collect_values(); // Grabs values and stores them within temp

    // sort(temp.begin(), temp.end()); // Sorts all of the values in the temp vector
    bool inserted = false;
    for (int i = 0; i < temp.size() - 1; i++) {
        if (temp[i] < value && temp[i+1] > value) {
            int pos = i + 1;
            temp.insert(temp.begin() + pos, value);
            break;
        }
    }

    if (!inserted) {
        if (temp.empty() || temp.back() < value) {
            temp.push_back(value);
        }
    }

    buildTree(temp); // Builds a new tree given the temp vector
    return true; // Returns true to verify that the value was inserted
}
template <class DT>
void MTree<DT>::split_node() { // Split the node if it exceeds capacity
    if (values.size() < M) { // If the values are less than M, then nothing should be done
        return;
    }

    int splitSize = values.size() / M; // Determines the size for each split
    vector<DT> tempValues = values; // Stores the current values temporarily
    values.clear(); // Clears the current values to redistribute them into child nodes

    for (int i = 0; i < M; i++) { // Creates M children
        int start = i * splitSize; // Starting index for this child's values
        int end = (i == M - 1) ? tempValues.size() : (i + 1) * splitSize; // Handles the last child differently to include all remaining values

        vector<DT> childValues(tempValues.begin() + start, tempValues.begin() + end); // Extracts a portion of values for this child

        MTree<DT>* child = new MTree<DT>(M); // Creates a new child node
        child->values = childValues; // Assigns values to the child
        children.push_back(child); // Adds the child to the current node's children
    }
}
template <class DT>
MTree<DT>* MTree<DT>::find_child(const DT& value) { // Find child
    for (int i = 0; i < values.size(); i++) { // Iterates through the current node's values
        if (value < values[i]) { // If the value is less than the current value
            return children[i]; // Return the corresponding child
        }
    }
    return children[children.size() - 1]; return children[children.size() - 1]; // If no smaller value is found, return the last child
}
template <class DT>
bool MTree<DT>::search(const DT& value) { // Search for a value in the MTree
    for (int i = 0; i < values.size(); i++) { // Check current node's values
        if (values[i] == value) { // If the value is found
            return true; // Return true to indicate value found
        }
    }

    if (isLeaf()) { // If the current node is a leaf
        return false; // The value is not found
    }

    MTree<DT>* child = find_child(value); // Determine which child might contain the value
    if (child) { // If a valid child is found
        return child->search(value); // Recursively search in the child
    }

    return false; // If no valid child is found, return false
}
template <class DT>
void MTree<DT>::remove(const DT& value) { // Delete a value from the MTree
    vector<DT> temp = (*this).collect_values(); // Collect all values from the true into a temp vector
    bool found = false; // Placeholder for whether or not value is found
    for (int i = 0; i < temp.size(); i++) { // Iterate through the collected values
        if (temp[i] == value) { // If the value to be removed is found
            found = true; // Set found to true
            for (int j = i; j < temp.size() - 1; j++) { // Shift subsequent values to overwrite the found value
                temp[j] = temp[j + 1];
            }
            temp.pop_back(); // Remove the last value (now a duplicate due to shifting)
            break; // Exit the loop since the value is found and removed
        }
    }

    if (!found) { // If the value was not found in the tree
        throw NotFoundException(); // Throw a NotFoundException to indicate an error
    }

    buildTree(temp); // Rebuild the tree with the updated values after removal
}
template <class DT>
void MTree<DT>::buildTree(vector<DT>& input_values) { // Build the tree given a vector of values

    values.clear(); // Clear the current node's values
    for (int i = 0; i < children.size(); i++) { // Delete all child nodes
        delete children[i];
    }
    children.clear(); // Clear the children vector

    if (input_values.size() <= M - 1) { // If the input values fit within a single node
        values = input_values; // Assign them to the current node
        return;
    }
    else {
        int D = input_values.size() / M; // Determine the size of each partition
        for (int i = 0; i < M; i++) { // Create M children
            int start = D * i; // Starting index for this partition
            int end;
            if (i == M - 1) { // Handle the last partition
                end = input_values.size() -1;
            }
            else {
                end = start + D - 1;
                values.push_back(input_values[end]); // Store a boundary value in the current node
            }
            vector<DT> child_values(input_values.begin() + start, input_values.begin() + end + 1); // Extra partition values
            MTree<DT>* child = new MTree<DT>(M); // Create a new child node
            child->buildTree(child_values); // Recursively build the child
            children.push_back(child); // Add the child to the current node
        }
    }
}
template <class DT>
vector<DT> MTree<DT>::collect_values() { // Collect values from all leaf nodes
    vector<DT> result; // Stores the collected values

    for (int i = 0; i < M; i++) { // Iterates through all children
        if (children[i]->isLeaf()) { // If the child is a leaf
            int value;
            for (int j = 0; j < children[i]->values.size(); j++) { // Collect all values from the leaf
                value = children[i]->values[j];
                result.push_back(value); // Add each value to the result
            }
        }
        else {
            vector<DT> result2 = children[i]->collect_values(); // Recursively collect values from non-leaf children
            for (int j = 0; j < result2.size(); j++) { // Add these values to the result
                result.push_back(result2[j]);
            }
        }
    }

    return result; // Return all collected values
}
template <class DT>
bool MTree<DT>::find(DT& value) { // Determine if a value is within the tree
    
    for (int i = 0; i < M; i++) { // Iterates through all children
        if (children[i]->isLeaf()) { // If the child is a leaf
            int x;
            for (int j = 0; j < children[i]->values.size(); j++) { // Search all values in the leaf
                x = children[i]->values[j];
                if (x == value) { // If the value is found
                    return true; // Return true
                }
            }
        }
        else {
            if (children[i]->find(value)) { // Recursively search in non-leaf children
                return true; // If found in a child, return true
            }
        }
    }

    return false; // Return false if the value is not found
}

int main() {
    int n = 0; // Amount of values within array
    int MValue; // MValue for the MTree
    int numCommands; // Number of commands given to the MTree
    char command; // Current command given to the MTree
    int value; // Value taken in (with a command that takes a value)

    vector<int> mySortedValues(n); // Create vector with size of the number of values

    cin >> n; // Read in number of values
    for (int i = 0; i < n; i++) { // Puts the values into mySortedValues vector
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
        switch (command) { // Switch/case to determine what each command does
            case 'I': { // Insert
                cin >> value; // Take in value to be inserted
                bool canBeInserted = myTree->insert(value); // Simultaneously insert the value and verify whether it can be inserted
                if (canBeInserted) { // If the value is inserted
                    cout << "The value = " << value << " has been inserted." << endl;
                }
                else { // If the value is not inserted
                    cout << "The value = " << value << " already in the tree." << endl;
                }
                break;
            }
            case 'R': { // Remove
                cin >> value; // Take in value to be removed
                try { // Try to remove value
                    myTree->remove(value);
                    cout << "The value = " << value << " has been removed." << endl;
                } catch (NotFoundException& e) { // If value is not within MyTree
                    cout << "The value = " << value << " not found." << endl;
                }
                break;
            }
            case 'F': { // Find
                cin >> value; // Take in value to be found
                bool isFound = myTree->find(value); // Search MyTree for value and determine whether it is found
                if (isFound) { // If value is found
                    cout << "The element with value = " << value << " was found." << endl;
                }
                else { // If value is not found
                    cout << "The element with value = " << value << " not found." << endl;
                }
                break;
            }
            case 'B': { // Rebuild Tree
                vector<int> myValues = (*myTree).collect_values(); // Takes values within current tree
                (*myTree).buildTree(myValues); // Rebuilds the tree
                cout << "The tree has been rebuilt." << endl;
                break;
            }
            default: { // Invalid command
                cout << "Invalid command!" << endl;
                break;
            }
        }
    }

    cout << "Final list: ";
    vector<int> finalList = myTree->collect_values(); // Grabs all values within MTree and puts them into finalList vector
    for (int i = 0, j = 1; i < finalList.size(); i++, j++) { // Prints every value within finalList vector
        cout << finalList[i];
        if (i < finalList.size() - 1) { // If the value is not the last value in the vector, put a space after the value
            cout << " ";
        }
        if (j % 20 == 0 && j != 0) { // Every 20 values there should be a newline
            cout << endl;
        }
    }

    delete myTree; // Delete MTree
    return 0; // Program end
}

/*
LLM Documentation:
    Prompts and Suggestions 1: Help me fix the remove method in my MTree class.
    Rationate 1: I encountered challenges in implementing the `remove` method, particularly in preserving the tree structure and handling exceptions. 
        The LLM provided a clear and functional implementation.
    Incremental Development 1: The `remove` method was refined to correctly search for the value, remove it from the collected values, 
        and rebuild the tree while maintaining the integrity of the MTree structure.

    Prompts and Suggestions 2: Make an exception for me called NotFoundException.
    Rationale 2: I was having issues making my exception class function, and it helped me to create and implement the new class.
    Incremental Development 2: I used this prompt to create my NotFoundException class, which is highlighted as needed in the project 4 guide.
*/

/*
Debugging and Testing Plan:
    Specific Test 1: After creating a for loop to read in all of the values to be inserted into the mySortedValues vector, I then created another for loop to print all of these values to 
        test and see if everything is functioning as intended before moving on.
    Issues and Resolutions 1: There was no issues
    Verification 1: I combined the output from the console with the input files to verify that all of the numbers are being read in correctly.

    Specific Test 2: I created a program that compares strings so that I could compare my output for each input file to the correct output files.
    Issues and Resolutions 2: It took me time to create the program, and complete this program so that all of the outputs are correct, but overall minimal issues.
    Verification 2: Using the program I created I could paste the output I got from the project4 program I created and the desired output files for the project to see if my program was 
        functioning properly.
*/