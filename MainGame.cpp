#include <iostream>
#include "GamePlayer.h"
#include "GameCharacter.h"

int main()
{
	srand((unsigned int)time(NULL));

	std::cout << "Welcome to my turned base game, Hope you have fun!" << std::endl;
	
	int TurnIndex = 0;
	
	GamePlayer GamePlayers[2] = { GamePlayer(false), GamePlayer(true) };

	do
	{
		GameCharacter& Opponent = GamePlayers[(TurnIndex + 1) % 2].GetCharacter();

		if (GamePlayers[TurnIndex].ProcessChoice(Opponent))
		{
			GamePlayers[TurnIndex].FinishTurn();
			TurnIndex = (TurnIndex + 1) % 2;
		}
	}
	while (GamePlayers[0].IsCharacterAlive() && GamePlayers[1].IsCharacterAlive());

	std::string Winner;

	if (GamePlayers[0].IsCharacterAlive())
	{
		Winner = "Player";
	}
	else
	{
		Winner = "Enemy";
	}

	std::cout << "The " << Winner << " is the winner!" << std::endl;

		return 0;

};