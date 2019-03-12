#pragma once
#include "fBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame(){ Reset("5"); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset(FString hiddenWordLength)
{
	MyCurrentTry = 1;
	int32 RandNum = rand() % 9 + 1;
	FString RandNumString = std::to_string(RandNum);
	FString HiddenWord = "";
	

	if(hiddenWordLength == "3")
	{
		TMap<FString, FString> HiddenWords{ { "1","nut" },{ "2","lit" },{ "3","bit" },{ "4","bag" },{ "5","ice" },{ "6","law" },{ "7","toy" },{ "8","sad" },{ "9","key" },{ "10","aid" } };
		 HiddenWord = HiddenWords[RandNumString];
	}
	else if(hiddenWordLength == "4")
	{
		TMap<FString, FString> HiddenWords{ { "1","dips" },{ "2","sand" },{ "3","fame" },{ "4","sect" },{ "5","shut" },{ "6","coin" },{ "7","vile" },{ "8","sing" },{ "9","peat" },{ "10","bend" } };
		HiddenWord = HiddenWords[RandNumString];
	}
	else if (hiddenWordLength == "5")
	{
		TMap<FString, FString> HiddenWords{ { "1","large" },{ "2","shale" },{ "3","alien" },{ "4","slunk" },{ "5","raked" },{ "6","fibre" },{ "7","chile" },{ "8","youre" },{ "9","facts" },{ "10","depth" } };
		HiddenWord = HiddenWords[RandNumString];
	}
	else if (hiddenWordLength == "6")
	{
		TMap<FString, FString> HiddenWords{ { "1","forbes" },{ "2","daring" },{ "3","browns" },{ "4","design" },{ "5","golves" },{ "6","mouldy" },{ "7","locker" },{ "8","hasted" },{ "9","blocks" },{ "10","blokes" } };
		HiddenWord = HiddenWords[RandNumString];
	}
	else if (hiddenWordLength == "7")
	{
		TMap<FString, FString> HiddenWords{ { "1","desktop" },{ "2","roguish" },{ "3","society" },{ "4","britons" },{ "5","lashing" },{ "6","clothed" },{ "7","seating" },{ "8","details" },{ "9","fragile" },{ "10","forgave" } };
		HiddenWord = HiddenWords[RandNumString];
	}
	else if (hiddenWordLength == "8")
	{
		TMap<FString, FString> HiddenWords{ { "1","pastiche" },{ "2","whistler" },{ "3","doctrine" },{ "4","rainbows" },{ "5","unharmed" },{ "6","modeling" },{ "7","boasting" },{ "8","istanbul" },{ "9","frighten" },{ "10","fatigued" } };
		HiddenWord = HiddenWords[RandNumString];
	}

		
	MyHiddenWord = HiddenWord;
	
	bGameIsWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WorldLengthToMaxTries{{3,5},{4,8},{5,10},{6,15},{7,20},{8,30} };
	return WorldLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::TestValidGuess(FString guess) const
{
	if (!isIsogram(guess)) //if guess isnt a isogram then
	{
		
		return EGuessStatus::Not_Isogram;
	}
	else if(!isLower(guess))  //if guess isnt all lowercase TODO Write function
	{
		return EGuessStatus::Capital_used;
	}
	else if (guess.length() != MyHiddenWord.length()) //if guess is wrong length
	{
		return EGuessStatus::Wrong_length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}

//Recevies a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitVaildGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //Assuming the same length as guess


	//Loop through all letters in the hidden word	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//Compare letters against the guess
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++)
		{
			if(guess[GuessChar] == MyHiddenWord[MHWChar])
			{
				//If the match
				if(MHWChar == GuessChar)
				{
					//increment bulls if they are in the same place
					BullCowCount.Bulls++;
				}
				else
				{
					//Increment cows if not
					BullCowCount.Cows++;
				}
			}
			
		}
	}

	//Checks to see if the game is won
	if(BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
	//Treat 0 or 1 letter strings as an isogram
	if (word.length() <= 1) { return true; }

	//set up map
	TMap<char, bool> LetterSeen;
	for(auto Letter : word) //For all letters of the word
	{
		Letter = tolower(Letter); //Handles mixed chars
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; //for example in cases where /0 is entered
}

bool FBullCowGame::isLower(FString word) const
{
	for(auto Letter : word)
	{
		if(!islower(Letter))
		{
			return false;
		}
		
	}

	return true;
}
