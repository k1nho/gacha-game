#include <iostream>
#include "Character.h"
#include <string>
#include <fstream>

using namespace std;
using std::string;

// default constructor for character
Character::Character(string name_param, int hp_param, int atk_param, string talent_param,
	int rarity_param, string type_param) {
	set_name(name_param);
	set_hp(hp_param);
	set_atk(atk_param);
	set_talent(talent_param);
	set_rarity(rarity_param);
	set_type(type_param);
}

//constructor to be inherited by enemy class (no rarity)
Character::Character(string name_param, int hp_param, int atk_param, string talent_param, string type_param) {
	set_name(name_param);
	set_hp(hp_param);
	set_atk(atk_param);
	set_talent(talent_param);
	set_type(type_param);
}


void Character::set_name(string name_param) {
	name = name_param;
}
string Character::get_name() const {
	return name;
}

void Character::set_hp(int hp_param) {
	hp = hp_param;
}
int Character::get_hp() const {
	return hp;
}

void Character::set_atk(int atk_param){
	atk = atk_param;
}
int Character::get_atk() const {
	return atk;
}
void Character::set_talent(string talent_param) {
	talent = talent_param;

}
string Character::get_talent() const {
	return talent;
}
void Character::set_rarity(int rarity_param) {
	rarity = rarity_param;
}
int Character::get_rarity() const {
	return rarity;
}
void Character::set_type(string type_param) {
	type = type_param;
}
string Character::get_type() const {
	return type;
}

// talent description for a character
void Character::talent_description() {
	ifstream talent_file;
	talent_file.open("Talents.txt");
	if (talent_file) {
		while (!talent_file.eof()) {

			string talent;
			getline(talent_file, talent, '\t');
			string description;
			getline(talent_file, description, '\t');

			if (talent != get_talent()) {
				talent_file.ignore(10000, '\n');
			}
			else if (get_talent() == "none") {
				cout << "The user does not posses a unique talent" << endl;
				break;
			}
			else {
				cout << "As a hero " << get_name() << " uses " << get_talent() << " to decimate the enemies. "
					<< endl << endl << talent << description << endl << endl;
				break;
			}
		}
	}
 talent_file.close();
}
// overloaded operator. This function returns true if the rarity of the character passed is less than the rarity of the character to the left.
bool Character::operator> (const Character& right) {
	bool stronger;

	if (get_rarity() > right.get_rarity()) {
		stronger = true;
	}
	// if rarity is the same, analyze by power formula
	else if (get_rarity() == right.get_rarity()) {
		int power1 = get_atk() + get_hp();
		int power2 = right.get_atk() + right.get_hp();
		if (power1 > power2) {
			stronger = true;
		}
		else {
			stronger = false;
		}
	}
	// rarity is not greater
	else {
		stronger = false;
	}

	return stronger;
}