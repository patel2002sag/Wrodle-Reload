/*--------------------------------------------
    Program 3: Wordle Reload
    CS 141, Spring 2022, UIC

    The objective of this game is to guess the randomly selected
    word within a given number of attempts. You can select either
    a three or five word board.
    At the conclusion of the game, stats will be displayed.
    Indicators will be given if characters of the user entered
    word are reflected in the guessed word.
        - If the character is in the correct position, the character
          will display as an uppercase value.
        - If the character is within the random word, the character
          will display as a lowercase value.
        - If you enter a character that is not in the word, an asterisk '*'
          will display.

    Course: CS 141, Spring 2022
    System: Windows and Mac using Visual Studio Code
    Author: Kathan Parikh, Sagar Patel
 ---------------------------------------------*/
 
#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
#include <cctype>     // Allows using the tolower() function
#include <ctime>      // Headed to set the random number seed to be the current time, Timer functions
using namespace std;  // don't need to preface cin and cout with std::


// This function displays the general directions of game, called in main() once with no parameters
void displayMessage() {
    cout << "Program 3: Wordle Reload\n";
    cout << "CS 141, Spring 2022, UIC\n";
    cout << endl;
    cout << "The objective of this game is to guess the randomly selected\n";
    cout << "word within a given number of attempts. You can select either\n";
    cout << "a three or five word board.\n";
    cout << "At the conlusion of the game, stats will be displayed.\n";
    cout << "Indicators will be given if characters of the user entered\n";
    cout << "word are reflected in the guessed word.\n";
    cout << "- If the character is in the correct position, the character\n";
    cout << "will display as an uppercase value.\n";
    cout << "- If the character is within the random word, the character\n";
    cout << "will display as a lowercase value.\n";
    cout << "- If you enter a character that is not in the word, an asterisk '*'\n";
    cout << "will display.\n";
    cout << endl;
}


// This function stores three letter and five letter words into their specified vector from wordleword file
// Receives three letter word and five letter word vectors as parameters. 
void readWordsIntoWordleWords(vector<string> & threeLetterWords, vector<string> &fiveLetterWords) {
    // Read in wordlewords into wordlewords vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "wordlewords.txt");      // Open wordlewords file
    assert( inStream.fail() == false );     // Ensure file open worked
    
    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    
    while(inStream >> newWord) {    
        if(newWord.length() == 3) {
            threeLetterWords.push_back( newWord);
        }
        //Appends the five letter word
        else if(newWord.length() == 5) {
            fiveLetterWords.push_back(newWord);
        }
    }
    // Close the wordlewords file
    inStream.close();
}


// This function searches word in their corresponding vectors using binary search and either returns -1 or returns its index. 
// It receives two paremeters: the search word and the vector of either three or five letter word.    
int binarySearchString(string searchWord, vector <string> fiveLetterOrThreeLetter) {
    //Variable Decleation
    int mid;
    int low;
    int high;
    
    // Initialize low and high variable
    low = 0;
    high = fiveLetterOrThreeLetter.size();
    
    //Write appropriate while condition below
    while (high >= low) {
        // Calculate the middle of low and high
        mid = (high + low) / 2;
        // Save the compared result between 1) the middle index element of dictionary and 2) searchWord
        int searchResult = searchWord.compare(fiveLetterOrThreeLetter[mid]);
        
        if (searchResult == 0) {
            return mid; 
        }
        else if (searchResult < 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return -1; // Not found
}


// This function returns a random word from either three letter or five letter word
// And receives three letter word or five letter word vectors as parameters.
string getRandomWord(vector <string> &threeOrFiveLetters ) {
    int randomIndex = rand() % threeOrFiveLetters.size();
    return threeOrFiveLetters.at(randomIndex);
}
  

// This function displays the prompt of menu option for user
void prompt () {
    cout << endl;
    cout << "Select a menu option: "<< endl;
    cout << "   1. To play Wordle Reload 3 letter play" << endl;
    cout << "   2. To play Wordle Reload 5 letter play" << endl;
    cout << "   3. Exit the program" << endl;
    cout << "Your choice --> ";
}


// This function saves the character of guess word into a string. 
// It receives three parameters user guessword, three letter word and savingcharacter string. 
void saveCharacters(string userGuessWord, string threeLetterWord, string& savingCharacters) {
    // For loop to store characters based on their conditions
    for(int i = 0; i < userGuessWord.length(); i++) {
        char guess_word_character = userGuessWord[i];

        if(userGuessWord[i] == threeLetterWord[i]) {
            userGuessWord[i] = toupper(userGuessWord[i]);   // Uppercase the character
            savingCharacters += userGuessWord[i];
        }
        else if ((threeLetterWord.find(guess_word_character) == 0) || (threeLetterWord.find(guess_word_character) == 1) || (threeLetterWord.find(guess_word_character) == 2)) {
            savingCharacters+=guess_word_character;         // Lowercase the character
        }
        else {
            savingCharacters+='*';                          // Else save *
        }
    }
}


// This function prints the characters of the guess word into brackets
// It receives savingcharacter string as parameter
void printSaveCharacters(string savingCharacters) {
    int counter = 0;    
    // For loop to format the printing of characters inside brackets                    
    for(int i = 0; i < savingCharacters.length(); i++) {
        if(counter % 3 == 0) {                              // Print new line and print characters inside brackets
            cout << endl;
            cout << "[ " << savingCharacters[i] << " ]" << "  "; 
        }
        else if(counter % 3 != 0) {                          // Print characters inside brackets
            cout << "[ " << savingCharacters[i] << " ]" << "  ";
        }
        counter++;
    }
}


// This function saves the character of guess word into a string. 
// It receives three parameters user guessword, five letter word and five letter savingcharacter string. 
void fiveLetterSaving(string userGuessWord, string fiveLetterWord, string& fiveLetterSavingCharacters) {
    // For loop to store characters based on their conditions
    for(int i = 0; i < userGuessWord.length(); i++) {
        char guess_word_character = userGuessWord[i];

        if(userGuessWord[i] == fiveLetterWord[i]) {
            userGuessWord[i] = toupper(userGuessWord[i]);       // Uppercase the character
            fiveLetterSavingCharacters += userGuessWord[i];
        }
        else if ((fiveLetterWord.find(guess_word_character) == 0) || (fiveLetterWord.find(guess_word_character) == 1) || (fiveLetterWord.find(guess_word_character) == 2)||(fiveLetterWord.find(guess_word_character) == 3)||(fiveLetterWord.find(guess_word_character) == 4)) {
            fiveLetterSavingCharacters += guess_word_character;   // Lowercase the character
        }
        else{
            fiveLetterSavingCharacters+='*';                    // Else save *
        }
    }
    
}


// This function prints the characters of the Guess Word into brackets
// It receives five letter saving character string as parameter
void printFiveLetterCharacters(string fiveLetterSavingCharacters) {
    // For loop to format the printing of characters inside brackets                    
    int counter = 0;                        
    for(int i = 0; i < fiveLetterSavingCharacters.length(); i++) {
        if(counter % 5 == 0) {                                   // Print new line and print characters inside brackets
            cout << endl;
            cout << "[ " << fiveLetterSavingCharacters[i] << " ]" << "  "; 
        }
        else if(counter % 5 != 0) {                              // Print characters inside brackets
            cout << "[ " << fiveLetterSavingCharacters[i] << " ]" << "  ";
        }
        counter++;
    }
}


// This function runs when user selects to play the three letter word game. 
// It receives streak counter, total guess word count, average word completime time, elapsed seconds, starttime,
// Three letter word, five letter word vector, and one word correct as parameters  
bool threeLetterWordle(int& streakCounter, int& totalGuessCount, int& averageWordCompletionTime, int& elapsedSeconds, time_t& startTime, vector<string> &threeLetterWords, vector <int>& streakCountSaving, bool &oneWordCorrect) {
    // Intial Variable Decleration 
    vector <string> wordlewords;
    int wordIndex;
    string threeLetterWord;
    string userGuessWord;
    string savingCharacters = "";
    int attempts = 4;
    threeLetterWord = getRandomWord(threeLetterWords);
    cout << endl; 

    // Prints the three letter word message
    cout << "To get started, enter your first 3 letter word.\n";
    cout << "You have 4 attempts to guess the random word.\n";
    cout << "The timer will start after your first word entry.\n";
    cout << "Try to guess the word within 20 seconds.\n";
    
    // While loop runs when attemtps are more than zero
    while(attempts > 0) {
        // Ask for user Word
        cout << endl;
        cout << endl;
        cout << "Please enter word --> ";
        cin >> userGuessWord;
        cout << endl;
        
        // Turn guess word into lower case
        for(int i = 0; i < userGuessWord.length(); i++) {
            userGuessWord[i] = tolower(userGuessWord[i]);
        }
        
        // Check if the word is valid
        int result = binarySearchString(userGuessWord, threeLetterWords);

        // Checks if the word is in the dictionary
        if(result != -1) {
            if(attempts == 4) {
                startTime = time(NULL);
            }
            attempts --;

            // Checks if the user words is equal to three letter word, display message and stats
            if (userGuessWord == threeLetterWord) {
                saveCharacters(userGuessWord, threeLetterWord, savingCharacters);
                printSaveCharacters(savingCharacters);
                cout << endl;
                cout << endl;
                cout << "Nice Work!  You guessed the correct word" << endl;
                cout << "  - You completed the board in: "<< elapsedSeconds << " seconds." << endl;
                cout << "  - It took you " << 4 - (attempts) << "/4 attempts." << endl;
                cout << endl;
                totalGuessCount++;
                streakCounter++;
                streakCountSaving.push_back(streakCounter);
                oneWordCorrect = true;
                return true;
            }
            // Checks if guess word doesn't equal three letter word then saves and prints the chracters
            else if(userGuessWord != threeLetterWord) {
                saveCharacters(userGuessWord, threeLetterWord, savingCharacters);
                printSaveCharacters(savingCharacters);
            }
            // Takes the difference of current time and start time
            elapsedSeconds = difftime(time( NULL), startTime);
        
        }
        // Prints invalid word when length of guess word is not equal to three
        else if((userGuessWord != threeLetterWord) && (userGuessWord.length() != 3)) {
            cout << "Invalid word entry - please enter a word that is 3 characters long." << endl;
        }
        // Prints not playable word when guess word is not in file 
        else {
            cout << endl;
            cout << "Not a playable word, please select another word." << endl;
        }

        // Checks if attempts is equal to zero and elapsesedconds are less than 20
        // Then prints Maximum amount of attempts have been reached
        if((attempts == 0) && (elapsedSeconds < 20)) {
            streakCounter = 0;
            streakCountSaving.push_back(streakCounter);
            cout << endl;
            cout << endl;
            cout << "Maximum amount of attempts have been reached. Try again." << endl;
        }
        
        // Checks if attempts are equal to 0 and elpased seconds are less than 20
        // Then prints time has expired
        else if((attempts == 0) && (elapsedSeconds > 20)) {
            streakCounter = 0;
            streakCountSaving.push_back(streakCounter);
            cout << endl;
            cout << endl;
            cout << "Your time has expired.  Try again." << endl;
            cout << "  - You are "<< elapsedSeconds - 20 << " seconds over the 20 second time limit." << endl;
        }
    } // End of while loop
}


// This function runs when user selects to play the three letter word game. 
// It receives streak counter, total guess word count, average word completime time, elapsed seconds, starttime,
// Three letter word, five letter word vector, and one word correct as parameters 
bool fiveLetterWordle(int& streakCounter, int& totalGuessCount, int& averageWordCompletionTime, int& elapsedSeconds, time_t& startTime,  vector<string> &fiveLetterWords, vector <int>& streakCountSaving, bool &oneWordCorrect) {
    // Intial Variable Decleration 
    vector <string> wordlewords;
    int wordIndex;
    string fiveLetterWord;
    string userGuessWord = "";
    string fiveLetterSavingCharacters = "";
    int attempts = 6;
    fiveLetterWord = getRandomWord(fiveLetterWords);
    
    // Prints the five letter word message
    cout << endl;
    cout << "To get started, enter your first 5 letter word.\n";
    cout << "You have 6 attempts to guess the random word.\n";
    cout << "The timer will start after your first word entry.\n";
    cout << "Try to guess the word within 40 seconds.\n";
   
   // While loop runs when attemtps are more than zero
    while(attempts > 0) {
        // Ask for user Word
        cout << endl;
        cout << "Please enter word --> ";
        cin >> userGuessWord;

        // Turn guess word into lower case
        for(int i = 0; i < userGuessWord.length(); i++) {
            userGuessWord[i] = tolower(userGuessWord[i]);
        }
        
        // Check if the word is valid
        int result = binarySearchString(userGuessWord, fiveLetterWords);
        
        //Checks if the word is in file 
        if(result != -1) {
            //Start the timer if attempts is equal to 6
            if(attempts == 6) {
                startTime = time(NULL);
            }
            attempts --; 
            
            // Checks if the user words is equal to three letter word, display message and stats
            if (userGuessWord == fiveLetterWord) {
                fiveLetterSaving(userGuessWord, fiveLetterWord, fiveLetterSavingCharacters);
                printFiveLetterCharacters(fiveLetterSavingCharacters);
                cout << endl;
                cout << endl;
                cout << "Nice Work!  You guessed the correct word" << endl;
                cout << "  -You completed the board in: "<< elapsedSeconds << " seconds." << endl;
                cout << "  -It took you " << 6 - (attempts) << "/6 attempts." << endl;
                cout << endl;
                totalGuessCount++;
                streakCounter++;
                streakCountSaving.push_back(streakCounter);
                oneWordCorrect = true;
                return true;
            }
            
            // Checks if guess word doesn't equal three letter word then saves and prints the chracters
            else if(userGuessWord != fiveLetterWord) {
                fiveLetterSaving(userGuessWord, fiveLetterWord, fiveLetterSavingCharacters);
                printFiveLetterCharacters(fiveLetterSavingCharacters);
            }
            
            // Takes the difference of current time and start time
            elapsedSeconds = difftime(time( NULL), startTime);
        } 

        // Prints invalid word when length of guess word is not equal to five
        else if((userGuessWord != fiveLetterWord) && (userGuessWord.length() != 5)) {
            cout << "Invalid word entry - please enter a word that is 5 characters long." << endl;
     
        }
        
        // Prints not playable word when guess word is not in file 
        else {
            cout << endl;
            cout << "Not a playable word, please select another word." << endl;
        }
        
        // Checks if attempts is equal to zero and elapsesedconds are less than 20
        // Then prints Maximum amount of attempts have been reached
        if((attempts == 0) && (elapsedSeconds < 40)) {
            streakCounter  = 0;
            streakCountSaving.push_back(streakCounter);
            cout << endl;
            cout << endl;
            cout << "Maximum amount of attempts have been reached. Try again." << endl;
        }
        
        // Checks if attempts are equal to 0 and elpased seconds are less than 20
        // Then prints time has expired
        else if((attempts == 0) && (elapsedSeconds > 40)) {
            streakCounter = 0; 
            streakCountSaving.push_back(streakCounter);
            cout << endl;

            cout << endl;
            cout << "Your time has expired.  Try again." << endl;
            cout << "  - You are "<< elapsedSeconds - 40 << " seconds over the 40 second time limit." << endl;
        }
    } // End while loop
} 


// Main function that defines the necessary game variables, reads the file, sets the seed to 1, runs a loop and 
// Calls functions determined by the selected menu option to play the game. Returns 0 to successfully execute the program
int main()
{
    // Calls the displayMessage function
    displayMessage();
    
    // Defines the necessary game variables to execute program and display stats properly
    int menu_option;
    int streakCounter = 0;
    int totalGuessCount = 0;
    int elapsedSeconds = 0;
    int averageWordCompletionTime = 0;
    string overTime = "N/A";
    time_t startTime = time(NULL);
    vector <string> threeLetterWords;
    vector <string> fiveLetterWords;
    vector <int> streakCountSaving;
    bool oneWordCorrect = false;
    
    // Calls this function and reads word from worldewords to save specifed length words into their specified vectors
    readWordsIntoWordleWords(threeLetterWords, fiveLetterWords);
    
    // Sets the seed of srand to 1
    srand(1);
    
    while(true) {
        prompt();
        cin >> menu_option;
        
        // if user select 3 as menu option, display overall stats and exiting program
        if(menu_option == 3) {
            cout << endl;
            cout << "Overall Stats: " << endl;
            cout << "  - You guessed: "<< totalGuessCount << endl;
            int max_number = 0;
            for(int i = 0; i < streakCountSaving.size(); i++) {
                if(max_number < streakCountSaving.at(i)){
                    max_number = streakCountSaving.at(i);
                }
            }
            cout << "  - Your longest streak is: "<< max_number << endl; 
            if((totalGuessCount != 0) && (oneWordCorrect)) {
                cout <<  "  - Average word completion time: " << (elapsedSeconds/totalGuessCount) << endl;   
            }
            else {
                cout <<  "  - Average word completion time: N/A" << endl;
            }
            cout << "Exiting program" << endl; 
            cout << endl;   
            break;
        }

        // if user selects 2 call the fiveLetterWordle function and pass necessary defined arguments to execute it successfully
        else if(menu_option == 2) {
            fiveLetterWordle(streakCounter, totalGuessCount, averageWordCompletionTime, elapsedSeconds, startTime, fiveLetterWords, streakCountSaving, oneWordCorrect);

        }
        // if user selects 1 call the threeLetterWordle function and pass necessary defined arguments to execute it successfully
        else if(menu_option == 1) {
            threeLetterWordle(streakCounter, totalGuessCount, averageWordCompletionTime, elapsedSeconds, startTime, threeLetterWords, streakCountSaving, oneWordCorrect);
                
        }
    }
    
    return 0; // Successfully executes the program
}