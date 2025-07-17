#include "Player.h"
// 获取血量
int Player::getHealth()
{
	return health;
}
void Player::revive()
{
	maxhealth = 100;
	health = 100;
}
void Player::addEXP(int aEXP)
{
	EXP += aEXP;
	if (EXP >= 100 * grade)
	{
		upGrade();
		std::cout << "Level up! Current level: " << grade << std::endl;
		std::cout << "HP restored and +10 HP after leveling up, current HP: " << health << std::endl;
	}
	std::cout << "Need " << 100 * grade - EXP << " more EXP to next level" << std::endl;
}
int Player::getStackeddamage()
{
	return stackeddamage;
}
// 遍历背包
void Player::showBag()
{
	auto it = bag.begin();
	for (; it != bag.end(); it++)
	{
		std::string name = it->first;
		std::string str = "";
		if (name.compare("EnergyShield") == 0)
		{
			str = "Energy Shield";
		}
		else if (name.compare("potion") == 0)
		{
			str = "Potion";
		}
		else if (name.compare("Medical") == 0)
		{
			str = "Medical Kit";
		}
		std::cout << str << "x" << it->second << " ";
	}
	std::cout << std::endl;
}
// 选择道具
std::string Player::selectProp()
{
	createWindow(bag);
	if (prop == 0)
	{
		return "EnergyShield";
	}
	else if (prop == 1)
	{
		return "potion";
	}
	else if (prop == 2)
	{
		return "Medical";
	}
	return "";
}
// 升级，血量+10
void Player::upGrade()
{
	//health = 100 + grade * 10;
	maxhealth += 10;
	health = maxhealth;
	grade++;
}
// 加入道具到背包
void Player::joinBag(std::string name)
{
	auto it = bag.find(name);
	if (it != bag.end())
	{
		it->second++;
	}
	else
	{
		bag[name] = 1;
	}
}
// 使用道具
void Player::useProp(std::string& name)
{
	auto it = bag.find(name);
	if (it != bag.end())
	{
		it->second--;
		if (name.compare("EnergyShield") == 0)
		{
			shield = 100;
		}
		else if (name.compare("potion") == 0)
		{
			stackeddamage = 20;
		}
		else if (name.compare("Medical") == 0)
		{
			health = maxhealth;
		}
		if (it->second == 0)
		{
			bag.erase(name);
		}
	}
}
// 获取等级
int Player::getGrade()
{
	return grade;
}
// 更换武器
void Player::changeWeapon(const std::string& weaponName)
{
	for (auto& weapon : weaponInventory)
	{
		if (weapon.getName() == weaponName)
		{
			currWeapon = &weapon;
			return;
		}
	}
}
// 攻击
int Player::attack()
{
	std::string name = "Laser Gun";
	if (name.compare(currWeapon->getName()) == 0)
	{
		return currWeapon->getDamage() + currWeapon->getDamage() * 0.2 + stackeddamage;
	}
	return currWeapon->getDamage() + stackeddamage;
}
// 受伤
int Player::takeDamage(int amount)
{
	int tem = health;
	if (shield > 0)
	{
		int stem = shield;
		health -= amount * 0.3;
		shield -= amount * 0.7;
		if (shield <= 0) {
			shield = 0;
			std::cout << "Shield took " << stem - shield << " damage, shield broken" << std::endl;
		}
		else {
			std::cout << "Shield took " << stem - shield << " damage, remaining: " << shield << std::endl;
		}
	}
	else
	{
		health -= amount;
	}
	if (health <= 0)
	{
		health = 0;
	}
	return tem - health;
}
// 获取当前武器
Weapon* Player::getCurrentWeapon() const
{
	return currWeapon;
}
// 添加武器到武器库
void Player::addWeaponToInventory(Weapon& weapon)
{
	weaponInventory.push_back(weapon);
}