#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_LETTERS 26
#define MAX_WORD_SIZE 32
#define SPACE ' '
#define STARTING_LIVES 5

void startGame(char* wordsFileName);

char* getRandomWord(char* sourceFileName);

int getNumberOfLinesInFile(FILE* sourceFile);

void deleteNewLine(char** pChosenWord);

void makeWordLowerCase(char** pChosenWord);

int checkGuess(char guess, char* word, char* guessedLetters, int* guessedLettersIndex);

void displayGameState(char* word, char* guessedLetters, int* guessedLettersIndex, int lives);

void clearConsole();

char getGuess();

void addGuessedLetter(char guess, char* guessedLetters, int* guessedLettersIndex);

int ifLetterInWord(char* word, char letter);

int ifLetterAlreadyGuessed(char letter, char* guessedLetters, int* guessedLettersIndex);

int checkWin(char* word, char* guessedLetters, int* guessedLettersIndex);

void displayWin();

void displayLose();

#endif