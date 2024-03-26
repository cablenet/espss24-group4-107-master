//--------------------------------------------------------------------------------------------------------------------- 
// <a1.c> 
// 
// < In Hangman there are at least two players where one thinks of a word
// and the other(s) try to guess it by suggesting letters.
// The player(s) only have a limited number of available guesses. 
// When the player(s) do not have any guesses left, 
// they loose the game and win if the word was found before that.> 
// 
// Group: <Group 07> 
// 
// Name: <Mohsen Al Hemyari>
//
// Author: <01435764> 
//--------------------------------------------------------------------------------------------------------------------- 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 19
#define MAX_ATTEMPTS 5

// Function prototypes
void getWord(char word[], int *wordLength);
void playGame(char word[], int wordLength);
int containsLetter(char letter, char guessedLetters[]);
void displayWordState(char word[], char guessedLetters[], int wordLength);
int isWordGuessed(char word[], char guessedLetters[], int wordLength);

// Main function
int main(void) {
    char word[MAX_WORD_LENGTH + 1];
    int wordLength;

    getWord(word, &wordLength);
    playGame(word, wordLength);

    return 0;
}

// Function to get the word from the user
void getWord(char word[], int *wordLength) {
    printf("Word to look for: ");
    if (fgets(word, MAX_WORD_LENGTH + 1, stdin) == NULL) {
        printf("Error reading word.\n");
        word[0] = '\0';
        *wordLength = 0;
        return;
    }
    word[strcspn(word, "\n")] = '\0'; 
    *wordLength = strlen(word); 
}

// Function to play the Hangman game
void playGame(char word[], int wordLength) {
    char guessedLetters[26] = {0};
    int attempts = MAX_ATTEMPTS;
    int wordGuessed = 0;
    char inputStr[100];

    while (attempts > 0 && !wordGuessed) {
        printf("Attempts left: %d\n", attempts);
        printf("Enter a letter: ");

        if (fgets(inputStr, sizeof(inputStr), stdin) == NULL) {
            printf("Error or EOF detected.\n");
            break;
        }

        char input = toupper(inputStr[0]);

        if (!isalpha(input)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        if (containsLetter(input, guessedLetters)) {
            printf("Letter %c was used already!\n", input);
            continue;
        }

        guessedLetters[input - 'A'] = 1;

        int letterFound = 0;
        for (int i = 0; i < wordLength; i++) {
            if (toupper(word[i]) == input) {
                letterFound = 1;
                break; // Stop searching once the letter is found
            }
        }
        displayWordState(word, guessedLetters, wordLength);

        if (!letterFound) {
            attempts--;
        }

        wordGuessed = isWordGuessed(word, guessedLetters, wordLength);
    }

    if (wordGuessed) {
        printf("Congratulations, you won!\n");
    } else {
        printf("LOST! The Word was %s\n", word);
    }
}

// Function to check if a letter has been guessed
int containsLetter(char letter, char guessedLetters[]) {
    return guessedLetters[letter - 'A'];
}

// Function to display the current state of the word
void displayWordState(char word[], char guessedLetters[], int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        char letter = toupper(word[i]);
        if (containsLetter(letter, guessedLetters)) {
            printf("%c ", word[i]); 
        } else {
            printf("_ "); 
        }
    }
    printf("\n");
}

// Function to check if the word is fully guessed
int isWordGuessed(char word[], char guessedLetters[], int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (!containsLetter(toupper(word[i]), guessedLetters)) {
            return 0;
        }
    }
    return 0;
}

