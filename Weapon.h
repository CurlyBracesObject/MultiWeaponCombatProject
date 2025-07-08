#pragma once

#include <iostream>
#include <string>

#ifndef WEAPON
#define WEAPON

//武器类
class Weapon {
private:
	std::string name;//武器名
	int damage;//伤害
	int cooldown;//冷却时间
	int useTime = -50;//使用的时刻
	std::string Feature;//针对不同敌人类型的特性
	int compatibilityBonus=0;//兼容性加成
public:
	//初始化
	Weapon(std::string name, int damage, int cooldown) : name(name), damage(damage), cooldown(cooldown) {}
	void setFeature(std::string Feature);
	std::string getFeature();
	void setCompatibilityBonus(int compatibilityBonus);
	int getCompatibilityBonus();
	int attack();//攻击
	void setUseTime(int time);//设置使用的时刻
	int coolOk(int time);//是否冷却完毕
	std::string getName();//获取武器名
	int getDamage();//获取伤害
};
#endif

