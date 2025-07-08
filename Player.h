#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef PLAYER
#define PLAYER
#include "win.h"
#include "Weapon.h"

class Player
{
private:
	int health;                          // 血量
	int stackeddamage = 0;               // 使用药水叠加的伤害
	int shield = 0;                      // 使用能量盾增加的护盾
	int grade = 1;                       // 等级
	int maxhealth = 100;                          // 最大血量
	Weapon* currWeapon;                  // 当前武器
	std::vector<Weapon> weaponInventory; // 武器库
	std::map<std::string, int> bag;      // 背包
	int EXP = 0;

public:
	// 初始化
	Player(int initialHealth) : health(initialHealth), currWeapon(nullptr) {}
	// 获取血量
	int getHealth();
	//复活
	void revive();
	//增加经验
	void addEXP(int aEXP);
	//获取使用药水叠加的伤害
	int getStackeddamage();
	// 遍历背包
	void showBag();
	// 选择道具
	std::string selectProp();
	// 升级，血量+10
	void upGrade();
	// 加入道具到背包
	void joinBag(std::string name);
	// 使用道具
	void useProp(std::string& name);
	// 获取等级
	int getGrade();
	// 更换武器
	void changeWeapon(const std::string& weaponName);

	// 攻击
	int attack();
	// 受伤
	int takeDamage(int amount);
	// 获取当前武器
	Weapon* getCurrentWeapon() const;

	// 添加武器到武器库
	void addWeaponToInventory(Weapon& weapon);
};
#endif

