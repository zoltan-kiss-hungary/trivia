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
public:
	PlayerList();
	string currentPlayerName();
	unsigned currentPlayerId();
	void bumpPlayer();
	void push_back(const string &);
	unsigned size(void) const;
};

class Game{

private:

	PlayerList players;
	int places[6];
	int purses[6];

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

	bool didPlayerWin();
};

#endif /* GAME_H_ */
