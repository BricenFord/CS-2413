/*
Project Description:
This project's objective is to implement a Multiway Search Tree (M-Tree) using efficient insertion, deletion, and search operations by splitting a sorted
array recursively and using the split values for tree navigation.
*/

template <class DT>
/* Write NotFoundException exception for removal */
class MTree {
    private:
        DT value;
    public:
        MTree(); // Default constructor
        MTree(DT value); // Take value and create MTree node (object)
        ~MTree(); // Destructor
        MTree* LC; // Left subtree
        MTree* RC; // Right subtree
        DT insert(DT value); // !!!
        DT search(DT value); // !!!
        DT remove(DT value); // !!!
        void rebuild(); // !!!
};

int main() {
    int n; // Amount of values within initial array
    int MValue;
    int numCommands;
    char command;
    int value;

    switch (command) {
        case 'I': { // Insert

        }
        case 'R': { // Remove

        }
        case 'F': { // Find

        }
        case 'B': { // Rebuild Tree

        }
        default: {// Invalid command
            // invalid command exception (just print "Invalid command!" << endl)
        }
    }

    return 0;
}