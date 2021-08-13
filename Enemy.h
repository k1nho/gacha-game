#ifndef PROGRAMMING_ISEKAI_ENEMY
#define PROGRAMMING_ISEKAI_ENEMY

#include "Character.h"
#include <string>

class Enemy : public Character {
private:
	std::string territory;
	std::string weakness;
public:
	// constructor for enemy class
	Enemy(std::string = "none", int hp = 100, int atk = 100, std::string talent = "none",
		std::string type = "none", std::string territory = "none" , std::string weakness = "none");
	//setters and getters
	void set_territory(std::string);
	std::string get_territory() const;
	void set_weakness(std::string);
	std::string get_weakness() const;
	// polymorphism 
	void talent_description() const;

};




#endif
