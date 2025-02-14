#include <fstream>
#include <iostream>
#include <vector>
#include <string>
//#include <windows.h>

using namespace std;

//void setConsoleColor(int textColor, int backgroundColor) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
//}


class FileManager {
private:
    fstream inputFile; // File stream for reading from the file

public:
    // Constructor that opens the specified file for reading
    FileManager(const string& filename) {
        inputFile.open(filename, ios::in);
        if (!inputFile.is_open()) {
            cerr << "Error in opening file: " << filename << endl;
        } else {
            cout << "File opened successfully: " << filename << endl;
        }
    }

    // Destructor to close the file if it's open
    ~FileManager() {
        if (inputFile.is_open()) {
            inputFile.close();
        }
    }

    // Read all words from the file and return them as a vector
    vector<string> readWords() {
        vector<string> words;
        string word;
        while (inputFile >> word) {
            words.push_back(word);
        }
        return words;
    }

    // Read all lines from the file and return them as a vector
    vector<string> readLines() {
        vector<string> lines;
        string line;
        inputFile.clear(); // Clear any error flags
        inputFile.seekg(0); // Reset the file pointer to the beginning
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        return lines;
    }
};




class UserHandler {
private:
    vector<string> words; // Store words read from the file
    vector<string> lines; // Store lines read from the file
    int choice; // User's choice for output type

public:
    // Constructor that reads words and lines from the FileManager
    UserHandler(FileManager& fm) {
        words = fm.readWords();
        lines = fm.readLines();
    }

    // Generate output based on user choice
    vector<string> RandomWordGenerator() {
        cout << "Choose 1 for words, and 2 for lines: ";
        cin >> choice;

        if (choice == 1) {
            return words; // Return words if user chooses 1
        } else if (choice == 2) {
            return lines; // Return lines if user chooses 2
        } else {
            cout << "Invalid choice. Returning empty vector." << endl;
            return {}; // Return an empty vector for invalid choice
        }
    }
};




int main() {
	
//	setConsoleColor(12, 15); 
	
    FileManager fm("word.txt"); // Create a FileManager to handle the file
    UserHandler UH(fm); // Create a UserHandler to manage user interactions

    vector<string> result = UH.RandomWordGenerator(); // Get user-selected data

    // Print the result to the console
    for (const auto& item : result) {
        cout << item << endl; // Output each word or line
    }
    cout << "Working so far!" << endl;

    return 0; // Exit the program successfully
}