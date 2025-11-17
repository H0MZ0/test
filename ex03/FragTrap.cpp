#include "FragTrap.hpp"

FragTrap::FragTrap() {
	std::cout << "Default FragTrap constructor called!" << std::endl;
	name = "Hamza";
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
	std::cout << "FragTrap " << name << " copy constructed" << std::endl;
	if (this != &other){
		this->attackDamage = other.attackDamage;
		this->energyPoints = other.energyPoints;
		this->hitPoints = other.hitPoints;
		this->name = other.name;
	}
}

FragTrap& FragTrap::operator=(const FragTrap &other) {
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return *this;
}

FragTrap::FragTrap(std::string Name) : ClapTrap(Name){
	std::cout << "FragTrap " << name << " constructed" << std::endl;
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
}

void FragTrap::highFivesGuys(void){
	std::cout << "FragTrap " << name << " is requesting a high five!" << std::endl;
}

FragTrap::~FragTrap(){
	std::cout << "FragTrap " << name << " destructed" << std::endl;
}