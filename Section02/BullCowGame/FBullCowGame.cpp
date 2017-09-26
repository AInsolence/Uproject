#include "stdafx.h"
#include "FBullCowGame.h"

// constructor
FBullCowGame::FBullCowGame()
{
	Reset(); //delegate to Reset() method
	return;
}

// constructor of copy
FBullCowGame::FBullCowGame(const FBullCowGame& orig)
{
	return;
}

// destructor
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

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

//Methods

void FBullCowGame::Reset()// TODO make a more reach return value
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "and";

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	return;
}

bool FBullCowGame::IsGameWon()
{
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't an isogram
	if (false)
	{
		return EGuessStatus::NotIsogram;
	}
	// if guess isn't all lower case
	else if (false)
	{
		return EGuessStatus::NotLowercase;
	}
	// if guess length is wrong
	else if (Guess.length() != this->GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	else
	{
		return EGuessStatus::OK; // TODO make actual error
	}
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
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength && GChar < Guess.length(); GChar++)
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
