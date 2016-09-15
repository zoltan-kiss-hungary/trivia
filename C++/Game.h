#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <list>
#include <vector>
using namespace std;

class PlayerList {
private:
	int currentPlayer;
	vector<string> playernames;
	vector<unsigned> places;
	vector<unsigned> purses;
public:
	PlayerList();
	string currentPlayerName();
	unsigned currentPlayerId();
	unsigned currentPlayerPlace();
	unsigned currentPlayerCoin();
	void bumpCurrentPlayer();
	void moveCurrentPlayerPlace(unsigned);
	void bumpCurrentPlayerCoin();
	void push_back(const string &);
	unsigned size(void) const;
	bool didPlayerWin();
};

class Game{

private:

	PlayerList players;

	bool inPenaltyBox[6];

	list<string> popQuestions;
	list<string> scienceQuestions;
	list<string> sportsQuestions;
	list<string> rockQuestions;

	bool isGettingOutOfPenaltyBox;
	void addQuestion(list<string> &questionlist, string text, int i);
public:
	Game();
	bool isPlayable();
	bool add(string playerName);

	int howManyPlayers();
	void roll(int roll);

	bool wasCorrectlyAnswered();
	bool wrongAnswer();

private:
	void askQuestion();
	string currentCategory();
};

#endif /* GAME_H_ */
