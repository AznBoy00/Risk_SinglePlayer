#pragma once
class Dice
{
public:
	Dice(int num);
	~Dice();
	void rollDice(int num);
	
private:
	int diceRollNumber;
	int *diceValue;
	int getDiceRollNumber();
	void setDiceRollNumber(int num);
};

