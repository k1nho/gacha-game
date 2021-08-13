#include <iostream>
#include "Enemy.h"
#include <string>
#include <fstream>

using namespace std;
using std::string;

Enemy::Enemy(string name_param, int hp_param, int atk_param, string talent_param,
	string type_param, string territory_param, string weakness_param)
	:Character(name_param, hp_param, atk_param,talent_param, type_param) {
	set_territory(territory_param);
	set_weakness(weakness_param);
}
void Enemy::set_territory(string territory_param) {
	territory = territory_param;
}
string Enemy::get_territory() const {
	return territory;
}
void Enemy::set_weakness(string weakness_param) {
	weakness = weakness_param;
}
string Enemy::get_weakness() const {
	return weakness;
}
// polymorphism, if it is an enemy object this function will be called.
void Enemy::talent_description() const{
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
				cout << "As a villain " << get_name() << " uses " << get_talent() << " to crush your forces. "
					<< endl << endl << talent << description << endl << endl;
				break;
			}
		}
	}
  talent_file.close();
}