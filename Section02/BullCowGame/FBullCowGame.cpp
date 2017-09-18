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

int FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int FBullCowGame::GetMyCurrentTry() const
{
	return MyCurrentTry;
}

//Methods

void FBullCowGame::Reset()// TODO make a more reach return value
{
	constexpr int MAX_TRIES = 5;
	MyMaxTries = MAX_TRIES;
	
	MyCurrentTry = 1;
	
	return;
}

bool FBullCowGame::IsGameWon()
{
	return false;
}

bool FBullCowGame::CheckValidity(std::string)// TODO make a more reach return value
{
	return false;
}
