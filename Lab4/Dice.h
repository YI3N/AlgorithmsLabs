#pragma once
#include <string>
#include <random>
#include <stdarg.h>

int GetDice(std::string dice)
{	
	int result = 0;
	int diceThrows = 0;
	int diceType = 0;
	int diceMod = 0;
	bool havePlusMod = false;
	bool haveMinusMod = false;

	std::string str = "";
	for (auto ch : dice)
	{
		str += ch;
			
		if (ch == 'd')
		{
			diceThrows = std::stoi(str);
			str = "";
		}
		else if (ch == '+')
		{
			havePlusMod = true;
			diceType = std::stoi(str);
			str = "";
		}
		else if (ch == '-')
		{
			haveMinusMod = true;
			diceType = std::stoi(str);
			str = "";
		}
	}

	if (havePlusMod)
		diceMod += std::stoi(str);
	else if (haveMinusMod)
		diceMod -= std::stoi(str);
	else
		diceType = std::stoi(str);

	for (int i = 0; i < diceThrows; i++)
		result += std::rand() % diceType + 1;
	result += diceMod;

	return result;
}

std::vector<int> ThrowDice(int dicesAmount...)
{
	std::vector<int> results;

	va_list dices;
	char* dice;

	va_start(dices, dicesAmount);
	for (int i = 0; i < dicesAmount; i++)
	{
		dice = va_arg(dices, char*);
		results.push_back(GetDice(dice));
	}
	va_end(dices);

	return results;
}