#include "stdafx.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset(); //delegate to Reset() method
	return;
}

FBullCowGame::FBullCowGame(const FBullCowGame& orig)
{
	return;
}

FBullCowGame::~FBullCowGame()
{
	return;
}

//Getters

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetMyCurrentTry() const
{
	return MyCurrentTry;
}

//Methods

void FBullCowGame::Reset()// TODO make a more reach return value
{
	constexpr int32 MAX_TRIES = 5;
	MyMaxTries = MAX_TRIES;
	
	MyCurrentTry = 1;

	const FString HIDDEN_WORD = "and";
	MyHiddenWord = HIDDEN_WORD;
	
	return;
}

bool FBullCowGame::IsGameWon()
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
// TODO make a more reach return value
{
	return false;
}

// recieves a valid guess, increments tries, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increase the tries number
	MyCurrentTry++;

	// setup the return variable
	FBullCowCount BullCowCount;

	// check for not empty guess string
	if (Guess.empty())
	{
		std::cout << "Please try again. You can not guess if you enter an empty string!";
		std::cout << std::endl;
		return BullCowCount;
	}

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
	{
		// compare letters against the hidden word
		for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
		{
			// if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they're in the same place
				if (GChar == MHWChar)
				{
					// incriment bulls
					BullCowCount.Bulls++;
				}
				else
				{
					// incriment cows
					BullCowCount.Cows++;
				}	
			}				
		}
	}
	return BullCowCount;
}
