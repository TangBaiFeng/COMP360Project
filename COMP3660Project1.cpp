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
#include <algorithm>
#include <map>

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
/**
 * @brief Prints out a syntax error if the top-down parser detects a problem within the EBNF
 *
 * @param errorMessage from topDownParser()
 */
void error(string errorMessage);

// Name of the file that the user inputs
string fileName;

// List of words broken up by the readFile
vector <string> wordList;

// Stores a list of indentifiers
vector<string> idents;

// Stores each type of token in an enumerator
enum Lexume { Keyword, Operator, Punctuator, Identifier };
map<int, pair<Lexume, string>> lexicalReturn;
int main() {
    /* code */
    cout << "Input file name (Example.txt):";
    cin >> fileName;
    readFile(fileName);
    lexicalAnalyzer();
    topDownParser();
    return 0;
}

void lexicalAnalyzer() {
    string analyze;
    for (int i = 0; i < wordList.size(); i++) { // Loop that goes through the entire wordList.
        analyze = wordList[i];
        if (isKeyword(analyze)) {   // The process of determining what category each token from the wordList goes into.
            cout << analyze << "  -> " << "Keyword" << endl;
            lexicalReturn.insert(pair<int, pair<Lexume, string>>(i, pair<Lexume, string>(Keyword, analyze)));
        }
        else if (isOperator(analyze)) {
            cout << analyze << "    -> " << "Operator" << endl;
            lexicalReturn.insert(pair<int, pair<Lexume, string>>(i, pair<Lexume, string>(Operator, analyze)));
        }
        else if (isPunctuation(analyze[0])) {
            cout << analyze << "    -> " << "Punctuator" << endl;
            lexicalReturn.insert(pair<int, pair<Lexume, string>>(i, pair<Lexume, string>(Punctuator, analyze)));
        }
        else if (isalpha(analyze[0])) {
            cout << analyze << "    -> " << "Identifier" << endl;
            lexicalReturn.insert(pair<int, pair<Lexume, string>>(i, pair<Lexume, string>(Identifier, analyze)));
        }
    }
}

void topDownParser() {
    //Program start
    //Determines whether or not the function is valid based off the EBNF Grammar provided in the sample demo.
    string compare = "(";
    if (lexicalReturn.at(0).first != Keyword) error(lexicalReturn.at(0).second);
    if (lexicalReturn.at(1).first != Identifier) {
        error(lexicalReturn.at(1).second);
    }
    else {
        idents.push_back(lexicalReturn.at(1).second);
    }
    if (lexicalReturn.at(2).second != "(") error(lexicalReturn.at(2).second);    
    if (lexicalReturn.at(3).first != Keyword) error(lexicalReturn.at(3).second);
    if (lexicalReturn.at(4).first != Identifier) {
        error(lexicalReturn.at(4).second);
    }
    else {
        idents.push_back(lexicalReturn.at(4).second);
    }    if (lexicalReturn.at(5).second != ")") error(lexicalReturn.at(5).second);
    if (lexicalReturn.at(6).second != "{") error(lexicalReturn.at(6).second);

    bool declare = true;
    bool expr = true;
    int counter = 7;

    while (declare) {   // Checks if all initialized variables are valid. 
                        // Ends if there are no more variables intialized ahead
        if (lexicalReturn.at(counter).first != Keyword) error(lexicalReturn.at(counter).second);
        if (lexicalReturn.at(counter + 1).first != Identifier) {
            error(lexicalReturn.at(counter + 1).second);
        }
        else {
            idents.push_back(lexicalReturn.at(counter + 1).second);
        }
        if (lexicalReturn.at(counter + 2).second != ";") error(lexicalReturn.at(counter + 2).second);

        if (lexicalReturn.at(counter + 3).first != Keyword) declare = false;
        counter += 3;

    }
    if (lexicalReturn.at(counter).first != Identifier) {
        error(lexicalReturn.at(counter).second);
    }
    else {
        if (find(idents.begin(), idents.end(), lexicalReturn.at(counter).second) == idents.end()) {
            error(lexicalReturn.at(counter).second);
        }
    }
    counter++;
    if (lexicalReturn.at(counter).first != Operator) error(lexicalReturn.at(counter).second);
    counter++;

    while (expr) {
        if (lexicalReturn.at(counter).first != Identifier) {
            error(lexicalReturn.at(counter).second);
        }
        else {
            if (find(idents.begin(), idents.end(), lexicalReturn.at(counter).second) == idents.end()) {
                error(lexicalReturn.at(counter).second);
            }
        }
        if (lexicalReturn.at(counter + 1).first != Operator) {
            expr = false;
            counter++;
        }
        else {
            counter += 2;
        }

    }
    if (lexicalReturn.at(counter).second != ";") error(lexicalReturn.at(counter).second);
    counter++;
    if (lexicalReturn.at(counter).second != "}") error(lexicalReturn.at(counter).second);
    // Prints that the test program functions according to the demo ENBF grammar.
    cout << "The test program is generated by the BNF grammar" << endl;
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

void error(string errorString) {
    cout << "The test program cannot be generated by the Simple Demo Function BNF Grammar" << endl;
    cout << errorString << " Is improper" << endl;
    exit(1);
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