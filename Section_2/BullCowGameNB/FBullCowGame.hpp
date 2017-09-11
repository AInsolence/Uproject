/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FBullCowGame.hpp
 * Author: A.Iovbak
 *
 * Created on September 11, 2017, 5:21 PM
 */

#pragma once
#include<string>

class FBullCowGame {
public:
    FBullCowGame();
    FBullCowGame(const FBullCowGame& orig);
    virtual ~FBullCowGame();
    
    void Reset(); //TODO make a more reach return value
    int GetMaxTries();
    int GetMyCurrentTry();
    bool IsGameWon();
    bool CheckGuessValidity(std::string);//TODO make a more reach return value
    
// ^^ Please try to ignore this and try to focus on the interface above ^^ 
private:
    int MyCurrentTry;
    int MyMaxTries;
    bool IsIsogram(std::string);
};


