#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function to print the choices
void printChoices(char playerChoice, char computerChoice) {
    cout << "You chose: " << playerChoice << endl;
    cout << "Computer chose: " << computerChoice << endl;
}

// Function to determine the winner of a single round
// Returns 1 if player wins, -1 if computer wins, 0 for a tie
int determineRoundWinner(char playerChoice, char computerChoice) {
    if (playerChoice == computerChoice) {
        return 0; // Tie
    }
    else if ((playerChoice == 'r' && (computerChoice == 's' || computerChoice == 'l')) ||
        (playerChoice == 'p' && (computerChoice == 'r' || computerChoice == 'k')) ||
        (playerChoice == 's' && (computerChoice == 'p' || computerChoice == 'l')) ||
        (playerChoice == 'l' && (computerChoice == 'k' || computerChoice == 'p')) ||
        (playerChoice == 'k' && (computerChoice == 's' || computerChoice == 'r'))) {
        return 1; // Player wins
    }
    else {
        return -1; // Computer wins
    }
}

// Function to display the results after each round
void displayCurrentResults(int playerScore, int computerScore) {
    cout << "\nCurrent results:" << endl;
    cout << "Player score: " << playerScore << endl;
    cout << "Computer score: " << computerScore << endl;
}

// Function to display the final results
void displayFinalResults(int playerScore, int computerScore, const string& playerName) {
    cout << "\nGame over! Final results:" << endl;
    cout << "Player score: " << playerScore << endl;
    cout << "Computer score: " << computerScore << endl;

    if (playerScore > computerScore) {
        cout << "Congratulations! You win the game!" << endl;
    }
    else if (computerScore > playerScore) {
        cout << "Computer wins the game. Better luck next time!" << endl;
    }
    else {
        cout << "It's a tie game!" << endl;
    }

    // Save results to file
    ofstream outFile("game_results.txt", ios::app); // Append mode
    if (outFile.is_open()) {
        outFile << "Player Name: " << playerName << endl;
        outFile << "Player Score: " << playerScore << endl;
        outFile << "Computer Score: " << computerScore << endl;
        outFile << "---------------------------------\n";
        outFile.close();
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }
}

// Function to get the player's choice with validation
char getPlayerChoice() {
    char playerChoice;
    cout << "Enter your choice (r for Rock, p for Paper, s for Scissors, l for Lizard, k for Spock): ";
    while (true) {
        cin >> playerChoice;
        if (playerChoice == 'r' || playerChoice == 'p' || playerChoice == 's' || playerChoice == 'l' || playerChoice == 'k') {
            break;
        }
        else {
            cout << "Invalid choice. Please enter 'r', 'p', 's', 'l', or 'k': ";
        }
    }
    return playerChoice;
}

// Function to get the computer's choice randomly
char getComputerChoice() {
    char choices[] = { 'r', 'p', 's', 'l', 'k' };
    return choices[rand() % 5];
}

// Function to play a single round
void playRound(int& playerScore, int& computerScore, int round) {
    cout << "\nRound " << round << endl;

    // Get player and computer choices
    char playerChoice = getPlayerChoice();
    char computerChoice = getComputerChoice();

    // Print choices
    printChoices(playerChoice, computerChoice);

    // Determine the winner of the round
    int roundResult = determineRoundWinner(playerChoice, computerChoice);

    if (roundResult == 1) {
        cout << "You win this round!" << endl;
        playerScore++;
    }
    else if (roundResult == -1) {
        cout << "Computer wins this round!" << endl;
        computerScore++;
    }
    else {
        cout << "It's a tie!" << endl;
    }

    // Display current results after each round
    displayCurrentResults(playerScore, computerScore);
}

// Function to display player statistics
void displayPlayerStatistics(const string& playerName) {
    ifstream inFile("game_results.txt");
    if (inFile.is_open()) {
        string line;
        int gamesPlayed = 0;
        int totalPlayerScore = 0;
        int totalComputerScore = 0;

        while (getline(inFile, line)) {
            if (line.find("Player Name: " + playerName) != string::npos) {
                gamesPlayed++;
                getline(inFile, line);
                totalPlayerScore += stoi(line.substr(line.find_last_of(' ') + 1));
                getline(inFile, line);
                totalComputerScore += stoi(line.substr(line.find_last_of(' ') + 1));
            }
        }
        inFile.close();

        cout << "\nPlayer Statistics for " << playerName << ":" << endl;
        cout << "Games Played: " << gamesPlayed << endl;
        cout << "Total Player Score: " << totalPlayerScore << endl;
        cout << "Total Computer Score: " << totalComputerScore << endl;
    }
    else {
        cerr << "Unable to open file for reading." << endl;
    }
}

// Function to check if the player wants to play again
bool playAgain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    while (true) {
        cin >> choice;
        if (choice == 'y' || choice == 'n') {
            break;
        }
        else {
            cout << "Invalid choice. Please enter 'y' or 'n': ";
        }
    }
    return choice == 'y';
}

int main() {
    srand(static_cast<unsigned int>(time(NULL))); // Seed the random number generator with current time

    string playerName;
    cout << "Welcome to Rock-Paper-Scissors-Lizard-Spock!" << endl;
    cout << "Please enter your name: ";
    cin >> playerName;

    do {
        int numRounds;
        cout << "Hi " << playerName << "! How many rounds do you want to play? ";
        cin >> numRounds;

        int playerScore = 0;
        int computerScore = 0;

        // Play the specified number of rounds
        for (int round = 1; round <= numRounds; ++round) {
            playRound(playerScore, computerScore, round);
        }

        // Display overall results
        displayFinalResults(playerScore, computerScore, playerName);

        // Display player statistics
        displayPlayerStatistics(playerName);

    } while (playAgain());

    cout << "Thanks for playing! Goodbye!" << endl;

    return 0;
}
