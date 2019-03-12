/*This is the game logic and has no direct user interaction*/
#pragma once
#include <string>

//This makes it so that the syntax is unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_length,
	Capital_used,
	Number_used,
	Symbol_used,
};

class FBullCowGame
{
public:
	FBullCowGame(); //constuctor


	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool isGameWon() const;
	int32 GetHiddenWordLength() const;

	void Reset(FString);  
	EGuessStatus TestValidGuess(FString) const; 
	
	// counts bulls and cows, increasing turn # assuming valid guess
	FBullCowCount SubmitVaildGuess(FString);

	

	//See constructor
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool isIsogram(FString) const;
	bool isLower(FString) const;
};
