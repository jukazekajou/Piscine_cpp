#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon)
{
	_name = name;
	_weapon = &weapon;
}

void HumanA::attack()
{
	if (_weapon != NULL)
		std::cout << _name + " attacks with his " + _weapon->getType() + "\n";
	else
		std::cout << _name + " got no weapon, bad idea, bad idea ...\n";
}
