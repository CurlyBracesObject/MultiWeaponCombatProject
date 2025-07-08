#include "Enemy.h"

int Enemy::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
	return health;
}

int Enemy::attack()
{
	return attackPower;
}

