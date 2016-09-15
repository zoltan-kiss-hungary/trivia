#include <stdlib.h>
#include "Game.h"

static bool winner;

int main()
{
	Game aGame;

	aGame.add("Chet");
	aGame.add("Pat");
	aGame.add("Sue");

	do
	{

		aGame.roll(rand() % 5 + 1);

		if (rand() % 9 == 7)
		{
			winner = aGame.wrongAnswer();
		}
		else
		{
			winner = aGame.correctAnswer();
		}
	} while (!winner);

}
