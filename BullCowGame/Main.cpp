/* This is the console Exe, that makes use of the bull cow class 
   this acts as the view in a MVC patten , and is responisble for all
   user interaction. For game logic see the FBullCowGame
 */
#pragma once

#include <iostream>
#include <string>
#include "fBullCowGame.h"
#include <locale>

//This makes it so that the syntax is unreal friendly
using FText = std::string;
using int32 = int;

void PrintStart();
FText GetVaildGuess();                       
void StartGame();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //Makes new instance of a new game, which is reused

//The start point for the application
int main()
{
	
	//This keeps replaying the game untill the player wants to quit
	do
	{

		system("CLS");
		FString WordLengthWanted;
		bool VaildInput = false;

		//Keeps looping untill the player inputs a corrent word length that they want
		do {

			std::cout << "What length of word do you want? (3 - 8)  - ";
			std::getline(std::cin, WordLengthWanted);

			if (WordLengthWanted == "3" || WordLengthWanted == "4" || WordLengthWanted == "5" || WordLengthWanted == "6" || WordLengthWanted == "7" || WordLengthWanted == "8")
			{
				VaildInput = true;
			}

		} while (!VaildInput);

		//Resets the game so that the player can get a new word everytime
		BCGame.Reset(WordLengthWanted);

		//Introduce the game
		PrintStart();

		//Runs the StartGame function
		StartGame();

	} 
	while(PlayAgain() == 1);
	return 0;
}

void PrintStart()
{
	//Introduce the game
	system("CLS");
	std::cout << "Welcome to Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " Letter isogram i'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

//Loop continualy until the user give a valid guess
FText GetValidGuess() 
{
	EGuessStatus status = EGuessStatus::Invalid_Status;
	FText guess = "";
	do {
		//Gets current try
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " Of " << BCGame.GetMaxTries() << std::endl;

		//Get the guess from the player	
		std::cout << "What is your guess? - ";
		std::getline(std::cin, guess);
		

		//checks to see if guess is valid
		status = BCGame.TestValidGuess(guess);
		switch (status)
		{
		case EGuessStatus::Wrong_length:
			std::cout << std::endl;
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << std::endl << "-----------------------------" << std::endl;
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << std::endl;
			std::cout << "Please enter a isogramic word" << std::endl << "-----------------------------" << std::endl;
			
			break;
			
		case EGuessStatus::Capital_used:
			std::cout << std::endl;
			std::cout << "Please enter a word without capitals" << std::endl << "-----------------------------" << std::endl;
			
			break;

		default:
			//Assuming guess is valid
			break;
		}
	} while (status != EGuessStatus::OK); //This will keep looping until a vaild input has been guessed
	return guess;
}

//Plays 1 game to completion 
void StartGame()
{
 
	int32 MaxTries = BCGame.GetMaxTries();


	/*Loop for the number of turns allowed while the game 
	is NOT won and there is still tries remaining */
	while( !BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText guess = GetValidGuess(); 

		//Submit valid guess to game, and recive counts
		FBullCowCount BullCowCount = BCGame.SubmitVaildGuess(guess);

		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;	
	}

	PrintGameSummary();
	return;
}

bool PlayAgain()
{
	//This asks the player if they want to play again
	std::cout << "Do you want to play again? (Y/N) - ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	//Outputs if the player has won or lost
	if(BCGame.isGameWon())
	{
		std::cout << "Well Done - You WON" << std::endl;
	}
	else if(!BCGame.isGameWon())
	{
		std::cout << "Better luck next time - You LOST" << std::endl;
	}
	return;
}