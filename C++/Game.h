#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <list>
#include <vector>
using namespace std;

class PlayerList {
private:
	unsigned currentPlayer;
	vector<string> playernames;
	vector<unsigned> places;
	vector<unsigned> purses;
	vector<bool> inPenaltyBox;
public:
	PlayerList();
	string currentPlayerName();
	unsigned currentPlayerId();
	unsigned currentPlayerPlace();
	unsigned currentPlayerCoin();
	bool currentPlayerInPenaltyBox();
	void bumpCurrentPlayer();
	void moveCurrentPlayerPlace(unsigned);
	/* returns whether the player won or not */
	bool bumpCurrentPlayerCoin();
	void clearPenaltyCurrentPlayer();
	void setPenaltyCurrentPlayer();
	void push_back(const string &);
	unsigned size(void) const;
	bool didPlayerWin();
};

class Game{
private:
	PlayerList players;

	list<string> popQuestions;
	list<string> scienceQuestions;
	list<string> sportsQuestions;
	list<string> rockQuestions;

	void addQuestion(list<string> &questionlist, string text, int i);
	void askQuestion();
	string currentCategory();
public:
	/* Init the game with 50 questions in each of the 4 categories */
	Game();
	/* Check if we have at least 2 players in game */
	bool isPlayable();
	/* Add a player to the game with 'playerName'. Name duplication is
	 * allowed */
	void add(string playerName);
	/* Query how many players we have */
	int howManyPlayers();
	/* Check for penalty status and move the player if possible, then ask the
	 * question. Returns whether the player is in penalty or not. */
	bool roll(int roll)

	/* Call these after the player answered. depending on whether their answer
	 * was right or wrong. They return whether the player won or not. Don't
	 * call them if player is in penalty. */
	bool correctAnswer();
	bool wrongAnswer();
};

#endif /* GAME_H_ */
