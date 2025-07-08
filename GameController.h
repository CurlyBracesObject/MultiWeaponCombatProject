#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include <random>  
#include <chrono> 
#include <algorithm>  
#include "Enemy.h"
#include "Player.h"
#include "DerivativeSystem.h"
using namespace std;

//游戏控制类
class GameController {
private:
	Player* currentPlayer = NULL;//当前玩家
	Enemy* currentEnemy = NULL;//当前敌人
	string playrAtt = "";//要输出的玩家攻击字符串
	string playrDamage = "";//要输出的玩家受伤字符串
	string scurrentWeapon = "";//当前敌人名
	string gain = ""; //获得的道具
	Weapon* currentWeapon = NULL;//当前敌人
	int change = 0;//是否触发派生动作
	double addatt = 0;//派生动作附加的攻击力
	int beat = 0;//击杀数量
	int stat = 0;//攻击后的状态
	DerivativeSystem ds;//派生动作对象
	std::default_random_engine dr;//用于生成随机数
	std::uniform_int_distribution<int> uid;//用于生成随机数
	std::vector<int> nums = { 0, 1, 2 };//表示三种怪物的顺序
	int inums = 0;//当前出现的怪
	int sprop = 0;//掉落道具标志
public:
	int volatile nowTime = 0;//当前时间
	string playerAttack(Player& pl, Enemy& target);//玩家攻击敌人
	string enemyAttack(Enemy& target, Player& pl);//敌人攻击玩家
	void displayStatus();//显示玩家状态
	void startGame();//开始游戏
	int updateGameState();//更新状态
	int executePlayerAction();//执行玩家动作
	void showEnemy();//显示当前敌人
	void showWeapon();//显示武器
	void useProp();//使用道具
	void showEnd();//结束时的显示
};

