#include "stdafx.h"
#include "FBullCowGame.h"
#define TMap std::map

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

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

//Methods

void FBullCowGame::Reset()// TODO make a more reach return value
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "and";

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't an isogram
	if (!bIsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram; // TODO write function
	}
	// if guess isn't all lower case
	else if (false)
	{
		return EGuessStatus::NotLowercase; // TODO write function
	}
	// if guess length is wrong
	else if (Guess.length() != this->GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recieves a valid guess, increments tries, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{ // if they're in the same place
				if (GChar == MHWChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}	
			}				
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Guess) const
{
	// treat 0 or 1 letter word is isograms
	if (Guess.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> GuessWordLetters;
	// iterate through all letters in the guess
	for (char Letter : Guess)
	{
		Letter = tolower(Letter); // handle mixed case
		// if letter in the map
		if (GuessWordLetters[Letter])
		{
			return false; // the word is NOT an isogram
		}
		else
		{
			GuessWordLetters[Letter] = true; // add the letter to the map
		}
	}
	return true; // if there are not repeated letters in the Guess
}
