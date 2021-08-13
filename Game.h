#ifndef PROGRAMMING_ISEKAI_GAME
#define PROGRAMMING_ISEKAI_GAME

#include "Character.h"
#include "User.h"
#include <vector>
#include <string>

class Game {
private:
	static std::vector<Character> banner;
	int mode;
	std::string username;
	bool state;
	int battle_mode;
	int streak;
public:
	// constructor
	Game(int mode = 0, std::string username = "",
		bool state = true, int battle_mode = 1, int streak = 0);
	// setters and getters
	void set_mode(int);
	int get_mode() const;
	void set_username(std::string);
	std::string get_username() const;
	void set_state(bool);
	bool get_state() const;
	void set_battle_mode(int);
	int get_battle_mode() const;
	void set_streak(int);
	int get_streak() const;
	// login functions
	User create_session();
	User restore_session();
	// Banner generation function
	static void create_banner();
	// checking user existance
	bool check_session();
	// gamemode functions
	static User gacha_roll(User, std::string);
	static User arena(User, std::string);
	// friend function
	friend void multiplier(User& user, Game& game);

};


#endif
