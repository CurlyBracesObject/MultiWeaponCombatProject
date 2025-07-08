#include "Player.h"

// ��ȡѪ��
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
		std::cout << "����������ǰ�ȼ�:" << grade << std::endl;
		std::cout << "������Ѫ���ָ���+10��Ѫ����ǰѪ��:" << health << std::endl;
	}
	std::cout << "������һ������" << 100 * grade - EXP << "����" << std::endl;
}

int Player::getStackeddamage()
{
	return stackeddamage;
}

// ��������
void Player::showBag()
{
	auto it = bag.begin();
	for (; it != bag.end(); it++)
	{
		std::string name = it->first;
		std::string str = "";
		if (name.compare("EnergyShield") == 0)
		{
			str = "������";
		}
		else if (name.compare("potion") == 0)
		{
			str = "ҩˮ";
		}
		else if (name.compare("Medical") == 0)
		{
			str = "ҽҩ��";
		}
		std::cout << str << "x" << it->second << " ";
	}
	std::cout << std::endl;
}
// ѡ�����
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
// ������Ѫ��+10
void Player::upGrade()
{
	//health = 100 + grade * 10;
	maxhealth += 10;
	health = maxhealth;
	grade++;
}
// ������ߵ�����
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
// ʹ�õ���
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
// ��ȡ�ȼ�
int Player::getGrade()
{
	return grade;
}
// ��������
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

// ����
int Player::attack()
{
	std::string name = "����ǹ";
	if (name.compare(currWeapon->getName()) == 0)
	{
		return currWeapon->getDamage() + currWeapon->getDamage() * 0.2 + stackeddamage;
	}
	return currWeapon->getDamage() + stackeddamage;
}
// ����
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
			std::cout << "�����ܵ�:" << stem - shield << "���˺�����������" << std::endl;
		}
		else {
			std::cout << "�����ܵ�:" << stem - shield << "���˺���ʣ��:" << shield << std::endl;
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

// ��ȡ��ǰ����
Weapon* Player::getCurrentWeapon() const
{
	return currWeapon;
}

// ���������������
void Player::addWeaponToInventory(Weapon& weapon)
{
	weaponInventory.push_back(weapon);
}
