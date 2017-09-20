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

	const FString HIDDEN_WORD = "planet";
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

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		// compare letters against the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			// if they match
			if (Guess[i] == MyHiddenWord[j])
			{
				// if they're in the same place
				if (i == j)
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
