#ifndef MAIN_H
#define MAIN_H

void startGame();

char* getRandomWord(char* sourceFileName);

void displayGameState();

char getGuess();

int checkGuess(char guess, char* word, char* guessedLetters, int* lives);

void addGuessedLetter(char guess, char* guessedLetters);

int ifLetterInWord(char* word, char letter);

int checkWin(char* word, char* guessedLetters);

void displayWin();

void displayLose();

#endif