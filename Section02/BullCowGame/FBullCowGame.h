#pragma once

#pragma once
#include<string>

using FString = std::string;

class FBullCowGame {
public:
	FBullCowGame();
	FBullCowGame(const FBullCowGame& orig);
	virtual ~FBullCowGame();

	int GetMaxTries() const;
	int GetMyCurrentTry() const;
	void Reset(); // TODO make a more reach return value
	bool IsGameWon();
	bool CheckGuessValidity(FString);// TODO make a more reach return value
	// provide a method for counting bulls & cows, and increasing try #

// ^^ Please try to ignore this and try to focus on the interface above ^^ 
private:
	//see constructor for itialization
	int MyCurrentTry;
	int MyMaxTries;
};
