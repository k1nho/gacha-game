#include "Game.h"
#include "Enemy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;
using std::string;
using namespace std::this_thread;
using namespace std::chrono;

vector<Character> Game::banner;

Game::Game(int mode_param, string username_param,
	bool state_param, int battle_mode_param, int streak_param) {
	set_mode(mode_param);
	set_username(username_param);
	set_state(state_param);
	set_battle_mode(battle_mode_param);
	set_streak(streak_param);
}
void Game::set_mode(int mode_param) {
	mode = mode_param;
}
int Game::get_mode() const {
	return mode;
}
void Game::set_username(string username_param) {
	username = username_param;
}
string Game::get_username() const {
	return username;
}
void Game::set_state(bool state_param){
	state = state_param;
}
bool Game::get_state() const {
	return state;
}
void Game::set_battle_mode(int battle_mode_param) {
	battle_mode = battle_mode_param;
}
int Game::get_battle_mode() const {
	return battle_mode;
}
void Game::set_streak(int streak_param) {
	streak = streak_param;
}
int Game::get_streak() const {
	return streak;
}
// This funcion creates a new account 
User Game::create_session() {
	vector<Character> initial;
	Character first("Welcomer", 1000, 1000, "Burn", 2, "Sniper");
	initial.push_back(first);
	User temp(initial, 20, 0, 0);
	
	return temp;
}
//This function restore an account
User Game::restore_session() {
	ifstream user_file;
	// use the username in session to read the file
	user_file.open(get_username() + ".txt");

	vector<Character> temp;
	int money;
	int wins;
	int losses;
	int counter = 0;
	if (user_file) {
		while (!user_file.eof()) {
			
			if (counter == 0) {
				user_file >> money;
				user_file.ignore();

				user_file >> wins;
				user_file.ignore();

				user_file >> losses;
				user_file.ignore(1000,'\n');

				counter += 1;
			}
			else {
				string name;
				getline(user_file, name, '\t');

				int hp;
				user_file >> hp;
				user_file.ignore();

				int atk;
				user_file >> atk;
				user_file.ignore();

				string talent;
				getline(user_file, talent, '\t');

				int rarity;
				user_file >> rarity;
				user_file.ignore();

				string type;
				getline(user_file, type, '\n');

				Character tempo(name, hp, atk, talent, rarity, type);

				temp.push_back(tempo);
			}
		}
	}
	if (temp.back().get_name() == "") {
		temp.pop_back();
	}
	user_file.close();
	User existing_user(temp, money, wins, losses);

	return existing_user;

}
// This function creates a banner for a gacha session
void Game::create_banner() {
	int rotation = 1;
	srand(time(nullptr));
	// randomize the banner rotation
	rotation = rand() % 3 + 1;
	rand();

	ifstream banner_file;
	banner_file.open("Banner" + to_string(rotation) + ".txt");
	vector<Character> temp;

	 if(banner_file) {
		 while (!banner_file.eof()) {
			 string name;
			 getline(banner_file, name, '\t');

			 int hp;
			 banner_file >> hp;
			 banner_file.ignore();

			 int atk;
			 banner_file >> atk;
			 banner_file.ignore();

			 string talent;
			 getline(banner_file, talent, '\t');

			 int rarity;
			 banner_file >> rarity;
			 banner_file.ignore();

			 string type;
			 getline(banner_file, type, '\n');

			 Character tempo(name, hp, atk, talent, rarity, type);

			 temp.push_back(tempo);
		}
	}
	 if (temp.back().get_name() == "") {
		 temp.pop_back();
	 }

   banner_file.close();
	 banner = temp;
	 
}
// This function checks if an user file exists
bool Game::check_session() {
	ifstream user_file;
	user_file.open(get_username() + ".txt");

	if (user_file) {
    user_file.close();
		return true;
	}
  user_file.close();
	return false;
}
// This functions does all the operations related to the gacha mode
User Game::gacha_roll(User user, string filename) {

	// create the banner using the create banner function
	Game::create_banner();

	char accept = 'a';
	cout << "                               GACHA MODE" << endl << endl;
	int i, j;
	for (i = 1; i <= 6; i++) {
		for (j = 1; j <= 25; j++) {
			if (i == 1 || i == 6 ||
				j == 1 || j == 25) {
				cout << " * ";
			}
			else {
				if (i == 3 && j == 8) {
					cout << "Banner: the legendary " << banner[0].get_name() 
					<< setw(23 + 8 -banner[0].get_name().length()) << "*";
					break;
				}
				else {
					cout << "   ";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "Featuring 3* star: " << banner[0].get_name() << endl;
	banner[0].talent_description();
	cout << "Would you like to give it a try? (y/n): ";
	cin >> accept;
	cout << endl;

	// validate user input
	while (cin.fail() || (accept != 'y' && accept != 'n')) {
		cout << "Invalid command. Try again." << endl;
		cout << "Would you like to give it a try? (y/n): ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> accept;
		cout << endl;

	}


	// generate a random number to pull a character from the banner
	int roll = 0;
	srand(time(nullptr));
	// create a temporary character to be equal to the character pulled from the banner and roll a character
	roll = rand() % 9;
	Character character_pull = banner[roll];
	rand();

	if (accept == 'n') {
		cout << "Too bad. Maybe next time!" << endl;
	}
	else {
		// check if the currency of the user is enough to pull in the gacha
		if (user.get_currency() < 10) {
			cout << "You dont have sufficient currency to roll for a new character. Play arena to win currency!" << endl << endl;
		}
		else {
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "SUMMONING A CHARACTER!" << endl << endl;
			cout << "You summoned " << character_pull.get_rarity() << "* star " << character_pull.get_name() << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			user.set_currency(user.get_currency() - 10);
			// flag variable to cancel the pulling at any time
			char exit = 'a';
			//delete index in case a character is replaced.
			int delete_index = 0;
			while (exit != 'n') {
				// check if the user the maximum number of characters allowed 
				if (user.count_characters() == 10) {
					cout << "Cannot add more characters to your box. Do you want to delete? (y/n): ";
					cin >> exit;
					cout << endl;
					// validate user input
					while (cin.fail() || (exit != 'y' && exit != 'n')) {
						cout << "Invalid command. Try again." << endl;
						cout << "Cannot add more characters to your box. Do you want to delete? (y/n): ";
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cin >> exit;
						cout << endl;
					}

					if (exit == 'n') {
						cout << "Returning to home screen." << endl << endl;
						break;
					}
					cout << endl;
					user.show_box();
					cout << endl << "Which character would you like to delete from your box (enter an integer): ";
					cin >> delete_index;
					// validate user input
					while (cin.fail()) {
						cout << "Invalid command. Try again." << endl;
						cout << "Which character would you like to delete from your box (enter an integer): ";;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cin >> delete_index;
						cout << endl;
					}
					//catch errors produced by invalid index provided by the user to delete
					try {
						Character in_box = user.retrieve_character(delete_index);
						//check rarity of characters to make sure the user really wants to delete the character
						if (in_box > character_pull) {
							cout << in_box.get_name() << " is stronger than " << character_pull.get_name()
								<< ". Do you want to continue (y/n): ";
							cin >> exit;
							// validate user input
							while (cin.fail() || (exit != 'y' && exit != 'n')) {
								cout << "Invalid command. Try again." << endl;
								cout << "Cannot add more characters to your box. Do you want to delete? (y/n): ";
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								cin >> exit;
								cout << endl;
							}
							if (exit == 'n') {
								cout << "Returning to home screen." << endl << endl;
								break;
							}
						}
						user.delete_character(delete_index);
						cout << in_box.get_rarity() << " star "<<in_box.get_name() << " was deleted. ";
					}
					catch (const invalid_argument& e) {
						// error is produced continue next iteration to delete
						cout << e.what() << endl << endl;
						continue;
					}
						
				}
				// add the new character, save progress to user file, and exit the gacha
				user.add_character(character_pull);
				cout << character_pull.get_rarity() << " star "<< character_pull.get_name() << " was acquired." << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
				user.write_to_file(filename);
				exit = 'n';

			}

		}

	}
	return user;
}

/* 
The arena function is the main currency system of the game having two submodes:
single mode : face only one enemy, earn 1 currency for win, and nothing for loss
wave mode : face 3 enemies, earn 10 currency for win, and nothing for loss (3 character party)
*/
User Game::arena(User user, string filename) {

	//create the pool of enemies
	ifstream enemies_file;
	enemies_file.open("enemies.txt");

	vector<Enemy> enemies;


	if (enemies_file) {
		while (!enemies_file.eof()) {
			string name;
			getline(enemies_file, name, '\t');

			int hp;
			enemies_file >> hp;
			enemies_file.ignore();

			int atk;
			enemies_file >> atk;
			enemies_file.ignore();

			string talent;
			getline(enemies_file, talent, '\t');

			string type;
			getline(enemies_file, type, '\t');

			string territory;
			getline(enemies_file, territory, '\t');

			string weakness;
			getline(enemies_file, weakness, '\n');

			Enemy tempo(name, hp, atk, talent,type, territory, weakness);

			enemies.push_back(tempo);
		}
	}
	if (enemies.back().get_name() == "") {
		enemies.pop_back();
	}
  enemies_file.close();

	int gamemode;
	cout << "                               ARENA MODE" << endl << endl;
	cout << "1. Single mode: face 1 enemy [Rewards: 1 programming coin]" << endl << endl;
	cout << "2. Wave mode: face 3 enemies [Rewards: 10 programming coins]" << endl << endl;
	cout << "0. Exit" << endl << endl;
	cout << "Select a gamemode you will like to play (1/2) or 0 to exit: ";
	cin >> gamemode;
	cin.ignore(1000, '\n');
	cout << endl;
	// single mode
	if (gamemode == 1) {
		int selection;
		cout << "                               SINGLE MODE" << endl<< endl;
		cout << "Defeat the enemy and earn 1 programming coin to summon on gacha" << endl << endl;

		//pick a random enemy from the pool to face the fighter
		int enemy_select = 1;
		srand(time(nullptr));
		enemy_select = rand() % 11;
		rand();

		Enemy enemy = enemies[enemy_select];

		sleep_for(seconds(2));
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "Name: " << enemy.get_name() << endl;
		cout << "Weakness: " << enemy.get_weakness() << endl << endl;
		enemy.talent_description();
		cout << endl;

		if (enemy.get_territory() != "none") {
			cout << "Beware " << enemy.get_name() << " governs " << enemy.get_territory() <<
				". This enemy is stronger than usual" << endl << endl;
		}
		cout << "-------------------------------------------------------------------------------" << endl;

		sleep_for(seconds(2));
		user.show_box();
		cout << "Choose your fighter: ";
		cin >> selection;
		cout << endl;
		
		Character fighter("", 1,1,"",1,"");
		// set the character selection and check input
		while (cin.fail() ||(selection > user.count_characters() || selection <= 0)) {
			cout << "You do not have a character at this position. Try again." << endl;
			cout << "Choose your fighter: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> selection;
			cout << endl;
			
		}
		fighter = user.retrieve_character(selection);

		cout << "BATTLE STARTS!" << endl << endl;
		int enemy_hp = enemy.get_hp();
		int enemy_atk = enemy.get_atk();
		int character_hp = fighter.get_hp();
		int character_atk = fighter.get_atk();
		int turn_count = 1;
		int command;

		while (enemy_hp > 0 && character_hp > 0) {
			int turn_order = rand() % 2 + 1;
			int enemy_command = rand() % 3 + 1;
			rand();

			// check for type advantage of a character
			if (enemy.get_weakness() == fighter.get_type()) {
				// increase attack if the chracter has advantage over the enemy
				character_atk += 200;
			}
			
			if (turn_order == 1) {
				sleep_for(seconds(1));
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "TURN " << turn_count << endl << endl;
				cout << "You outspeed the enemy" << endl << endl;
				cout << "Battle" << endl;
				cout << "1.Attack" << "      2.Heal" << endl;
				cout << "3.Retreat" << "     ";
				if (turn_count > 3) {
					cout << "4.Talent";
				}
				cout << endl << endl;
				cout << "Choose a move: ";
				cin >> command;
				cout << endl;

				while (cin.fail() || (command < 0 || command > 4)) {
					cout << "This is not a valid command. Try again" << endl << endl;
					cout << "Battle" << endl;
					cout << "1. Attack" << "      2. Heal" << endl;
					cout << "3. Retreat" << "     ";
					if (turn_count > 3) {
						cout << "4.Talent";
					}
					cout << endl << endl;
					cout << "Choose a move: ";
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin >> command;
				}

				if (command == 1) {
					enemy_hp -= character_atk;
					if (enemy_hp <= 0) {
						cout << "Enemy has been eliminated!" << endl << endl;
					}
					else {
						cout << "You attacked the enemy! hp: " << enemy_hp << endl << endl;
					}
				}
				else if (command == 2) {
					character_hp += 500;
					cout << "Character has been healed! hp: " << character_hp << endl << endl;
				}

				else if (command == 4) {
					cout << "Talent has been activated!" << endl;
					fighter.talent_description();
					sleep_for(seconds(3));
					if (fighter.get_talent() == "Burn") {
						character_atk += 200;
						cout << "Here goes the ultimate spell! BURN activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Freeze") {
						character_hp += 1000;
						cout << "Frostnova lend me your strenght! FREEZE activate" << endl << endl;
					}
					else if(fighter.get_talent() == "Tactics"){
						character_atk += 2000;
						enemy_hp -= 1500;
						cout << "A commander has only the best moves! TACTICS activate" << endl << endl;
					}
					else if (fighter.get_talent()== "Protocol 7") {
						character_atk += 5000;
						cout << "The evil must perish! PROTOCOL 7 activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Algoexpert") {
						character_hp += 2000;
						character_atk += 2000;
						cout << fighter.get_name() << " has activated its ultimate algorithm!" << endl << endl;
					}
					else if (fighter.get_talent() == "Underworld") {
						character_hp += 500;
						character_atk += 500;
						cout << "Darkness come forth! Underworld activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Sanctuary") {
						character_hp += 500;
						cout << "Heavens gate open! Sanctuary activate" << endl << endl;
					}
					else if (fighter.get_talent() == "RapidFire") {
						character_atk *= 2;
						cout << "Target in sight! RapidFire activate" << endl << endl;
					}
					else {
						cout << "This character does not posses a talent. You lose a turn" << endl << endl;
					}
				}
				else if (command == 3) {
					cout << "You flee the battle. Returning to homescreen" << endl << endl;
					break;
				}
				cout << "-------------------------------------------------------------------------------" << endl;
			}
			else if(turn_order == 2){
				sleep_for(seconds(1));
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "TURN " << turn_count << endl << endl;
				// generate the move for the enemy

				cout << enemy.get_name() << " was faster" << endl;

				sleep_for(seconds(2));
				if (enemy_command == 1) {
					character_hp -= enemy_atk;
					if(character_hp <= 0){
						cout << fighter.get_name() << " has been eliminated" << endl << endl;
					}
					else {
						cout << fighter.get_name() << " has been attacked! hp has been reduced to " << character_hp << endl << endl;
					}
				}
				else if (enemy_command == 2) {
					enemy_hp += 500;
					cout << "Enemy has been healed! hp was increased to " << enemy_hp << endl << endl;
					
				}

				else if (enemy_command == 3) {
					cout << "Talent has been activated!" << endl << endl;
					enemy.talent_description();
					sleep_for(seconds(3));
					if (enemy.get_talent() == "Burn") {
						enemy_atk += 200;
						cout << "Here goes the ultimate spell! BURN activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Freeze") {
						enemy_hp += 1000;
						cout << "Frostnova lend me your strenght! FREEZE activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Tactics") {
						enemy_atk += 2000;
						character_hp -= 1500;
						cout << "A commander has only the best moves! TACTICS activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Protocol 7") {
						enemy_atk += 5000;
						cout << "The evil must perish! PROTOCOL 7 activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Algoexpert") {
						enemy_hp += 2000;
						enemy_atk += 2000;
						cout << enemy.get_name() << " has activated its ultimate algorithm!" << endl << endl;
					}
					else if (enemy.get_talent() == "Underworld") {
						enemy_hp += 500;
						enemy_atk += 500;
						cout << "Darkness come forth! Underworld activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Sanctuary") {
						character_hp += 500;
						cout << "Heavens gate open! Sanctuary active" << endl << endl;
					}
					else if (enemy.get_talent() == "RapidFire") {
						enemy_atk *= 2;
						cout << "Target in sight! RapidFire activate" << endl << endl;
					}
					else {
						cout << "Enemy has flinched. It loss a turn" << endl << endl;
					}
				}
				cout << "-------------------------------------------------------------------------------" << endl;
			}
			turn_count += 1;
		}
		// if chararacter hp is 0 then finish the game
		if (character_hp <= 0) {
			cout << "You fought hard, but " << enemy.get_name() << " was stronger" << endl << endl;
			cout << "Returning to home screen" << endl << endl;
			user.set_arena_losses(user.get_arena_losses() + 1);
		}
		// if the user won, then finish the game
		else if(enemy_hp <= 0) {
			cout << "Victory! you defeated " << enemy.get_name() << endl;
			cout << "You have won 1 programming coin to summon on gacha congratulations!" << endl;
			user.set_currency(user.get_currency() + 1);
			user.set_arena_wins(user.get_arena_wins() + 1);
		}

		
	}
	// wave mode
	else if (gamemode == 2) {
		// check if the user has the minimum required number of characters to play wave mode
		if (user.count_characters() < 3) {
			cout << "You do not have enough characters to play wave mode. Minimum number of characters is 3" << endl;
			cout << "Try single mode and earn currency to summon on the gacha!" << endl << endl;
			return user;
		}

		cout << "                               WAVE MODE" << endl << endl;
		cout << "Defeat the horde of enemies and earn 10 programming coins to summon on gacha" << endl << endl;
		
		//pick 3 random enemies from the pool to face the fighter
		int enemy_select1 = 1;
		int enemy_select2 = 1;
		int enemy_select3 = 1;
		srand(time(nullptr));
		enemy_select1 = rand() % 11;
		rand();
		enemy_select2 = rand() % 11;
		rand();
		enemy_select3 = rand() % 11;
		rand();

		// create the enemy horde
		Enemy enemy1 = enemies[enemy_select1];
		Enemy enemy2 = enemies[enemy_select2];
		Enemy enemy3 = enemies[enemy_select3];
		vector<Enemy> horde;
		horde.push_back(enemy1);
		horde.push_back(enemy2);
		horde.push_back(enemy3);

		int num = 1;
		for (Enemy enemy : horde) {
			sleep_for(seconds(2));
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "Enemy " << num << endl << "Name: " <<enemy.get_name() << endl;
			cout << "Weakness: " << enemy.get_weakness() << endl << endl;
			enemy.talent_description();
			cout << endl;

			if (enemy.get_territory() != "none") {
				cout << "Beware " << enemy.get_name() << " governs " << enemy.get_territory() <<
					". This enemy is stronger than usual" << endl << endl;
			}
			cout << "-------------------------------------------------------------------------------" << endl;
			num += 1;
		}

		
		// let the user create his party 
		int selection1, selection2, selection3;
		sleep_for(seconds(2));
		user.show_box();
		cout << "Choose your 1st fighter: ";
		cin >> selection1;
		
		// set the character selection and check input for all three characters
		while (cin.fail() || (selection1 > user.count_characters() || selection1 <= 0)) {
			cout << "You do not have a character at this position. Try again." << endl;
			cout << "Choose your 1st fighter: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> selection1;
			cout << endl;

		}
		cout << endl;
		
		cout << "Choose your 2nd fighter: ";
		cin >> selection2;
		while (cin.fail() || (selection2 > user.count_characters() || selection2 <= 0)) {
			cout << "You do not have a character at this position. Try again." << endl;
			cout << "Choose your 2nd fighter: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> selection2;
			cout << endl;

		}
		cout << endl;
		cout << "Choose your 3rd fighter: ";
		cin >> selection3;
		while (cin.fail() || (selection3 > user.count_characters() || selection3 <= 0)) {
			cout << "You do not have a character at this position. Try again." << endl;
			cout << "Choose your 3rd fighter: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> selection3;
			cout << endl;

		}
		cout << endl;
		// set the characters selection
		Character fighter1 = user.retrieve_character(selection1);
		Character fighter2 = user.retrieve_character(selection2);
		Character fighter3 = user.retrieve_character(selection3);

		// create a common fighter and enemy to battle, initialize to the first instance
		Character fighter = fighter1;
		Enemy enemy = enemy1;

		// start the battle
		cout << "BATTLE STARTS!" << endl << endl;
		int enemy_hp = enemy1.get_hp();
		int enemy_atk = enemy1.get_atk();
		int character_hp = fighter1.get_hp();
		int character_atk = fighter1.get_atk();
		int turn_count = 1;
		int command = 0;

		int death_enemies = 0;
		int death_characters = 0;

		while (death_enemies < 3 && death_characters < 3) {
			int turn_order = rand() % 2 + 1;
			int enemy_command = rand() % 3 + 1;
			rand();

			// check for type advantage of a character
			if (enemy.get_weakness() == fighter.get_type()) {
				// increase attack if the chracter has advantage over the enemy
				character_atk += 200;
			}
			
			if (turn_order == 1) {
				sleep_for(seconds(1));
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "TURN " << turn_count << endl << endl;
				cout << "You outspeed the enemy" << endl << endl;
				cout << "Battle" << endl;
				cout << "1.Attack" << "      2.Heal" << endl;
				cout << "3.Retreat" << "     ";
				if (turn_count > 3) {
					cout << "4.Talent";
				}
				cout << endl << endl;
				
				cout << "Choose a move: ";
				cin >> command;
				cin.ignore(1000, '\n');
				cout << endl;
				
				// check user input 
				while(cin.fail() || (command < 0 || command > 4)) {
					cout << "This is not a valid command. Try again" << endl << endl;
					cout << "Battle" << endl;
					cout << "1.Attack" << "      2.Heal" << endl;
					cout << "3.Retreat" << "     ";
					if (turn_count > 3) {
						cout << "4.Talent";
					}
					cout << endl << endl;
					cout << "Choose a move: ";
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin >> command;
					cout << endl;
				}

				if (command == 1) {
					enemy_hp -= character_atk;
					if (enemy_hp <= 0) {
						cout << "Enemy has been eliminated!" << endl << endl;
					}
					else {
						cout << "You attacked the enemy! hp: " << enemy_hp << endl << endl;
					}
				}
				else if (command == 2) {
					character_hp += 500;
					cout << "Character has been healed! hp: " << character_hp << endl << endl;
				}

				else if (command == 4) {
					cout << "Talent has been activated!" << endl;
					fighter.talent_description();
					sleep_for(seconds(3));
					if (fighter.get_talent() == "Burn") {
						character_atk += 200;
						cout << "Here goes the ultimate spell! BURN activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Freeze") {
						character_hp += 1000;
						cout << "Frostnova lend me your strenght! FREEZE activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Tactics") {
						character_atk += 2000;
						enemy_hp -= 1500;
						cout << "A commander has only the best moves! TACTICS activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Protocol 7") {
						character_atk += 5000;
						cout << "The evil must perish! PROTOCOL 7 activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Algoexpert") {
						character_hp += 2000;
						character_atk += 2000;
						cout << fighter.get_name() << " has activated its ultimate algorithm!" << endl << endl;
					}
					else if (fighter.get_talent() == "Underworld") {
						character_hp += 500;
						character_atk += 500;
						cout << "Darkness come forth! Underworld activate" << endl << endl;
					}
					else if (fighter.get_talent() == "Sanctuary") {
						character_hp += 500;
						cout << "Heavens gate open! Sanctuary activate" << endl << endl;
					}
					else if (fighter.get_talent() == "RapidFire") {
						character_atk *= 2;
						cout << "Target in sight! RapidFire activate" << endl << endl;
					}
					else {
						cout << "This character does not posses a talent. You lose a turn" << endl << endl;
					}
				}
				else if (command == 3) {
					cout << "You flee the battle. Returning to homescreen" << endl << endl;
					cout << "-------------------------------------------------------------------------------" << endl;
					break;
				}
				cout << "-------------------------------------------------------------------------------" << endl;
			}
			else if (turn_order == 2) {
				sleep_for(seconds(1));
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "TURN " << turn_count << endl << endl;
				// generate the move for the enemy

				cout << enemy.get_name() << " was faster" << endl;

				sleep_for(seconds(2));
				if (enemy_command == 1) {
					character_hp -= enemy_atk;
					if (character_hp <= 0) {
						cout << fighter.get_name() << " has been eliminated" << endl << endl;
					}
					else {
						cout << fighter.get_name() << " has been attacked! hp has been reduced to " << character_hp << endl << endl;
					}
				}
				else if (enemy_command == 2) {
					enemy_hp += 500;
					cout << "Enemy has been healed! hp was increased to " << enemy_hp << endl << endl;

				}

				else if (enemy_command == 3) {
					cout << "Talent has been activated!" << endl << endl;
					enemy.talent_description();
					sleep_for(seconds(3));
					if (enemy.get_talent() == "Burn") {
						enemy_atk += 200;
						cout << "Here goes the ultimate spell! BURN activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Freeze") {
						enemy_hp += 1000;
						cout << "Frostnova lend me your strenght! FREEZE activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Tactics") {
						enemy_atk += 2000;
						character_hp -= 1500;
						cout << "A commander has only the best moves! TACTICS activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Protocol 7") {
						enemy_atk += 5000;
						cout << "The evil must perish! PROTOCOL 7 activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Algoexpert") {
						enemy_hp += 2000;
						enemy_atk += 2000;
						cout << enemy.get_name() << " has activated its ultimate algorithm!" << endl << endl;
					}
					else if (enemy.get_talent() == "Underworld") {
						enemy_hp += 500;
						enemy_atk += 500;
						cout << "Darkness come forth! Underworld activate" << endl << endl;
					}
					else if (enemy.get_talent() == "Sanctuary") {
						character_hp += 500;
						cout << "Heavens gate open! Sanctuary active" << endl << endl;
					}
					else if (enemy.get_talent() == "RapidFire") {
						enemy_atk *= 2;
						cout << "Target in sight! RapidFire activate" << endl << endl;
					}
					else {
						cout << "Enemy has flinched. It loss a turn" << endl << endl;
					}
				}
				cout << "-------------------------------------------------------------------------------" << endl;
			}
			turn_count += 1;
			// handle enemy transition from 1 to 2 to 3.
			if (enemy_hp <= 0) {
				death_enemies += 1;
				if (death_enemies == 1) {
					cout << "You have defeated " << enemy1.get_name() << ". Two more to go." << endl;
					enemy = enemy2;
					enemy_hp = enemy2.get_hp();
					enemy_atk = enemy2.get_atk();
				}
				else if (death_enemies == 2) {
					cout << "You have defeated " << enemy2.get_name() << ". One more to go." << endl;
					enemy = enemy3;
					enemy_hp = enemy3.get_hp();
					enemy_atk = enemy3.get_atk();
				}
			}
			// handle character transition from 1 to 2 to 3.
			if (character_hp <= 0) {
				death_characters += 1;
				if (death_characters == 1) {
					cout  << fighter1.get_name() << " has been defeated. " << endl;
					fighter = fighter2;
					character_hp = fighter2.get_hp();
					character_atk = fighter2.get_atk();
				}
				else if (death_characters == 2) {
					cout << fighter2.get_name() << " has been defeated. " << endl;
					fighter = fighter3;
					character_hp = fighter3.get_hp();
					character_atk = fighter3.get_atk();
				}
			}

		}
		// check if player loss by seeing the total number of death characters
		if (death_characters == 3) {
			cout << "You fought hard, but " << enemy.get_name() << " was stronger" << endl << endl;
			cout << "Returning to home screen" << endl << endl;
			user.set_arena_losses(user.get_arena_losses() + 1);
		}
		// check if enemy loss by seeing the total number of death of enemies
		else if(death_enemies == 3) {
			cout << "Victory! you defeated " << enemy.get_name() << endl;
			cout << "You have won 10 programming coin to summon on gacha congratulations!" << endl << endl;
			user.set_currency(user.get_currency() + 10);
			user.set_arena_wins(user.get_arena_wins() + 1);

		}

	}

	else {
		cout << "Exiting arena mode. Returning to home screen" << endl << endl;
	}

	// save currency and return the user to keep game state
	cout << "-------------------------------------------------------------------------------" << endl;
	user.write_to_file(filename);
	return user;
}