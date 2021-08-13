#ifndef PROGRAMMING_ISEKAI_USER
#define PROGRAMMING_ISEKAI_USER

#include "Character.h"
#include <string>
#include <vector>

// use foward declaration for friend function
class Game;

class User {
private:
	std::vector<Character> player_box;
	int currency;
	int arena_wins;
	int arena_losses;

public:
	// constructor
	User(std::vector<Character> player_box, int currency = 100, int arena_wins = 0, int arena_losses = 0);
	//setters and getters
	void set_currency(int);
	int get_currency() const;
	void set_arena_wins(int);
	int get_arena_wins() const;
	void set_arena_losses(int);
	int get_arena_losses() const;
	// useful functions
	int count_characters();
	void add_character(Character);
	void delete_character(int);
	void show_box();
	Character retrieve_character(int);
	// file writting function
	void write_to_file(std::string);
	// friend function
	friend void multiplier(User& user, Game& game);
};

#endif
