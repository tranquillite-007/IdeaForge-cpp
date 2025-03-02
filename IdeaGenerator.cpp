#include <fstream> // For FileHandling
#include <iostream>// For I/O
#include <vector>  // For <vector>
#include <string>  // For substr()
#include <sstream> // for stringStream
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time() 
#include <thread>  // For this_thread::sleep_for
#include <chrono>  // For chrono::milliseconds
#include <iomanip> // For setw

using namespace std;

// Class to handle file input and output
class FileManager {
private:
    fstream inputFile; 
    string line;

public:
    // Constructor that opens the specified file for reading
    FileManager(const string& filename) {
        inputFile.open(filename, ios::in);
        if (!inputFile.is_open()) {
            cerr << "Error in opening file: " << filename << " --Make sure the file is in the same folder and the name is word.txt" << endl;
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

    // Function to extract all categories from inputFile
    vector<string> extractCategoryName() {
        vector<string> catItems;                                                            // catItems to store categories which are started with #
        while (getline(inputFile, line)) {
            if (!line.empty() && line[0] == '#') {
                string item = line.substr(1);
                catItems.push_back(item);
            }
        }
        return catItems;
    }

    // Function to extract values for a specific category
    vector<string> extractValuesForCategory(const string& category) {
        vector<string> values;                                                                     // values vector to store words in each category
        inputFile.clear();
        inputFile.seekg(0);
        bool foundCategory = false;

        while (getline(inputFile, line)) {
            if (line == "#" + category) {
                foundCategory = true; 
                getline(inputFile, line); 
                if (line.front() == '(' && line.back() == ')') {
                    // Extract values between parentheses
                    stringstream ss(line.substr(1, line.size() - 2));
                    string value; // value variable to store word
                    while (getline(ss, value, ',')) {
                        values.push_back(value);
                    }
                }
                break; 
				// Exit after finding the category
            }
        }
        return values;
    }
};

// Class to handle user input and display output
class UserHandler {
private:
    FileManager fm; 
    vector<string> catItems; 
    int choiceCount, id;
    vector<int> choosenVector; 
    vector<vector<string>> values;                                                           // To store values for each chosen category

public:
    // Constructor to initialize FileManager and extract categories
    UserHandler(const string& filename) : fm(filename) {
        catItems = fm.extractCategoryName(); 
    }
    
    void displayAvailableCategories() {
        cout << "Available Categories:" << endl;
        for (size_t i = 0; i < catItems.size(); ++i) {
            cout << "[" << i << "] " << catItems[i] << endl;
        }
    }

    void createChoiceVector() {
        cout << "Enter number of Categories need to forge Idea: \n";
        cin >> choiceCount;

        if (choiceCount <= catItems.size()) { 
            cout << "Enter IDs of all " << choiceCount << " categories (0 to " << catItems.size() - 1 << "): \n";
            for (int i = 0; i < choiceCount; i++) {
                cin >> id;
                if (id >= 0 && id < catItems.size()) { 
                    choosenVector.push_back(id);
                    
                    // Extract values for the chosen category
                    vector<string> categoryValues = fm.extractValuesForCategory(catItems[id]);
                    values.push_back(categoryValues);
                } else {
                    cout << "Invalid ID: " << id << ". Please enter a valid ID." << endl;
                    i--; 
                }
            }
        } else {
            cout << "Invalid Value: --Given number is greater than total categories available" << endl;
        }
    }
    
    void displaySelectedCategories() {
        cout << "Selected categories are: \n";
        for (size_t i = 0; i < choosenVector.size(); ++i) {
            cout << "[" << choosenVector[i] << "] " << catItems[choosenVector[i]] << endl; 
        }
    }

    vector<vector<string>> getValues() {
        return values; 
    }

    vector<int> getChosenVector() {
        return choosenVector; 
    }

    vector<string> getCategoryNames() {
        return catItems; 
    }

    void reset() {
        choosenVector.clear();
        values.clear();
    }
};

// Class to handle random word generation
class RandomWordGenerator {
private:
    UserHandler& userHandler;

public:
    RandomWordGenerator(UserHandler& uh) : userHandler(uh) {
        srand(static_cast<unsigned int>(time(0)));                                  // Seed for random number generation
    }

    void generateRandomWords() {
        int numWords;
        cout << "Enter the number of words to generate from each category (max 5): ";
        cin >> numWords;

        if (numWords > 5) {
            cout << "Maximum number of words is 5. Setting to 5." << endl;
            numWords = 5;
        }

        vector<vector<string>> values = userHandler.getValues();
        vector<int> chosenVector = userHandler.getChosenVector();
        vector<string> catItems = userHandler.getCategoryNames(); 


        // Loading animation
        cout << "Generating random words";
        const char spinner[] = {'|', '/', '-', '\\'};
        for (int i = 0; i < 20; ++i) { 
            cout << "\r" << "Generating random words " << spinner[i % 4] << flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));                             // Delay for 200 milliseconds
        }
        cout << endl;

        // Delay before printing the random words
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));                                // Additional delay of 1 second

        // Print the table header
        cout << "+----------------+----------------+" << endl;
        cout << "| Category       | Random Word    |" << endl;
        cout << "+----------------+----------------+" << endl;

        // Store generated words for the table
        for (size_t i = 0; i < chosenVector.size(); ++i) {
            cout << "| " << left << setw(14) << catItems[chosenVector[i]];

            for (int j = 0; j < numWords; ++j) {
                if (j < values[i].size()) { 
                    int randomIndex = rand() % values[i].size(); 
                    cout << "| " << left << setw(14) << values[i][randomIndex];
                    if (j < numWords - 1) {
                        cout << endl << "| " << left << setw(14) << "";
                    }
                }
            }
            cout << endl << "+----------------+----------------+" << endl; 
        }
    }
};

int main() {
    string filename = "word.txt";
    char userChoice;

    do {
        UserHandler uh(filename); 

        // Display all available categories in the wordFile
        uh.displayAvailableCategories();

        // Take user input to create a vector of the chosen categories
        uh.createChoiceVector();
        
        // Display selected categories
        uh.displaySelectedCategories();

        // Create an instance of RandomWordGenerator and generate random words
        RandomWordGenerator rwg(uh);
        rwg.generateRandomWords();

        // Ask user if they want to recreate
        cout << "Do you want to recreate? Press 'O' for Yes or 'X' for No: ";
        cin >> userChoice;

        // Validate user input
        while (userChoice != 'o' && userChoice != 'x') {
            cout << "Invalid input. Please press 'O' for Yes or 'X' for No: ";
            cin >> userChoice;
        }

        // Reset UserHandler for the next iteration
        uh.reset();

    } while (userChoice == 'o');

    cout << "Exiting the program. Goodbye!" << endl;
    return 0;
}