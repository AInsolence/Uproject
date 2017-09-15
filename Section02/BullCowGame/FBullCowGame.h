#pragma once

#pragma once
#include<string>

class FBullCowGame {
public:
	FBullCowGame();
	FBullCowGame(const FBullCowGame& orig);
	virtual ~FBullCowGame();

	int GetMaxTries() const;
	int GetMyCurrentTry() const;
	void Reset(); //TODO make a more reach return value
	bool IsGameWon();
	bool CheckGuessValidity(std::string);//TODO make a more reach return value

// ^^ Please try to ignore this and try to focus on the interface above ^^ 
private:
	int MyCurrentTry = 1;
	int MyMaxTries = 5;
	bool IsIsogram(std::string);
};