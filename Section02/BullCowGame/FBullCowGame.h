#pragma once

#include <string>
#include <map>

using int32 = int;
using FString = std::string;

// all values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	NotIsogram,
	WrongLength,
	NotLowercase
};

class FBullCowGame {
public:
	FBullCowGame();
	FBullCowGame(const FBullCowGame& orig);
	virtual ~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetMyCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity (FString) const;
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString);

// ^^ Please try to ignore this and try to focus on the interface above ^^ 
private:
	//see constructor for itialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool bIsIsogram(FString) const;
	bool bIsLowercase(FString) const;
};
