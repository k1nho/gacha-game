#ifndef PROGRAMMING_ISEKAI_CHARACTER
#define PROGRAMMING_ISEKAI_CHARACTER

#include <string>

class Character {
private:
	int rarity;
protected:
	std::string name;
	int hp;
	int atk;
	std::string talent;
	std::string type;
public:
	//constructors
	Character(std::string name = "none", int hp = 100, int atk = 100, std::string talent = "none",
		int rarity = 1, std::string type = "none");
	Character(std::string name = "none", int hp = 100, int atk = 100, std::string talent = "none",
		 std::string type = "none");
	//setters and getters
	void set_name(std::string);
	std::string get_name() const;
	void set_hp(int);
	int get_hp() const;
	void set_atk(int);
	int get_atk() const;
	void set_talent(std::string);
	std::string get_talent() const;
	void set_rarity(int);
	int get_rarity() const;
	void set_type(std::string);
	std::string get_type() const;
	// virtual function (polymorphism)
	virtual void talent_description();
	//overloaded operator
	bool operator> (const Character& right);
};


#endif
