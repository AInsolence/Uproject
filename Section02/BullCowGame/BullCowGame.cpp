// BullCowGame.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "FBullCowGame.h"

/*
*
*/

void PrintIntro();
void PlaySingleGame();

std::string GetGuessFromPlayer();
void PrintPlayerGuess(std::string& Guess);
bool AskPlayAgain();

FBullCowGame BCGame;//instantiate a new game

					//the entry point of the application
int main(int argc, char** argv) {

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlaySingleGame();
		bPlayAgain = AskPlayAgain();
	} while (bPlayAgain);

	system("pause");

	return 0;//exit the application
}

//introduce the game
void PrintIntro()
{
	constexpr int WORD_LENGTH = 6;
	std::cout << "Welcome to Bulls & Cows, a fun word game!" << std::endl;
	std::cout << "Can you Guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}

//get Guess from Player
std::string GetGuessFromPlayer()
{
	//get the Guess from player
	int CurrentTry = BCGame.GetMyCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your Guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);

	return Guess;
}

//print out Player Guess
void PrintPlayerGuess(std::string& Guess) {
	std::cout << "Your variant is : " << Guess << std::endl;
}

//single game loop function
void PlaySingleGame()
{
	int MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;
	//loop for the number of turns asking for Guesses
	for (int i = 0; i < MaxTries; i++) {
		std::string Guess = GetGuessFromPlayer();
		PrintPlayerGuess(Guess);
	}
}

//ask Player is he want to play again
bool AskPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?" << std::endl;
	std::string PlayerAnswer = "";
	std::getline(std::cin, PlayerAnswer);
	return (PlayerAnswer[0] == 'y') || (PlayerAnswer[0] == 'Y');
}
