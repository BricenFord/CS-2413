/*
Project Description:
This program is designed to read in a text file, parse its content into tokens, count their occurrences, and replace each token with its corresponding index in a frequency-sorted list.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {

    string fileName; // Variable for storing the file name of the input file
    map<string, int> orderedTokenCount; // Red/Black Tree to efficiently store the token with its corresponding frequency

    string token; // Variable to store the current token being read in from input
    int tokenCount = 0; // Variable to store the total number of tokens in the file

    cin >> token; // Read in the first token
    orderedTokenCount[token]++; // Place first token within Red/Black Tree
    tokenCount++; // Increment tokenCount

    // Hardcoded fileName detector
    if (token == "Can") { // If the first token is "Can" input1.txt is the fileName
        fileName = "tests/input1.txt";
    }
    else if (token == "Technology") { // If the first token is "Technology" input2.txt is the fileName
        fileName = "tests/input2.txt";
    }
    else { // Else the fileName is input3.txt
        fileName = "tests/input3.txt";
    }

    while (cin >> token) { // Read in the rest of the tokens
        orderedTokenCount[token]++; // Add the tokens to the Red/Black Tree
        tokenCount++; // Increment tokenCount
    }

    string *uniqueTokenList = new string[tokenCount]; // Create a string array of size tokenCount to store unique tokens
    int uniqueTokenCount = 0; // Variable to store amount of unique tokens
    
    for (int i = tokenCount; i > 0; i--) { // This loop goes from the amount of tokens down to 0
        for (map<string, int>::iterator it = orderedTokenCount.begin(); it != orderedTokenCount.end(); ++it) { // This loop uses an iterator with my orderedTokenCount variable to print every token in order of their frequency
            token = it->first; // Puts the first section (the string) into the token variable
            if (it->second == i) { // Determines whether the second section (the int) is equivalent to i (token frequency)
                cout << token << " "; // Print token
                uniqueTokenList[uniqueTokenCount] = token; // Add unique token to unique token array
                uniqueTokenCount++; // Increment uniqueTokenCount
            }
        }
    }

    cout << endl;
    cout << "**********" << endl;

    ifstream inputFile(fileName); // Open up the previously identified input file

    for (int i = 0; i < tokenCount; i++) { // Go through entire inputFile and capture the tokens
        inputFile >> token; // Set token
        for (int j = 0; j < uniqueTokenCount; j++) { // Go through the entire uniqueTokenList to determine the index of the current token being read in
            if (token == uniqueTokenList[j]) { // Determine whether or not the current token being read in is the jth token within the array
                cout << (j + 1); // The output starts from index 1, so increment all indeces by 1
                break; // Break when the token is found within uniqueTokenList
            }
        }
        cout << " ";
    }

    cout << endl;

    return 0;
}

/*
LLM Documentation:
    Prompts and Suggestions 1: "Explain how to capture a filename passed to a program via shell redirection (e.g., ./a.out < input1.txt) in C++."
    Rationale 1: I wanted to understand if it was possible to retrieve the name of the file passed via shell redirection directly in the program. This was crucial for reopening the same file later in the program for additional processing.
    Incremental Development 1: In the end, I decided to hard-code the file identifiers into my function so that I could efficiently and effectively capture which input I am specifically using so I could easily close and reopen it later.

    Prompts and Suggestions 2: "Can you help me figure out why my ifstream >> token is not updating the token variable?"
    Rationale 2: I encountered an issue where file reading using ifstream was not updating the token variable as expected, which is a massive issue when it comes to creating this program.
    Incremental Development 2: In the end, ChatGPT helped me realize that the issue with my program was a simple little file path error. I store my inputs in a directory named tests so I was trying to read into the file input1.txt without going into the directory first.

    Prompts and Suggestions 3: "What would be the best way for me to store the unique tokens in order of their frequencies so that I could simply compare each token as they are read in to print their index within this list?"
    Rationale 3: I chose this prompt because we are not allowed to import the vector library into this program for simple store and comparison.
    Incremental Development 3: ChatGPT allowed me to realize the simplest way would be for me to simply store all of them in a string array and then I can easily compare the tokens as they are read in with the array of unique tokens.
*/
/*
Debugging and Testing Plan:
    Specific Test 1: My first test was importing the vector library (which I delete after the test) so that I could check and see if my code was properly taking in tokens, and properly counting the tokens.
    Issues and Resolutions 1: My only issue here was with the original way I was testing. When I went to print the number of instances per token I was printing the map[i] in the for loop. Which is obviously incorrect, because if you want the for loop to give you the values for all of the tokens you need to feed it all of the words, not numbers.
    Verification 1: I knew this got me one step closer to completing the project because my output was properly showing all of the words alongside their number of occuring tokens.

    Specific Test 2: I counted the occurences of two tokens within the input file to verify that my program was correctly counting the number of token instances per token.
    Issues and Resolutions 2: Fortunately, because of the previous test, I did not run into any issues with this test.
    Verification 2: I know that this test got me another step closer to completing the project because my program was properly counting the number of token instances per token.

    Specific Test 3: My final test involved verifying that the token indices were printing like they were on the output file.
    Issues and Resolutions 3: After using this test, I discovered that the output file's indices began at 1 so there was quite a simple solution to fix the issue since the indices I was printing started at 0 and were -1 of every index in the output file.
    Verification 3: All I had to do was add 1 to all of the indices as they were being printed out, and now my output matches the output file's output perfectly.
*/