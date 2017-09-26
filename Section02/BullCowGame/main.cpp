// BullCowGame.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "FBullCowGame.h"

/*
*
*/

using int32 = int;
using FText = std::string;
FBullCowGame BCGame;// instantiate a new game

// introduce the game
void PrintIntro()
{
	std::cout << "\n\n";
	std::cout << "Welcome to Bulls & Cows, a fun word game!" << std::endl;
	std::cout << "Can you Guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}
void PlayGame();
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

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	
	do {
		// get the Guess from player
		int32 CurrentTry = BCGame.GetMyCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your Guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::NotIsogram:
			std::cout << "Please enter the word without repeating letters.\n\n";
			break;
		case EGuessStatus::WrongLength:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
			std::cout << " letter word.\n\n";
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
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
