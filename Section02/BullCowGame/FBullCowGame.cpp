#include "stdafx.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
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

int FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int FBullCowGame::GetMyCurrentTry() const
{
	return MyCurrentTry;
}

//Methods

void FBullCowGame::Reset()//TODO make a more reach return value
{
	return;
}

bool FBullCowGame::IsGameWon()
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(std::string)//TODO make a more reach return value
{
	return false;
}

bool FBullCowGame::IsIsogram(std::string)
{
	return false;
}
