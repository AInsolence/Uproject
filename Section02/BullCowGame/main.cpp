/*	This is a console executable, that makes use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For the game logic see the FBullCowGame class.
*/

#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using int32 = int;
using FText = std::string;
FBullCowGame BCGame;// instantiate a new game, which we re-use across plays

// function prototypes as otside the class
void PrintIntro();
void PlayGame();
void AskWordLength();
void GetValidLength(int32 MIN_WORD_LENGTH, int32 MAX_WORD_LENGTH);
void PrintGameSummary();
FText GetValidGuess();
void PrintPlayerGuess(FText& Guess);
bool AskPlayAgain();

// the entry point of the application
int main(int argc, char** argv) {

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskPlayAgain();
	} while (bPlayAgain);

	system("pause");

	return 0;// exit the application
}

void PrintIntro()
{
	std::cout << "\n\n";
	std::cout << "Welcome to Bulls & Cows, a fun word game!\n" << std::endl;
	std::cout << "           }   {         /__/ " << std::endl;
	std::cout << "           (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\   /        \\  /-------\\ " << std::endl;
	std::cout << "  / | BULL |o o          oo| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |               |------|  * " << std::endl;
	std::cout << "    ^      ^               ^      ^ " << std::endl;
	std::cout << "Try to guess the isogram I'm thinking of !!!\n" << std::endl;
	std::cout << "Hint: it is a part of human body.\n" << std::endl;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	
	do {
		// get the Guess from player
		int32 CurrentTry = BCGame.GetMyCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your Guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::NotIsogram:
			std::cout << "Please enter the word without repeating letters.\n";
			break;
		case EGuessStatus::WrongLength:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
			std::cout << " letter word.\n";
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	
	return Guess;
}

// print out Player Guess
void PrintPlayerGuess(FText& Guess) {
	std::cout << "Your variant is : " << Guess << std::endl;
}

// single game loop function
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	AskWordLength();

	// loop asking for guesses while the game is NOT won
	// and there are still try remainings
	while (!BCGame.IsGameWon() && BCGame.GetMyCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		PrintPlayerGuess(Guess);
	}
	
	PrintGameSummary();

	return;
}

// asking user if he wants to set a hidden word length
void AskWordLength()
{
	const int32 MIN_WORD_LENGTH = 3;
	const int32 MAX_WORD_LENGTH = 7;

	FString UserChoice = "";
	std::cout << "Do you want to chose hidden word length (y/n)?\n";
	std::cin >> UserChoice;
	// if user want to set word length
	if (UserChoice == "y")
	{	
		GetValidLength(MIN_WORD_LENGTH, MAX_WORD_LENGTH);
	}
	else
	{
		std::cout << "Setting the default length for you!\n";
		BCGame.SetHiddenWordByLength(MIN_WORD_LENGTH);// by default use the 3 letter word
	}
	return;
}

// get from user a hidden word length
void GetValidLength(int32 MIN_WORD_LENGTH, int32 MAX_WORD_LENGTH)
{
	FString UserInput = "";
	std::cout << "Please enter available word length from ";
	std::cout << MIN_WORD_LENGTH << " to " << MAX_WORD_LENGTH << " :\n";
	std::cin >> UserInput;
	//check user input for valid characters & valid available word length
	if (UserInput.find_first_not_of("0123456789") == FString::npos && 
		stoi(UserInput) > MIN_WORD_LENGTH && stoi(UserInput) < MAX_WORD_LENGTH)
	{// if input is valid set hidden word with users length
		BCGame.SetHiddenWordByLength(stoi(UserInput));
	}
	else
	{// if user input is invalid, suggest him to try again
		std::cout << "Your input is not valid or ";
		std::cout << "the length of the word you entered is not available.\nPlease try again\n\n";
		AskWordLength();
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nYOU WIN!!! Congratulations!!!\n";
	}
	else
	{
		std::cout << "\nYOU LOSE!!! Better luck next time!!!\n";
	}
}


// ask Player is he want to play again
bool AskPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?\n";
	FText PlayerAnswer = "";
	std::getline(std::cin, PlayerAnswer);
	return (PlayerAnswer[0] == 'y') || (PlayerAnswer[0] == 'Y');
}
