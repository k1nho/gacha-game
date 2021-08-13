#ifndef PROGRAMMING_ISEKAI_MULTIPLIER
#define PROGRAMMING_ISEKAI_MULTIPLIER

#include "Game.h"
#include "Character.h"

void multiplier(User& user, Game& game) {
	//if battlemode is single mode, increase the currency by 2 (normal would be 1)
	if (game.get_battle_mode() == 1) {
		if (game.get_streak() == 3) {
			user.set_currency(user.get_currency() + 1);
			game.set_streak(0);
		}
	}
	// if gamemode is wave mode increase the currency by 20 (normal would be 10)
	else if (game.get_battle_mode() == 2) {
		if (game.get_streak() == 3) {
			user.set_currency(user.get_currency() + 10);
			game.set_streak(0);
		}
	}
}



#endif