/**
 * @brief We will input a file, identify the substrings and find all syntax errors
 * @author Stephen Whitley
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
/**
 * @brief Checks if string is an operator
 * @return true if *, /, +, -, =, %
 */
bool isOperator(string input);
/**
 * @brief Checks if string is a keyword
 * @return true if it is a primitive type
 */
bool isKeyword(string input);
/**
 * @brief Checks if char is punctuation
 * @return true
 */
bool isPunctuation(char i);
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

void tempTest();

// List of words broken up by the readFile
vector <string> wordList;

vector<string> idents;
int main(int argc, char const* argv[]) {
    /* code */
    readFile("test1.txt");
    // tempTest();
    lexicalAnalyzer();
    return 0;
}

void lexicalAnalyzer() {
    string analyze;
    for (int i = 0; i < wordList.size() - 1; i++) {
        analyze = wordList[i];
        if (isKeyword(analyze)) {
            cout << analyze << " is a keyword." << endl;
            //triggers keyword flag

        }
        else if (isOperator(analyze)) {
            cout << analyze << " is an operator." << endl;
        }
        else if (isPunctuation(analyze[0])) {
            cout << analyze << " is a punctuator." << endl;
        }
        else if (isalpha(analyze[0])) {
            cout << analyze << " is an identifier." << endl;
            //if followed after keyword, add to ident. If not followed by keyword, check if in ident list. if not in ident list, error
            //triggers ident flag
        }
    }
}

bool isOperator(string input) {
    return ((input == "+") || (input == "-") || (input == "/") || (input == "%") || (input == "*") || (input == "="));
}

bool isKeyword(string input) {
    return ((input == "int") || (input == "string") || (input == "double") || (input == "bool") || (input == "float") || (input == "char"));
}
bool isPunctuation(char i) {
    return ((i == '{') || (i == '}') || (i == '(') || (i == ')') ||
        (i == '&') || (i == '|') || (i == ';'));
}

void topDownParser() {

}

void readFile(string fileName) {
    string line;
    vector<int> position;
    ifstream myFile(fileName);
    if (myFile.is_open()) {
        while (getline(myFile, line, ' ')) {
            int i = 0;
            int newLinePos = line.find("\n");
            if (newLinePos != string::npos) {
                line.erase(newLinePos, 1);
            }
            while (i < line.size()) {
                if (isPunctuation(line[i]) && i == 0) {
                    wordList.push_back(line.substr(0, 1));
                    line.erase(0, 1);
                }
                else if (isPunctuation(line[i])) {
                    wordList.push_back(line.substr(0, i));
                    line.erase(0, i);
                    i = 0;
                }
                else {
                    i++;
                }
            }
            if (line.length() != 0) {
                wordList.push_back(line);
            }

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