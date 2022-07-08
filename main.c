#include "main.h"

void startGame(char* wordsFileName)
{
    char* word = getRandomWord(wordsFileName);
    char* guessedLetters = malloc(NUM_OF_LETTERS * sizeof(char));
    size_t guessedLettersIndex = 0;
    int lives = STARTING_LIVES;
    
    while (lives > 0)
    {
        clearConsole();
        displayGameState(word, guessedLetters, &guessedLettersIndex, lives);
        char guess = getGuess();
        if (checkGuess(guess, word, guessedLetters, &guessedLettersIndex))
        {
            addGuessedLetter(guess, guessedLetters, &guessedLettersIndex);
            if (checkWin(word, guessedLetters, &guessedLettersIndex))
            {
                clearConsole();
                printf("The word was %s!\n", word);
                displayWin();
                exit(0);
            }         
        }
        else
        {
            lives--;
        }        
    }
    clearConsole();
    printf("The word was %s!\n", word);
    displayLose();
    exit(-1);
}

char* getRandomWord(char* sourceFileName)
{
    FILE* wordsFile = fopen(sourceFileName,"r");
    srand(time(NULL));  
    int randomNum = rand() % getNumberOfLinesInFile(wordsFile);
    char* chosenWord = malloc(MAX_WORD_SIZE * sizeof(char));

    for (size_t i = 0; i < randomNum; i++)
    {
        fgets(chosenWord, "%s", wordsFile);
    }

    deleteNewLine(&chosenWord);

    makeWordLowerCase(&chosenWord);

    fclose(wordsFile);

    return chosenWord;
}

void deleteNewLine(char** pChosenWord)
{
    int len = strlen(*pChosenWord);
    (*pChosenWord)[len-1] = 0;
}

void makeWordLowerCase(char** pChosenWord)
{
    size_t wordIndex = 0;
    while ((*pChosenWord)[wordIndex])
    {
        (*pChosenWord)[wordIndex] = tolower((*pChosenWord)[wordIndex]);
        wordIndex++;
    }
}

int getNumberOfLinesInFile(FILE* sourceFile)
{
    size_t lineCount = 1;
    
    for (char c = getc(sourceFile); c != EOF; c = getc(sourceFile))
    {
        if (c == '\n')
        {
            lineCount++;
        }
    }
    rewind(sourceFile);

    return lineCount;
}

void displayGameState(char* word, char* guessedLetters, int* guessedLettersIndex, int lives)
{
    size_t wordIndex = 0;
    while (word[wordIndex])
    {
        if (ifLetterAlreadyGuessed(word[wordIndex], guessedLetters, guessedLettersIndex) || word[wordIndex] == SPACE)
        {
            printf("%c ", word[wordIndex]);
        }
        else
        {
            printf("_ ");
        }   
        wordIndex++;    
    }
    printf("remaining lives: %d\n", lives);
}

void clearConsole()
{
    for (size_t i = 0; i < 10; i++)
    {
        printf(" \n");
    }    
}

char getGuess()
{
    char guess;
    do
    {
        printf("please enter a letter:\n");
        scanf(" %c", &guess);
    } while (!isalpha(guess));
    
    return guess;
}

int checkGuess(char guess, char* word, char* guessedLetters, int* guessedLettersIndex)
{
    if (!ifLetterAlreadyGuessed(guess, guessedLetters, guessedLettersIndex))
    {
        return ifLetterInWord(word, guess);
    }
    return 0;
}

void addGuessedLetter(char guess, char* guessedLetters, int* guessedLettersIndex)
{
    guessedLetters[*guessedLettersIndex] = guess;
    (*guessedLettersIndex)++;
}

int ifLetterInWord(char* word, char letter)
{
    size_t wordIndex = 0;
    while (word[wordIndex])
    {
        if (word[wordIndex] == letter)
        {
            return 1;
        }
        
        wordIndex++;
    }
    return 0;
}

int ifLetterAlreadyGuessed(char letter, char* guessedLetters, int* guessedLettersIndex)
{
    for (size_t i = 0; i < *guessedLettersIndex; i++)
    {
        if (guessedLetters[i] == letter)
        {
            return 1;
        }     
    }
    return 0;
}

int checkWin(char* word, char* guessedLetters, int* guessedLettersIndex)
{
    size_t wordIndex = 0;
    while (word[wordIndex])
    {
        if (!ifLetterAlreadyGuessed(word[wordIndex], guessedLetters, guessedLettersIndex))
        {
            return 0;
        }
        
        wordIndex++;
    }
    return 1;
}

void displayWin()
{
    printf("gg ez\n");
}

void displayLose()
{
    printf("you lost :(\n");
}

int main()
{
    printf("Starting game...\n");
    startGame("words.txt"); 
    return 0;
}
