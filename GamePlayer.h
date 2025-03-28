#pragma once
#include <string>
#include<cstdlib>
#include<ctime>
#include "GameCharacter.h"

class GamePlayer
{
	enum MenuOption
	{
		Invalid,
		Heal = 1,
		Recharge = 2,
		Dodge = 3,
		NormalAttack = 4,
		SpecialAttack = 5
	};
	
	GameCharacter Character;
	bool IsAI;
	bool HasHealed;
	MenuOption LastChoice = MenuOption::Invalid;

	
	GamePlayer() = default;
public:
	GamePlayer(bool ParamIsAI)
	{
		Character = GameCharacter(100, 50);
		IsAI = ParamIsAI;
		HasHealed = false;
	}

	bool ProcessChoice(GameCharacter& Opponent)
	{
		MenuOption Choice;

		if (!IsAI)
		{
			do
			{
				std::cout << std::endl;

				if (!HasHealed)
				{
					std::cout << "1- Heal" << std::endl;
				}

				if (LastChoice != MenuOption::Recharge)
				{
					std::cout << "2- Recharge" << std::endl;
				}
				
				if (LastChoice != MenuOption::Dodge)
				{
					std::cout << "3- Dodge" << std::endl;
				}

				if (LastChoice != MenuOption::NormalAttack)
				{
					std::cout << "4- Normal Attack" << std::endl;
				}

				if (LastChoice != MenuOption::SpecialAttack)
				{
					std::cout << "5- SpeciaL Attack" << std::endl;
				}

				std::cout << std::endl << "Choose a number option: ";

				int NewInput;
				std::cin >> NewInput;
				Choice = (MenuOption)NewInput;
			} while (LastChoice != MenuOption::Invalid && Choice == LastChoice || Choice < MenuOption::Heal + HasHealed || Choice > MenuOption::SpecialAttack);
		}
		else
		{
			std::cout << std::endl << "Enemy is choosing..." << std::endl;

			do
			{
				int EnemyInput = rand() % MenuOption::SpecialAttack + (MenuOption::Heal + HasHealed);
				Choice = (MenuOption)EnemyInput;
			} while (LastChoice != MenuOption::Invalid && Choice == LastChoice);
		}

		return UpdateWorld(Choice, Opponent);
	}

	bool UpdateWorld(MenuOption choice, GameCharacter& Opponent)
	{
		bool EndTurn = true;

		if (choice == MenuOption::Heal)
		{
			if (IsAI)
			{
				std::cout << "Enemy chose Heal" << std::endl;
			}

			Character.Heal();
			HasHealed = true;
			EndTurn = false;
		}
		else if (choice == MenuOption::Recharge)
		{
			if (IsAI)
			{
				std::cout << "Enemy chose Recharge" << std::endl;
			}

			Character.Recharge(Opponent);
			
		}
		else if (choice == MenuOption::Dodge)
		{
			if (IsAI)
			{
				std::cout << "Enemy chose Dodge" << std::endl;
			}

			Character.DodgeOption(Opponent);
		
		}
		else if (choice == MenuOption::NormalAttack)
		{
			if (IsAI)
			{
				std::cout << "Enemy chose Normal Attack" << std::endl;
			}

			Character.NormalAttack(Opponent);
			
		}
		else
		{
			if (IsAI)
			{
				std::cout << "Enemy chose Special Attack" << std::endl;
			}

			EndTurn = Character.SpecialAttack(Opponent);
			
		}

		std::cout << std::endl;

		Character.DisplayStats(IsAI);
		Opponent.DisplayStats(!IsAI);

		if (EndTurn)
		{
			LastChoice = choice;
		}

		return EndTurn;
	}

	void FinishTurn()
	{
		Character.FinishTurn();
		HasHealed = false;
	}

	bool IsCharacterAlive()
	{
		return Character.GetHealth() > 0;
	}

	GameCharacter& GetCharacter()
	{
		return Character;
	}
};