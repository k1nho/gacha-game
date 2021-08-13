#include "User.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

User::User(std::vector<Character> player_box_param, int currency_param, int arena_wins_param, int arena_losses_param) {
	player_box = player_box_param;
	set_currency(currency_param);
	set_arena_wins(arena_wins_param);
	set_arena_losses(arena_losses_param);
}

void User::set_currency(int currency_param) {
	currency = currency_param;
}
int User::get_currency() const {
	return currency;
}
void User::set_arena_wins(int arena_wins_param) {
	arena_wins = arena_wins_param;
}
int User::get_arena_wins() const {
	return arena_wins;
}
void User::set_arena_losses(int arena_losses_param) {
	arena_losses = arena_losses_param;
}
int User::get_arena_losses() const {
	return arena_losses;
}
int User::count_characters() {
	int count = 0;
	for (Character character : player_box) {
		count += 1;
	}
	return count;
}
// This function adds a character to te player box
void User::add_character(Character character) {
	
		player_box.push_back(character);

}
// This function deletes a character from the player box
void User::delete_character(int index) {

	int index_to_delete = index - 1;
	if (count_characters() == 1) {
		throw invalid_argument("You cannot delete the last character in your account.");
		cout << endl;
	}

	else if (index <= 0 || index > 10) {
		throw invalid_argument("Invalid index. Try again");
		cout << endl;
	}

	else {
		for (int i = 0; i < count_characters(); i++) {
			if (i == index_to_delete) {
				player_box.erase(player_box.begin() + index_to_delete);
				break;
			}
		}
		
	}
}
// This function shows the user all the characters owned
void User::show_box() {
	cout << "                           CHARACTER BOX                                       " << endl << endl;
	cout <<setw(3) << "  N" <<setw(15) << "Name" << setw(10) << "Hp" << setw(10) << "Atk " << setw(15) << "Talent" <<
	setw(10) << "Rarity" << setw(10) << "      Type" << endl << endl;

	for (int i = 0; i < count_characters(); i++) {
		if (i == 9) {
			cout << setw(3) <<i+1 <<setw(15) << player_box[i].get_name()
			<< setw(10) << player_box[i].get_hp() << setw(10) << player_box[i].get_atk() << setw(15) <<
			player_box[i].get_talent() << setw(10) << player_box[i].get_rarity() << setw(10) << player_box[i].get_type() << endl;
		}
		else {
			cout<< setw(3) <<i+1<<setw(15) << player_box[i].get_name()
			<< setw(10) << player_box[i].get_hp() << setw(10) << player_box[i].get_atk() << setw(15) <<
			player_box[i].get_talent() << setw(10) << player_box[i].get_rarity() << setw(10) << player_box[i].get_type() << endl;
		}
	}
	cout << endl;
}
// This function retrieves an specific character from the player box
Character User::retrieve_character(int index) {
	if (index <= 0 || index > count_characters()) {
		throw invalid_argument("Invalid index. Try again");
	}
	return player_box[index -1];
}
// This function records the user's stats into a unique file
void User::write_to_file(string username) {
	ofstream output_file;
	output_file.open(username + ".txt");

	output_file << get_currency() << '\t' << get_arena_wins() << '\t' << get_arena_losses() << endl;

	for (int i = 0; i < count_characters(); i++) {
 
		if (i == count_characters() - 1) {
			output_file << player_box[i].get_name() << '\t' << player_box[i].get_hp() << '\t' << player_box[i].get_atk() << '\t'
				<< player_box[i].get_talent() << '\t' << player_box[i].get_rarity() << '\t' << player_box[i].get_type();
		}
		else {
			output_file << player_box[i].get_name() << '\t' << player_box[i].get_hp() << '\t' << player_box[i].get_atk() << '\t'
				<< player_box[i].get_talent() << '\t' << player_box[i].get_rarity() << '\t' << player_box[i].get_type() << endl;
		}
	}

	output_file.close();
}
