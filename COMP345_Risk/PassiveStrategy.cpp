#include "PassiveStrategy.h"
#include "Time.h"

class Strategy;

//Computer Passive Strategy

void PassiveStrategy::attack(Map* map, vector<Player*> playerVector) {
	string input;

	player->stream << "\nATTACK PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	do {
		player->stream << "\nBenevolent Computer will not attack." << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");
		input == "n";
	} while (input == "y");
}

void PassiveStrategy::reinforce(Map* map, Deck* deck) {
	int reinforceAmount = 0;
	int weakestArmy = 999; // Probably impossible occurence, hardcoded

	player->stream << "------------------------------------------\n"
		<< "IT'S PLAYER " << player->getId() << "'S TURN!\n"
		<< "Turn #: " << player->getTurnNumber() << "\n"
		<< "------------------------------------------\n";
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	int addArmies = 0;
	addArmies += player->getOwnedCountries().size() < 12 ? 3 : (int)(player->getOwnedCountries().size() / 3);

	player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s weakest country as the turn starts." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	//find weakest army
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() < weakestArmy) {
			weakestArmy = player->getOwnedCountries()[i]->getNumberOfTroops();
		}
	}

	//reinforce weakest army
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() == weakestArmy) {
			reinforceAmount = addArmies;
			player->getOwnedCountries().at(i)->setNumberOfTroops(player->getOwnedCountries().at(i)->getNumberOfTroops() + reinforceAmount);
			addArmies -= reinforceAmount;
			reinforceAmount = 0;
			player->stream << "Added " << reinforceAmount << " armies to " << player->getOwnedCountries().at(i)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
			break;
		}
	}

	if (player->getHand()->cardsInHand(player->getId(), deck) > 5) {
		cout << "You have more than 5 cards in hand. Trading you hands for reinforcement troops..." << endl;
		addArmies += deck->exchangeHand(player->getId(), deck);
	}
	else {
		cout << "Do you want to exchange your cards? (y to exchange, otherwise reinforce phase will be over)" << endl;
		string confirm;
		confirm = "y";

		if (confirm == "y") {
			addArmies += deck->exchangeHand(player->getId(), deck);
		}
	}

	if (addArmies != 0) {
		player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s countrie(s) of choice" << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");

		//find weakest army
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			if (player->getOwnedCountries()[i]->getNumberOfTroops() < weakestArmy) {
				weakestArmy = player->getOwnedCountries()[i]->getNumberOfTroops();
			}
		}

		//reinforce weakest army
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			if (player->getOwnedCountries()[i]->getNumberOfTroops() == weakestArmy) {
				reinforceAmount = addArmies;
				player->getOwnedCountries().at(i)->setNumberOfTroops(player->getOwnedCountries().at(i)->getNumberOfTroops() + reinforceAmount);
				addArmies -= reinforceAmount;
				reinforceAmount = 0;
				player->stream << "Added " << reinforceAmount << " armies to " << player->getOwnedCountries().at(i)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
				player->Notify();
				player->stream.clear();
				player->stream.str("");
				break;
			}
		}
	}
}


void PassiveStrategy::fortify() {
	int fromCountry = 0, toCountry = 0, moveTroops = 0;
	int weakestArmy = 999, strongestAlly = 0;

	player->stream << "FORTIFYING PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	//to
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() < weakestArmy) {
			weakestArmy = player->getOwnedCountries()[i]->getNumberOfTroops();
		}
	}
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() == weakestArmy) {
			toCountry = i + 1;
		}
	}

	//from
	for (size_t i = 0; i < player->getOwnedCountries()[toCountry - 1]->getAllies().size(); i++) {
		if (player->getOwnedCountries()[toCountry - 1]->getAllies()[i]->getNumberOfTroops() > strongestAlly) {
			strongestAlly = player->getOwnedCountries()[toCountry - 1]->getAllies()[i]->getNumberOfTroops();
		}
	}
	for (size_t i = 0; i < player->getOwnedCountries()[toCountry - 1]->getAllies().size(); i++) {
		if (player->getOwnedCountries()[toCountry - 1]->getAllies()[i]->getNumberOfTroops() == strongestAlly) {
			fromCountry = i + 1;
		}
	}

	moveTroops = strongestAlly - 1;

	if (moveTroops == 0) {
		player->stream << "No nearby ally countries can reinforce the strongest country" << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");
	} else {
		player->stream << "Transferring " << moveTroops << " troops from country: " << player->getOwnedCountries()[toCountry - 1]->getAllies()[fromCountry - 1]->getNameOfCountry() << " to " << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");

		player->getOwnedCountries()[fromCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() - moveTroops);
		player->getOwnedCountries()[toCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() + moveTroops);

		player->stream << player->getOwnedCountries()[fromCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() << " armies." << endl;
		player->stream << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() << " armies." << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");
	}
}