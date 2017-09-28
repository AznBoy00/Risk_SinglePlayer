#pragma once

class Dice {
public:
	Dice();
	~Dice();
	void rollDice(int num);
	int rollDiceOnce();
	void showStats();
private:
	int diceRollDistribution[6];
	int totalDiceRolled;
};