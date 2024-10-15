#include <iostream>
#include <string>
using namespace std;

// Class for holding information and computing operations on Chips
class Chip {
    private:
    char chipType; // Var for holding chipType
    string id; // Var for holding Chip ID
    Chip* input1 = nullptr; // Var for holding 1st input chip
    Chip* input2 = nullptr; // Var for holding 2nd input chip
    Chip* output = nullptr; // Var for holding output chip
    double inputValue; // Var to hold input chip's value

    public:
    // Constructors
    Chip() {} // Default constructor
    Chip(char type, const string& id); // Parameterized constructor
    // Destructor
    ~Chip();
    // Method prototypes
    Chip& operator=(const Chip& Chip); // = overloader method
    double compute(); // Performs the operation based on the chip type
    void display() const; // Displays the chip's information
    // Setters
    void setInput1(Chip* inputChip); // Sets the first input chip
    void setInput2(Chip* inputChip); // Sets the second input chip
    void setOutput(Chip* outputChip); // Sets the output chip
    void setInputValue(double value); // Sets the chip's input value
    // Getters
    string getID() const; // Returns the chip ID
    double getInputValue() const; // Returns chip input value
    char getChipType() const; // Returns chip type
    Chip* getInput1() const; // Returns Chip pointer for input1
    Chip* getInput2() const; // Returns Chip pointer for input2
};

// Instantiates chiptype and chip id
Chip::Chip(char type, const string& id) {
    this->chipType = type;
    this->id = id;
}
// Clears up memory by deleting chip pointers/objects
Chip::~Chip() {
}
// Overloads = operator on Chip objects by transferring over all values from instance variables
Chip& Chip::operator=(const Chip& Chip) {
    this->chipType = Chip.chipType;
    this->id = Chip.id;
    this->input1 = Chip.input1;
    this->input2 = Chip.input2;
    this->output = Chip.output;
    this->inputValue = Chip.inputValue;
    return *this;
}
// Sets input1 chip pointer to input
void Chip::setInput1(Chip* inputChip) {
    input1 = inputChip;
}
// Sets input2 chip pointer to input
void Chip::setInput2(Chip* inputChip) {
    input2 = inputChip;
}
// Sets output chip pointer to input
void Chip::setOutput(Chip* outputChip) {
    output = outputChip;
}
// Sets inputValue for input chips
void Chip::setInputValue(double value) {
    inputValue = value;
}
// Computes different operations based on chip type
double Chip::compute() {
    double result = 0; // result value

    // if chiptype is input chip then returns inputValue for input chips so that operations can be performed on them
    if (chipType == 'I') {
        return inputValue;
    }

    // if output chip, just return the input's computed value
    if (chipType == 'O') {
        if (input1 != nullptr) {
            return input1->compute();
        }
    }

    // negation returns the value but negative
    if (chipType == 'N') {
        if (input1 != nullptr) {
            return -input1->compute();  // negate the computed input value
        }
    }

    // Addition (A), Multiplication (M), Subtraction (S), and Division (D) operations
    double value1 = 0, value2 = 0; // keep track of values so operations can be performed on them

    if (input1 != nullptr) { // checking if chip has an input1 chip
        value1 = input1->compute();
    }
    if (input2 != nullptr) { // checking if chip has an input2 chip
        value2 = input2->compute();
    }

    switch (chipType) { // does operation based on chiptype
        case 'A': // addition
            result = value1 + value2;
            break;
        case 'M': // multiplication
            result = value1 * value2;
            break;
        case 'S': // subtraction
            result = value1 - value2;
            break;
        case 'D': // division (does not allow division by 0)
            if (value2 != 0) {
                result = value1 / value2;
            }
            break;
    }
    return result; // returns result value
}
// Displays chips inputs and output if defined
void Chip::display() const {
    cout << id << ", ";
    if (input1 != nullptr) { // if input1 is defined print it
        cout << "Input 1 = " << input1->getID();
    }
    if (input2 != nullptr) { // if input2 is defined print it
        cout << ", Input 2 = " << input2->getID() << ", ";
    } 
    else if (chipType == 'N') { // if the chip is a negation chip (which only has one input) then print "None" for second input
        cout << ", Input 2 = " << "None" << ", ";
    }
    if (output != nullptr) { // if output is defined print it
        cout << "Output = " << output->getID();
    }
    cout << endl; // print end line
}
// Returns chip id
string Chip::getID() const {
    return id;
}
// Returns inputValue for input chips
double Chip::getInputValue() const {
    return inputValue;
}
// Returns chipType of chip
char Chip::getChipType() const {
    return chipType;
}
// Returns input1 chip
Chip* Chip::getInput1() const {
    return input1;
}
// Returns input2 chip
Chip* Chip::getInput2() const {
    return input2;
}

// Main
int main () {
    // Variables
    int numChips; // Total number of chips
    Chip** allChips; // Array of Chip pointers (to be instantiated later with size of numChips)
    int numCommands; // Total number of commands
    string input; // String for holding input
    double result; // Double for holding result (result of compute method to print at end)
    int indexOfOutput; // Int for indexOfOutput (so that we can always print the output chip last)
    
    cin >> numChips; // Input number of chips
    allChips = new Chip*[numChips]; // Initialize Chip array to have size of input

    // Reads in all chips to allChips array of Chip pointers
    for (int i = 0; i < numChips; i++) {
        cin >> input; // read input
        char chipType = input[0]; // first letter is chiptype
        string chipID = input; // all is chip id
        allChips[i] = new Chip(chipType, chipID); // adds this new chip to the allChips array of chip pointers
    }

    cin >> numCommands; // read in number of commands
    
    // Increment through all of the commands and set inputs, outputs, input value, and finally compute()
    for (int i = 0; i < numCommands; i++) {

        cin >> input; // read in input to determine whether it is an A (assigning input or output), I (assigning input value), or O (commands are complete and it is time to compute)

        // Assigns input and output given input
        if (input == "A") {
                string inputChipID, targetChipID; // create holders for input
                cin >> inputChipID >> targetChipID; // take in input
                Chip* inputChip = nullptr; // create placeholder for when input chip is found
                Chip* targetChip = nullptr; // create placeholder for when target chip is found

                // Find input and target chip within allChips
                for (int i = 0; i < numChips; i++) {
                    if (allChips[i]->getID() == inputChipID) {
                        inputChip = allChips[i];
                    }
                    if (allChips[i]->getID() == targetChipID) {
                        targetChip = allChips[i];
                    }
                }

                // If both targetChip and inputChip have values that are not null (they were found within allChips array), then we assign the respective input and output chips.
                if (targetChip && inputChip) {
                    if (targetChip->getInput1() == nullptr) {
                        targetChip->setInput1(inputChip);
                        inputChip->setOutput(targetChip);
                    } else if (targetChip->getInput2() == nullptr) {
                        targetChip->setInput2(inputChip);
                        inputChip->setOutput(targetChip);
                    }
                }
        }
        // Assigns input value given input
        else if (input == "I") {
            cin >> input;
            for (int i = 0; i < numChips; i++) {
                if (allChips[i]->getID() == input) {
                    cin >> input;
                    allChips[i]->setInputValue(stod(input)); // parse the input into a double so that we can assign inputValue
                }
            }
        }
        // Performs compute()
        else if (input == "O") {
            cin >> input;
            for (int i = 0; i < numChips; i++) {
                if (allChips[i]->getID() == input) {
                    result = allChips[i]->compute(); // compute
                    indexOfOutput = i; // grab the index of output to print later
                }
            }
        }
    }

    cout << "Computation Starts" << endl;
    cout << "The output value from this circuit is " << result << endl; // print result acquired from compute()
    cout << "***** Showing the connections that were established" << endl;
    for (int i = 0; i < numChips; i++) { // print all Chips within allChips except the output chip
        if (i != indexOfOutput)
            allChips[i]->display();
    }
    allChips[indexOfOutput]->display(); // print output chip

    for (int i = 0; i < numChips; i++) { // delete chip pointers within allChips array
        delete allChips[i];
    }

    delete[] allChips; // delete array of chip pointers
    return 0;
}

/*
LLM Documentation:
    Prompt and Suggestion 1: Generate a recursive compute method given that I just want to feed it the output chip and it should read the line of input chips given the input chip into the output chip.
    Rationale 1: I chose this prompt because I wanted to be as concise as possible while also highlighting the main points that needed to be completed.
    Incremental Development 1: This allowed me to really grasp on to how exactly I should make the method function so that I can add the multiple if statements for differing chiptypes to do different functions.

    Prompt and Suggestion 2: This compute method is great, now I just need you to implement some way for the chips of chiptype I to use their inputValue var so that the value doesn't remain 0 the entire time.
    Rationale 2: I chose this prompt because chatgpt already had my previous prompt in its memory so I didn't have to give any further information for it to easily solve my issue.
    Incremental Development 2: The response to my prompt gave me a great guide on how I can further fix the compute() method and in turn, complete it.
*/

/*
Debugging and Testing Plan:
    Specific Test 1: The first test I conducted was verifying that the for loops in my main method were successfully reading in and directing all of the information as intended by printing out all of the information that I was reading in.
    Issue and Resolution 1: There was no issues when doing this, but it did help me to know precisely how the cin command works and how much information it takes in every time it is used.
    Verification 1: After using cout commands in my main to determine whether or not I am taking in exactly what I need to, I began to actually assign these inputs to variables within the respective Chip objects. I then tested to make sure this was completed properly by using the display() method.
    
    Specific Test 2: I checked to see if my setinput and setoutput logic is correct by creating the display method and using it on all elements of the allchips arr for all of the given input.txt files.
    Issue and Resolution 2: At first it was difficult for me to pinpoint exactly where my logic was wrong, but then I realized that the issue lied within my determining which input value to set the input to.
    Verification 2: I solved this by setting all of the instance variable chips to nullptr so that I could use if statements to determine if they had been set to a chip value or not so I could determine whether the chip should be set to input1 or input2.

    Specific Test 3: I used chatgpt to make my compute() method so, of course, it had some basic errors to fix. I determined this from testing the input1.txt on my program and noticing that it grabs all of the chips successfully but the result never increases from 0.
    Issue and Resolution 3: The underlying issue was that it never actually grabbed the inputvalues from the input chips. All I had to do was add another if statement to my compute() method that makes chiptype of I return inputvalue.
    Verification 3: I verified that all works splendidly by running all three input.txt files provided on my program.
*/