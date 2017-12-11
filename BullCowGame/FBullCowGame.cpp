#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 2;
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;

	const FString HIDDEN_WORD = "crowd";
	MyHiddenWord = HIDDEN_WORD;
	return;
}

int32 FBullCowGame::GetMaxTries() const{	return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const{	return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{	return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{	return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)//if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)	//if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!=GetHiddenWordLength())//if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else//otherwise
	{
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments turn and returns counts
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all the letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();

	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			//compare letters against the hidden word
			if (Guess[i] == MyHiddenWord[j])
			{
				//if they match then
				if (i == j)
				{
					//increment bulls if they are in the same place
					BullCowCount.Bulls++;
				}
				//else
				else
				{
					//increment cows if they are not
					BullCowCount.Cows++;
				}
			}
		}	
	}
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameIsWon = true;
	}
	return BullCowCount;
}