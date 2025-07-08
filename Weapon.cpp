#include "Weapon.h"

int Weapon::attack()
{
	return damage;
}

void Weapon::setUseTime(int time)
{
	this->useTime = time;
}

int Weapon::coolOk(int time)
{
	int rec = time - useTime;
	if (rec >= cooldown)
	{
		return 0;
	}
	return cooldown - rec;
}

std::string Weapon::getName()
{
	return this->name;
}

int Weapon::getDamage()
{
	return damage;
}

void  Weapon::setFeature(std::string Feature)
{
	this->Feature = Feature;
}
std::string  Weapon::getFeature()
{
	return Feature;
}
void  Weapon::setCompatibilityBonus(int compatibilityBonus)
{
	this->compatibilityBonus = compatibilityBonus;
}
int  Weapon::getCompatibilityBonus()
{
	return compatibilityBonus;
}
