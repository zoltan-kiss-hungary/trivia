#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

PlayerList::PlayerList() : currentPlayer(0) {}

void PlayerList::bumpPlayer()
{
	currentPlayer++;
	if (currentPlayer == playernames.size())
		currentPlayer = 0;
}

string PlayerList::currentPlayerName()
{
	return playernames[currentPlayer];
}

unsigned PlayerList::currentPlayerId()
{
	return currentPlayer;
}

void PlayerList::push_back(const string &val)
{
	playernames.push_back(val);
}

unsigned PlayerList::size(void) const
{
	return playernames.size();
}

Game::Game() : places(), purses(){
	for (int i = 0; i < 50; i++)
	{

		ostringstream oss (ostringstream::out);
		oss << "Pop Question " << i;

		popQuestions.push_back(oss.str());

		char str[255];
		sprintf(str, "Science Question %d", i);
		scienceQuestions.push_back(str);

		char str1[255];
		sprintf(str1, "Sports Question %d", i);
		sportsQuestions.push_back(str1);

		rockQuestions.push_back(createRockQuestion(i));
	}
}

string Game::createRockQuestion(int index)
{
	char indexStr[127];
	sprintf(indexStr, "Rock Question %d", index);
	return indexStr;
}

bool Game::isPlayable()
{
	return (howManyPlayers() >= 2);
}

bool Game::add(string playerName){
	players.push_back(playerName);
	places[howManyPlayers()] = 0;
	purses[howManyPlayers()] = 0;
	inPenaltyBox[howManyPlayers()] = false;

	cout << playerName << " was added" << endl;
	cout << "They are player number " << players.size() << endl;
	return true;
}

int Game::howManyPlayers()
{
	return players.size();
}

void Game::roll(int roll)
{
	cout << players.currentPlayerName() << " is the current player" << endl;
	cout << "They have rolled a " << roll << endl;

	if (inPenaltyBox[players.currentPlayerId()])
	{
		if (roll % 2 != 0)
		{
			isGettingOutOfPenaltyBox = true;

			cout << players.currentPlayerName() << " is getting out of the penalty box" << endl;
			places[players.currentPlayerId()] = places[players.currentPlayerId()] + roll;
			if (places[players.currentPlayerId()] > 11) places[players.currentPlayerId()] = places[players.currentPlayerId()] - 12;

			cout << players.currentPlayerName() << "'s new location is " << places[players.currentPlayerId()] << endl;
			cout << "The category is " << currentCategory() << endl;
			askQuestion();
		}
		else
		{
			cout << players.currentPlayerName() << " is not getting out of the penalty box" << endl;
			isGettingOutOfPenaltyBox = false;
		}

	}
	else
	{

		places[players.currentPlayerId()] = places[players.currentPlayerId()] + roll;
		if (places[players.currentPlayerId()] > 11) places[players.currentPlayerId()] = places[players.currentPlayerId()] - 12;

		cout << players.currentPlayerName() << "'s new location is " << places[players.currentPlayerId()] << endl;
		cout << "The category is " << currentCategory() << endl;
		askQuestion();
	}

}

void Game::askQuestion()
{
	if (currentCategory() == "Pop")
	{
		cout << popQuestions.front() << endl;
		popQuestions.pop_front();
	}
	if (currentCategory() == "Science")
	{
		cout << scienceQuestions.front() << endl;
		scienceQuestions.pop_front();
	}
	if (currentCategory() == "Sports")
	{
		cout << sportsQuestions.front() << endl;
		sportsQuestions.pop_front();
	}
	if (currentCategory() == "Rock")
	{
		cout << rockQuestions.front() << endl;
		rockQuestions.pop_front();
	}
}


string Game::currentCategory()
{
	if (places[players.currentPlayerId()] == 0) return "Pop";
	if (places[players.currentPlayerId()] == 4) return "Pop";
	if (places[players.currentPlayerId()] == 8) return "Pop";
	if (places[players.currentPlayerId()] == 1) return "Science";
	if (places[players.currentPlayerId()] == 5) return "Science";
	if (places[players.currentPlayerId()] == 9) return "Science";
	if (places[players.currentPlayerId()] == 2) return "Sports";
	if (places[players.currentPlayerId()] == 6) return "Sports";
	if (places[players.currentPlayerId()] == 10) return "Sports";
	return "Rock";
}

bool Game::wasCorrectlyAnswered()
{
	if (inPenaltyBox[players.currentPlayerId()])
	{
		if (isGettingOutOfPenaltyBox)
		{
			cout << "Answer was correct!!!!" << endl;
			purses[players.currentPlayerId()]++;
			cout << players.currentPlayerName()
			     << " now has "
			     << purses[players.currentPlayerId()]
				<<  " Gold Coins." << endl;

			bool winner = didPlayerWin();
			players.bumpPlayer();

			return winner;
		}
		else
		{
			players.bumpPlayer();
			return true;
		}



	}
	else
	{

		cout << "Answer was corrent!!!!" << endl;
		purses[players.currentPlayerId()]++;
		cout << players.currentPlayerName()
				<< " now has "
				<< purses[players.currentPlayerId()]
			<< " Gold Coins." << endl;

		bool winner = didPlayerWin();
		players.bumpPlayer();

		return winner;
	}
}

bool Game::wrongAnswer()
{
	cout << "Question was incorrectly answered" << endl;
	cout << players.currentPlayerName() + " was sent to the penalty box" << endl;
	inPenaltyBox[players.currentPlayerId()] = true;

	players.bumpPlayer();
	return true;
}


bool Game::didPlayerWin()
{
	return !(purses[players.currentPlayerId()] == 6);
}
