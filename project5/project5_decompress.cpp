/*
Project Description:
Take the output from project5.cpp and convert it back into the original text.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {

    string outputFromProject5File; // Variable for storing all output from the original project5 file so that I can use it for project5_decompress

    /*
    DISCLAIMER!
    Below is the original project5 program (the only change is all output is redirected from the console to outputFromProject5File)
    */

    // string fileName; // Variable for storing the file name of the input file
    map<string, int> orderedTokenCount; // Red/Black Tree to efficiently store the token with its corresponding frequency
    string *tokenList = new string[1]; // Stores input tokens

    string token; // Variable to store the current token being read in from input
    int tokenCount = 0; // Variable to store the total number of tokens in the file

    cin >> token; // Read in the first token
    orderedTokenCount[token]++; // Place first token within Red/Black Tree
    tokenList[tokenCount] = token; // Places first token into tokenList array
    tokenCount++; // Increment tokenCount

    // Hardcoded fileName detector
    // if (token == "Can") { // If the first token is "Can" input1.txt is the fileName
    //     fileName = "tests/input1.txt";
    // }
    // else if (token == "Technology") { // If the first token is "Technology" input2.txt is the fileName
    //     fileName = "tests/input2.txt";
    // }
    // else { // Else the fileName is input3.txt
    //     fileName = "tests/input3.txt";
    // }

    while (cin >> token) { // Read in the rest of the tokens
        orderedTokenCount[token]++; // Add the tokens to the Red/Black Tree
        tokenCount++; // Increment tokenCount
        string *temp = new string[tokenCount]; // Temporary array
        for (int i = 0; i < tokenCount - 1; i++) { // Move everything from uniqueTokenList to temp array
            temp[i] = tokenList[i];
        }
        temp[tokenCount - 1] = token; // Add new token to temp array
        delete[] tokenList; // Delete uniqueTokenList's contents
        tokenList = temp; // Set uniqueTokenList equal to temp
    }

    string *uniqueTokenList = new string[tokenCount]; // Create a string array of size tokenCount to store unique tokens
    int uniqueTokenCount = 0; // Variable to store amount of unique tokens
    
    for (int i = tokenCount; i > 0; i--) { // This loop goes from the amount of tokens down to 0
        for (map<string, int>::iterator it = orderedTokenCount.begin(); it != orderedTokenCount.end(); ++it) { // This loop uses an iterator with my orderedTokenCount variable to print every token in order of their frequency
            token = it->first; // Puts the first section (the string) into the token variable
            if (it->second == i) { // Determines whether the second section (the int) is equivalent to i (token frequency)
                outputFromProject5File += token + " "; // Print token
                uniqueTokenList[uniqueTokenCount] = token; // Add unique token to unique token array
                uniqueTokenCount++; // Increment uniqueTokenCount
            }
        }
    }

    outputFromProject5File += "\n";
    outputFromProject5File += "**********\n";

    // ifstream inputFile(fileName); // Open up the previously identified input file

    for (int i = 0; i < tokenCount; i++) { // Go through entire inputFile and capture the tokens
        // inputFile >> token; // Set token
        token = tokenList[i]; // Read the tokens from tokenList into token
        for (int j = 0; j < uniqueTokenCount; j++) { // Go through the entire uniqueTokenList to determine the index of the current token being read in
            if (token == uniqueTokenList[j]) { // Determine whether or not the current token being read in is the jth token within the array
                outputFromProject5File += to_string(j + 1); // The output starts from index 1, so increment all indeces by 1
                break; // Break when the token is found within uniqueTokenList
            }
        }
        outputFromProject5File += " ";
    }

    /*
    DISCLAIMER!
    Below is the decompression section of the program.
    */

    token = ""; // Variable for storing token input
    uniqueTokenCount = 0; // Variable for storing number of unique tokens
    uniqueTokenList = new string[uniqueTokenCount]; // Variable for storing unique tokens

    istringstream project5Output(outputFromProject5File); // Convert the string from project5 output into a stream
    while (project5Output >> token && token != "**********") { // Read in all tokens until you get to the separator
        uniqueTokenCount++; // Increment counter
        string *temp = new string[uniqueTokenCount]; // Create temp array
        for (int i = 0; i < uniqueTokenCount - 1; i++) { // Move everything from uniqueTokenList to temp array
            temp[i] = uniqueTokenList[i];
        }
        temp[uniqueTokenCount - 1] = token; // Add new token to temp array
        delete[] uniqueTokenList; // Delete uniqueTokenList's contents
        uniqueTokenList = temp; // Set uniqueTokenList equal to temp
    }

    int index; // Var for storing input index
    int indexCount = 0; // Var for storing number of indexes
    int *indexList = new int[indexCount]; // Array for storing all indeces input

    while (project5Output >> index) { // Take in all indeces
        indexCount++; // Increment indexCount
        int *temp = new int[indexCount]; // Create temp array
        for (int i = 0; i < indexCount - 1; i++) { // Move everything from indexList to temp array
            temp[i] = indexList[i];
        }
        temp[indexCount - 1] = index - 1; // Add new index to temp array
        delete[] indexList; // Delete indexList's contents
        indexList = temp; // Set indexList equal to temp
    }

    for (int i = 0; i < indexCount; i++) { // Go through entire indexList array and use uniqueTokenList array to print the corresponding token
        cout << uniqueTokenList[indexList[i]];
        if (i < indexCount - 1) { // Determine whether we are at the end of the output
            cout << " ";
        }
    }

    return 0;
}

/*
Debugging and Testing Plan:
    Specific Test 1: My first thought process when making this program was to take in all of the unique tokens and put them into a string array, so the first test I did was to make sure
        that I was properly taking the input and putting it into the string array. I did this by just using a for loop to increment through the whole array and print it to console.
    Issues and Resolutions 1: I did not have any issues doing this.
    Verification 1: This test was very important for me to complete the program because I need to have all of the tokens in an array so when I go to print the tokens with the index locations I can just use the indexes of the array.
*/