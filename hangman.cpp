#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class HangmanGame {
public:
    HangmanGame() {
        srand(time(nullptr));
        words = {"apple", "banana", "cherry", "grape", "orange"};
        selectedWord = words[rand() % words.size()];
        remainingAttempts = 6;
        guessedLetters = std::vector<bool>(selectedWord.length(), false);
    }

    void displayWord() {
        for (size_t i = 0; i < selectedWord.length(); ++i) {
            if (guessedLetters[i]) {
                std::cout << selectedWord[i] << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }

    void play() {
        std::string guessedWord;
        while (remainingAttempts > 0) {
            std::cout << "\nHangman Game\n" << std::endl;
            displayWord();
            std::cout << "Guess a letter: ";
            std::cin >> guessedWord;

            if (guessedWord.length() != 1 || !isalpha(guessedWord[0])) {
                std::cout << "Invalid input. Please enter a single letter." << std::endl;
                continue;
            }

            char guessedLetter = tolower(guessedWord[0]);
            if (guessedLetters[guessedLetter - 'a']) {
                std::cout << "You already guessed that letter." << std::endl;
                continue;
            }

            bool correctGuess = false;
            for (size_t i = 0; i < selectedWord.length(); ++i) {
                if (selectedWord[i] == guessedLetter) {
                    guessedLetters[i] = true;
                    correctGuess = true;
                }
            }

            if (!correctGuess) {
                --remainingAttempts;
                std::cout << "Incorrect guess! " << remainingAttempts << " attempts remaining." << std::endl;
            }

            if (std::all_of(guessedLetters.begin(), guessedLetters.end(), [](bool letter) { return letter; })) {
                std::cout << "\nCongratulations! You guessed the word: " << selectedWord << std::endl;
                break;
            }
        }

        if (remainingAttempts == 0) {
            std::cout << "\nGame Over. The word was: " << selectedWord << std::endl;
        }
    }

private:
    std::vector<std::string> words;
    std::string selectedWord;
    int remainingAttempts;
    std::vector<bool> guessedLetters;
};

int main() {
    HangmanGame game;
    game.play();
    return 0;
}
