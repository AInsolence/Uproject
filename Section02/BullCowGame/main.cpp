// BullCowGame.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "FBullCowGame.h"

/*
*
*/

using int32 = int;
using FText = std::string;

void PrintIntro();
void PlayGame();

FText GetGuessFromPlayer();
void PrintPlayerGuess(FText& Guess);
bool AskPlayAgain();

FBullCowGame BCGame;// instantiate a new game

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

// introduce the game
void PrintIntro()
{
	constexpr int32 WORD_LENGTH = 4;
	std::cout << "Welcome to Bulls & Cows, a fun word game!" << std::endl;
	std::cout << "Can you Guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}

//get Guess from Player
FText GetGuessFromPlayer()
{
	// get the Guess from player
	int32 CurrentTry = BCGame.GetMyCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your Guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);

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
	std::cout << MaxTries << std::endl;
	// loop for the number of tries asking for Guesses
	// TODO change from FOR to WHILE loop once we are validating tries
	for (int32 i = 0; i < MaxTries; i++) {
		FText Guess = GetGuessFromPlayer();// TODO make loop cheking valid

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
