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
	std::cout << "Welcome to Bulls & Cows, a fun word game!" << std::endl;
	std::cout << "Can you Guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}
void PlayGame();

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
	// get the Guess from player
	int32 CurrentTry = BCGame.GetMyCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your Guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);

	EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
	switch (Status)
	{
	case EGuessStatus::NotIsogram:
		break;
	case EGuessStatus::WrongLength:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
		std::cout << " letter word.\n";
		break;
	case EGuessStatus::NotLowercase:
		break;
	default:
		return Guess;
	}
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

	// loop for the number of tries asking for Guesses
	for (int32 i = 0; i < MaxTries; i++) { // TODO change from FOR to WHILE
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		PrintPlayerGuess(Guess);
	}
	
	// TODO summarise game
}

// ask Player is he want to play again
bool AskPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?" << std::endl;
	FText PlayerAnswer = "";
	std::getline(std::cin, PlayerAnswer);
	return (PlayerAnswer[0] == 'y') || (PlayerAnswer[0] == 'Y');
}
