/**
 * @brief We will input a file, identify the substrings and find all syntax errors
 * @author Stephen Witley???
 * @author Troy Boone
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief Lexical Analyzer to generate lexemes and tokens, and display them.
 *
 */
void lexicalAnalyzer();

bool isOperator(string input);  // Checks if string is an operator

bool isKeyword(string input);   // Checks if string is a keyword
/**
 * @brief Iterates through string and pulls out punctuation
 *
 * @param input unclean string
 * @return cleaned string
 */
string punctuatorFind(string input); // 

/**
 * @brief recursive-descent parser to check the syntax of the test program.
 *
 */
void topDownParser();
/**
 * @brief Takes the file location input and stores all the elements into a vector
 *
 * @param fileName the name of the file
 */
void readFile(string fileName);

// List of words broken up by the readFile
vector <string> wordList;
int main(int argc, char const* argv[]) {
    /* code */
    readFile("test1.txt");
    //tempTest();
    lexicalAnalyzer();
    return 0;
}

void lexicalAnalyzer() {
    string analyze;
    for (int i = 0; i < wordList.size() - 1; i++) {
        analyze = punctuatorFind(wordList[i]);
        if (isKeyword(analyze) == true) {
            cout << analyze << " is a keyword." << endl;
        }
        else if (isOperator(analyze) == true) {
            cout << analyze << " is an operator." << endl;
        }
        else if (isalpha(analyze[0])) {
            cout << analyze << " is an identifier." << endl;
        }
    }
}

bool isOperator(string input) {
    return (input == "+" || input == "-" || input == "/" || input == "%" || input == "*" || input == "=");
}

bool isKeyword(string input) {
    return ((input == "int") || (input == "string") || (input == "double") || (input == "bool") || (input == "float") || (input == "char"));
}

string punctuatorFind(string input) {
    for (int i = 0; i < input.size() - 1; i++) {
        if ((input[i] == '{') || (input[i] == '}') || (input[i] == '(') || (input[i] == ')') ||
            (input[i] == '&') || (input[i] == '|')) {
            cout << input[i] << " is a punctuator." << endl;
            input.erase(input.begin() + i);
        }
        return input;
    }
}

void topDownParser() {

}

void readFile(string fileName) {
    string line;
    ifstream myFile(fileName);
    if (myFile.is_open()) {
        while (getline(myFile, line, ' ')) {
            wordList.push_back(line);
        }
    }
    else {
        cout << "Unable to open file";
        exit(1);
    }
}

void tempTest() {
    for (int i = 0; i < wordList.size() - 1; i++) {
        cout << wordList[i] << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file