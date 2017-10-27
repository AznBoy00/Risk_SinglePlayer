#pragma once

class Dice {
public:
	Dice();
	~Dice();
	void rollDice(int num);
	int rollDiceOnce();
	int rollDefenseDice();
	void showStats();
private:
	int diceRollDistribution[6];
	int totalDiceRolled;
};