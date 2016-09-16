#include <stdlib.h>
#include "Game.h"

static bool winner = false;

int main()
{
	Game aGame;

	aGame.add("Chet");
	aGame.add("Pat");
	aGame.add("Sue");

	do
	{
		if (!aGame.roll(rand() % 5 + 1))
			continue;

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
