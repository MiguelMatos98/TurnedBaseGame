#pragma once

class GameCharacter
{
	float Health = 0;
	float Energy = 0;
	float EnergyRate = 25;
	int ExtraChanceToHit = 0;

public:

	GameCharacter() = default;

	GameCharacter(const float& MaxH, const float& MaxE)
	{
		Health = MaxH;
		Energy = MaxE;
	}

	float GetHealth()
	{
		return Health;
	}

	void Heal()
	{
		Health += Energy / 2;

		if (Health > 100)
		{
			Health = 100;
		}
	}

	void Recharge(GameCharacter& Opponent)
	{
		EnergyRate *= 4;
		Opponent.ExtraChanceToHit = 10;
	}

	void DodgeOption(GameCharacter& Opponent)
	{
		Opponent.ExtraChanceToHit = -30;
		EnergyRate = EnergyRate/2;
	}

	void Damage(int DamageAmount)
	{
		Health -= DamageAmount;

		if (Health < 0)
		{
			Health = 0;
		}
	}

	void NormalAttack(GameCharacter& Opponent)
	{
		if (rand() % 100 <= ExtraChanceToHit + 80)
		{
			int NormalDamage = rand() % 10 + 1;

			Opponent.Damage(NormalDamage);
		}
	}

	bool SpecialAttack(GameCharacter& Opponent)
	{
		bool EnoughEnergy = Energy >=50;

		if (EnoughEnergy)
		{
			Energy -= 50;
			
			if (rand() % 100 <= ExtraChanceToHit + 50)
			{
				int SpecialDamage = rand() % 20 + 5;

				Opponent.Damage(SpecialDamage);
			}
		}
		return EnoughEnergy;
	}

	void DisplayStats(bool IsAI)
	{
		std::string Type;

		if (IsAI)
		{
			Type = "Enemy ";
		}
		else 
		
			Type = "Player ";

		std::cout << Type << "Health is: " << Health << " and " << Type << "Energy is: " << Energy << std::endl;
	}

	void FinishTurn()
	{
		Energy += EnergyRate;

		if (Energy > 100)
		{
			Energy = 100;
		}

		EnergyRate = 25;
		ExtraChanceToHit = 0;
	}
};