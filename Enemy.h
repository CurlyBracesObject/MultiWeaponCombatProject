#pragma once

#include <iostream>  
#include <string>  

#ifndef ENEMY
#define ENEMY

//敌人类
class Enemy {
private:
	std::string type;        // 敌人类型 
	int health;              // 敌人血量  
	int attackPower;         // 敌人攻击力  
	int EXP;                //打败敌人获得的经验
public:
	// 初始化 
	Enemy(std::string type, int health, int attackPower, int EXP)
		: type(type), health(health), attackPower(attackPower), EXP(EXP) {}

	int getEXP() const {
		return EXP;
	}

	// 获取类型
	std::string getType() const {
		return type;
	}

	// 获取血量   
	int getHealth() const {
		return health;
	}

	// 获取攻击力  
	int getAttackPower() const {
		return attackPower;
	}

	// 攻击
	int attack();

	// 受伤
	int takeDamage(int damage);
};
#endif

