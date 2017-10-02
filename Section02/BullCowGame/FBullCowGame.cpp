/*	
	This is a class provides necessary data & game logic for the BullCow game
*/

#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#define TMap std::map // to make more Unreal friendly

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

// Setters

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

void FBullCowGame::SetHiddenWordByLength(int32 ChosenWordLength)
{
	// container with key = length, value = isograms
	TMap<int32, FString> WordByLength{ { 3, "ear" },{ 4, "hand" },{ 5, "chest" },\
	{ 6, "throat" },{ 7, "stomach" } };
	// initialize the hidden word depending on the length
	MyHiddenWord = WordByLength[ChosenWordLength];
}

//Methods

int32 FBullCowGame::GetMaxTries() const
{
	constexpr int32 DEFAULT_NUMBER_OF_TRIES = 5;
	// container with key = word_length, value = maximum_tries
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 },{ 4, 6 },{ 5, 7 },{ 6, 10 },{ 7, 15 } };
	if (WordLengthToMaxTries[MyHiddenWord.length()])
	{
		return WordLengthToMaxTries[MyHiddenWord.length()];
	}
	else
	{
		return DEFAULT_NUMBER_OF_TRIES;
	}
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't an isogram
	if (!bIsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram;
	}
	// if guess isn't all lower case
	else if (!bIsLowercase(Guess))
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
	if (BullCowCount.Bulls && BullCowCount.Bulls == WordLength)
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

bool FBullCowGame::bIsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) //if NOT a lowercase letter in guess
		{
			return false;
		}
	}
	return true;
}
