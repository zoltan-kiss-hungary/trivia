#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

PlayerList::PlayerList() : currentPlayer(0) {}

void PlayerList::bumpCurrentPlayer()
{
	currentPlayer++;
	if (currentPlayer == playernames.size())
		currentPlayer = 0;
}

 bool PlayerList::bumpCurrentPlayerCoin()
{
	purses[currentPlayer]++;
	return didPlayerWin();
}

void PlayerList::moveCurrentPlayerPlace(unsigned roll)
{
	places[currentPlayer] += roll;
	if (places[currentPlayer] > 11)
		places[currentPlayer] = places[currentPlayer] - 12;

}

void PlayerList::penaltyForCurrentPlayer()
{
	inPenaltyBox[currentPlayer] = true;
}

string PlayerList::currentPlayerName()
{
	return playernames[currentPlayer];
}

unsigned PlayerList::currentPlayerId()
{
	return currentPlayer;
}

unsigned PlayerList::currentPlayerPlace()
{
	return places[currentPlayer];
}

unsigned PlayerList::currentPlayerCoin()
{
	return purses[currentPlayer];
}

bool PlayerList::currentPlayerInPenaltyBox()
{
	return inPenaltyBox[currentPlayer];
}

void PlayerList::push_back(const string &val)
{
	playernames.push_back(val);
	places.push_back(0);
	purses.push_back(0);
	inPenaltyBox.push_back(false);
}

unsigned PlayerList::size(void) const
{
	return playernames.size();
}

Game::Game() : isGettingOutOfPenaltyBox(false) {
	for (int i = 0; i < 50; i++) {
		addQuestion(popQuestions, "Pop Question ", i);
		addQuestion(scienceQuestions, "Science Question ", i);
		addQuestion(sportsQuestions, "Sports Question ", i);
		addQuestion(rockQuestions, "Rock Question ", i);
	}
}

void Game::addQuestion(list<string> &questionlist, string text, int i)
{
	ostringstream question (ostringstream::out);
	question << text << i;
	questionlist.push_back(question.str());
}

bool Game::isPlayable()
{
	return (howManyPlayers() >= 2);
}

bool Game::add(string playerName){
	players.push_back(playerName);

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

	if (players.currentPlayerInPenaltyBox())
	{
		if (roll % 2 != 0)
		{
			isGettingOutOfPenaltyBox = true;

			cout << players.currentPlayerName() << " is getting out of the penalty box" << endl;
			players.moveCurrentPlayerPlace(roll);

			cout << players.currentPlayerName() << "'s new location is " << players.currentPlayerPlace() << endl;
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

		players.moveCurrentPlayerPlace(roll);

		cout << players.currentPlayerName() << "'s new location is " << players.currentPlayerPlace() << endl;
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
	switch (players.currentPlayerPlace()) {
		case 0 : return "Pop";
		case 4 : return "Pop";
		case 8 : return "Pop";
		case 1 : return "Science";
		case 5 : return "Science";
		case 9 : return "Science";
		case 2 : return "Sports";
		case 6 : return "Sports";
		case 10 : return "Sports";
	}
	return "Rock";
}

bool Game::correctAnswer()
{
	if (players.currentPlayerInPenaltyBox() && !isGettingOutOfPenaltyBox) {
		players.bumpCurrentPlayer();
		return false;
	}
	cout << "Answer was correct!!!!" << endl;
	cout << players.currentPlayerName() << " now has "
		<< players.currentPlayerCoin() << " Gold Coins." << endl;

	bool winner = players.bumpCurrentPlayerCoin();
	players.bumpCurrentPlayer();
	return winner;
}

bool Game::wrongAnswer()
{
	cout << "Question was incorrectly answered" << endl;
	cout << players.currentPlayerName() + " was sent to the penalty box" << endl;
	players.penaltyForCurrentPlayer();

	players.bumpCurrentPlayer();
	return false;
}


bool PlayerList::didPlayerWin()
{
	return purses[currentPlayer] == 6;
}
