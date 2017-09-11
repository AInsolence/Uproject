/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FBullCowGame.cpp
 * Author: A.Iovbak
 * 
 * Created on September 11, 2017, 5:21 PM
 */

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame() {
}

FBullCowGame::FBullCowGame(const FBullCowGame& orig) {
}

FBullCowGame::~FBullCowGame() {
}

void Reset();//TODO make a more reach return value
int GetMaxTries();
int GetMyCurrentTry();
bool IsGameWon();
bool CheckGuessValidity(std::string);//TODO make a more reach return value
