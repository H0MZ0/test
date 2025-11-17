#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : name("Hamza"){
	ClapTrap::name = name + "_clap_name";
	std::cout << "DiamondTrap " << ClapTrap::name << " constructed" << std::endl;
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 30;
}

DiamondTrap::DiamondTrap(std::string name) : name(name){
	ClapTrap::name = name + "_clap_name";
	std::cout << "DiamondTrap " << ClapTrap::name << " constructed" << std::endl;
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 30;
}

void DiamondTrap::whoAmI(){
	std::cout << "My DiamondTrap name is " << name << std::endl;
	std::cout << "My ClapTrap name is " << ClapTrap::name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) :
	ClapTrap(other), FragTrap(other), ScavTrap(other) {
	// this->attackDamage = other.attackDamage;
	// this->energyPoints = other.energyPoints;
	// this->hitPoints = other.hitPoints;
	this->name = other.name;
	ClapTrap::name = other.ClapTrap::name;

	std::cout << "DiamondTrap " << name << " copy constructed" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap &other) {
	std::cout << "DiamondTrap copy assignment operator called" << std::endl;
	if (this != &other){
		ClapTrap::operator=(other);
		// this->attackDamage = other.attackDamage;
		// this->energyPoints = other.energyPoints;
		// this->hitPoints = other.hitPoints;
		this->name = other.name;
		ClapTrap::name = other.ClapTrap::name;
	}
	return *this;
}

void	DiamondTrap::attack(const std::string& target){
	ScavTrap::attack(target);
}

DiamondTrap::~DiamondTrap(){
	std::cout << "DiamondTrap " << name << " destructed" << std::endl;
}