/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: A.Iovbak
 *
 * Created on September 11, 2017, 11:34 AM
 */

#include "header.hpp"
#include "FBullCowGame.hpp"

/*
 * 
 */
void PrintIntro();
std::string GetGuessFromPlayer();
void PrintPlayerGuess();
bool AskPlayAgain();

//the entry point of the application
int main(int argc, char** argv) {
    
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlaySingleGame();
        bPlayAgain = AskPlayAgain();
    }
    while(bPlayAgain);
    
    system("pause");
    
    return 0;//exit the application
}

//introduce the game
void PrintIntro()
{
    std::cout << "Welcome to Bulls & Cows, a fun word game!" << std::endl; 
}

//get guess from Player
std::string GetGuessFromPlayer()
{
    //get the guess from player
    constexpr int WORD_LENGTH = 6;
    std::cout << "Can you guess the " << WORD_LENGTH;
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    std::string Guess = "";
    std::getline(std::cin, Guess);
    
    return Guess;
}

//print out Player guess
void PrintPlayerGuess(std::string& Guess){
    std::cout << "Your variant is : " << Guess << std::endl;
}

//single game loop function
void PlaySingleGame()
{
    //loop for the number of turns asking for guesses
    constexpr int NUMBER_OF_TRIES = 3;
    for (int i = 0; i < NUMBER_OF_TRIES; i++) {
        std::string Guess = GetGuessFromPlayer();
        PrintPlayerGuess(Guess);
    }
}

//ask Player is he want to play again
bool AskPlayAgain()
{
    std::cout << "Do you want to play again (y/n)?" << std::endl;
    std::string PlayerAnswer = "";
    std::getline(std::cin, PlayerAnswer);
    return (PlayerAnswer[0] == 'y') || (PlayerAnswer[0] == 'Y');
}
