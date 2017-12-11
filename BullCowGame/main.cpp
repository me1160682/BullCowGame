#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

//The entry point of our application
int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} while (AskToPlayAgain());
	return 0; // exit the application
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game
	//is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess();

		std::cout << "Your guess was: " << Guess << std::endl;

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls : " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows : " << BullCowCount.Cows << std::endl;

	}
	PrintGameSummary();
}

void PrintIntro()
{
	// introduce the game
	int32 WordLength = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << WordLength << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

//loop continually until the user gets a valid guess
Ftext GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		Ftext Guess = "";
		std::cout << "Try " << CurrentTry << ". Enter your guess : ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			return Guess;
		}
	} while (Status!=EGuessStatus::OK);//Keep looping until no errors
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again(y/n) with the same hidden word? ";
	Ftext Response = "";
	getline(std::cin,Response);
	std::cout << std::endl;
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "You won ! Well done.\n";
	}
	else
	{
		std::cout << "You lose. Better luck next time.\n";
	}
	return;
}