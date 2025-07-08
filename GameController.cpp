#pragma warning(disable: 4244)
#pragma warning(disable: 4996)
#include "GameController.h"

string GameController::playerAttack(Player& pl, Enemy& target)
{
	string s = "";
	int r = currentWeapon->coolOk(nowTime);
	if (r != 0)
	{
		stat = 1;
		s = "武器冷却中，剩余冷却时间:" + to_string(r) + "秒";
		return s;
	}
	currentWeapon->setUseTime(nowTime);
	if (&pl != NULL && &target != NULL)
	{
		int a = pl.attack();
		if (currentEnemy->getType().compare("外星感染生物") == 0 && currentWeapon->getName().compare("能量剑") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "使用" << currentWeapon->getFeature() << ":能量剑 克制" << currentEnemy->getType() << endl;
		}
		else if (currentEnemy->getType().compare("变异人类") == 0 && currentWeapon->getName().compare("重锤") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "使用" << currentWeapon->getFeature() << ":重锤 克制" << currentEnemy->getType() << endl;
		}
		else if (currentEnemy->getType().compare("机械生命体") == 0 && currentWeapon->getName().compare("激光枪") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "使用" << currentWeapon->getFeature() << ":激光枪 克制" << currentEnemy->getType() << endl;
		}
		s = "发起攻击,使用武器:" + currentWeapon->getName() + "\n";
		if (change == 1)
		{
			//int adda = static_cast<int>(round(a * addatt));//这个地方 double转到int 可能丢失数据
			int adda = round(a * addatt);
			int ta = a;
			a = a + adda;
			if (adda > 0)
				s += currentWeapon->getName() + "武器造成" + to_string(ta) + "点伤害,武器切换造成" + to_string(adda) + "点伤害\n";
			change = 0;
			addatt = 0;
		}
		int rec = target.takeDamage(a);
		s += "总共造成" + to_string(a) + "点伤害\n" + "怪物剩余" + to_string(rec) + "点血";
		if (rec == 0)
		{
			s += "\n打败" + target.getType() + ",获得" + to_string(currentEnemy->getEXP()) + "经验";
			stat = 2;
			beat++;
			int random_number1 = uid(dr);
			if (random_number1 == 0)
			{
				currentPlayer->joinBag("EnergyShield");
				gain = "能量盾(可抵挡70%伤害)";
			}
			else if (random_number1 == 1)
			{
				currentPlayer->joinBag("potion");
				gain = "药水(攻击增加20)";
			}
			else if (random_number1 == 2)
			{
				currentPlayer->joinBag("Medical");
				gain = "医药箱(恢复HP)";
			}
			s += "\n怪物掉落道具:" + gain;
			sprop = 1;
		}
	}
	return s;
}

string GameController::enemyAttack(Enemy& target, Player& pl)
{
	string s = "";
	if (&pl != NULL && &target != NULL)
	{
		int a = target.attack();
		if (pl.getHealth() > 0)
		{
			int r = pl.takeDamage(a);
			s = "玩家受到" + to_string(r) + "点伤害";
		}
	}
	return s;
}

void GameController::displayStatus()
{
	cout << "玩家血量：" << currentPlayer->getHealth() << endl;
	cout << "玩家等级：" << currentPlayer->getGrade() << endl;
	if (currentPlayer->getStackeddamage() > 0)
		cout << "攻击力加成：" << currentPlayer->getStackeddamage() << endl;
}

void GameController::startGame()
{
	inums = 0;
	beat = 0;
	sprop = 0;
	playrAtt = "";       // 要输出的玩家攻击字符串
	playrDamage = "";    // 要输出的玩家受伤字符串
	scurrentWeapon = ""; // 当前敌人名
	gain = "";           // 获得的道具
	uid = std::uniform_int_distribution<int>(0, 2);
	dr.seed(time(NULL));                      // 使用当前时间作为随机数生成器的种子
	srand(time(NULL));                        // 使用当前时间作为随机数生成器的种子
	//random_shuffle(nums.begin(), nums.end()); // 打乱怪物出现顺序
	Player* pl = new Player(100);
	Weapon w1("能量剑", 50, 10);//创建对象,武器名、武器伤害、冷却时间
	w1.setCompatibilityBonus(100);  //设置克制敌人时增加的攻击力
	w1.setFeature("快速攻击武器");
	Weapon w2("重锤", 20, 5);
	w2.setCompatibilityBonus(300);
	w2.setFeature("重击型武器");
	Weapon w3("激光枪", 80, 20);
	w3.setCompatibilityBonus(500);
	w3.setFeature("穿透性武器");
	//添加派生动作
	ds.add("能量剑", "重锤", 0.38);//能量剑切换到重锤增加38%伤害
	ds.add("能量剑", "激光枪", 0.38);
	ds.add("重锤", "能量剑", 0.25);
	ds.add("重锤", "激光枪", 0.25);
	ds.add("激光枪", "重锤", 0.5);
	ds.add("激光枪", "能量剑", 0.5);
	pl->addWeaponToInventory(w1);
	pl->addWeaponToInventory(w2);
	pl->addWeaponToInventory(w3);
	pl->changeWeapon("能量剑");
	Enemy* en1 = new Enemy("", 0, 10, 0);
	currentEnemy = en1;
	currentPlayer = pl;
	currentWeapon = pl->getCurrentWeapon();
	updateGameState();
}

void GameController::showEnemy()
{
	cout << "敌人:" << currentEnemy->getType() << " 血量:" << currentEnemy->getHealth() << endl;
}

void GameController::showEnd()
{
	std::cout << "等级：" << currentPlayer->getGrade() << std::endl;
	std::cout << "击杀数量：" << beat << std::endl;
	cout << "获得道具:";
	currentPlayer->showBag();
}

int GameController::updateGameState()
{
	if (currentPlayer->getHealth() <= 0)
	{
		cout << "玩家死亡" << endl;
		showEnd();
		cout << "1.复活 2.退出游戏" << endl;
		char s = getch();
		if (s == '1')
		{
			currentPlayer->revive();
			return 0;
		}
		else if (s == '2')
		{
			exit(0);
		}
	}
	if (currentEnemy->getHealth() <= 0)
	{
		if (currentEnemy != NULL)
			currentPlayer->addEXP(currentEnemy->getEXP());
		delete currentEnemy;
		if (inums >= 3)
		{
			cout << "打败全部怪物" << endl;
			showEnd();
			cout << "1.重玩 2.退出游戏" << endl;
			char s = getch();
			if (s == '1')
			{
				delete currentPlayer;
				return 1;
			}
			else if (s == '2')
			{
				exit(0);
			}
		}
		int random_number = nums[inums++];
		Enemy* en = NULL;
		if (random_number == 0)
		{
			string type = "外星感染生物";
			en = new Enemy(type, 400, 10, 50);
		}
		else if (random_number == 1)
		{
			string type = "变异人类";
			en = new Enemy(type, 800, 20, 75);
		}
		else if (random_number == 2)
		{
			string type = "机械生命体";
			en = new Enemy(type, 1000, 30, 100);
		}
		currentEnemy = en;
		return 3;
	}
	return 2;
}

void GameController::showWeapon()
{
	currentWeapon = currentPlayer->getCurrentWeapon();
	int stime = currentWeapon->coolOk(nowTime);
	if (stime == 0)
	{
		scurrentWeapon = currentWeapon->getName() + " 可用";
	}
	else
	{
		scurrentWeapon = currentWeapon->getName() + " 冷却中，剩余冷却时间:" + to_string(stime);
	}
	cout << "当前武器：" << scurrentWeapon << endl;
	scurrentWeapon = "";
}

void GameController::useProp()
{
	string rec = currentPlayer->selectProp();
	string pp;
	if (prop == 0)
	{
		pp = "能量盾，抵挡%70杀伤";
		cout << "使用道具:" << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
	else if (prop == 1)
	{
		pp = "药水，攻击力曾强";
		cout << "使用道具:" << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
	else if (prop == 2)
	{
		pp = "医药箱，血量恢复满";
		cout << "使用道具:" << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
}

int GameController::executePlayerAction()
{
	cout << "我方回合" << endl;
	showEnemy();
	if (sprop == 1)
	{
		cout << "是否使用背包里的物品?(yes/no):";
		string scin;
		cin >> scin;
		if (scin.compare("yes") == 0)
		{
			useProp();
		}
		sprop = 0;
	}
	displayStatus();
	cout << "1.能量剑 2.重锤 3.激光枪 4.使用道具 5.不出战 空格:攻击 ESC:退出游戏" << endl;
	while (1)
	{
		char c = getch();
		if (c == '1')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("能量剑") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "能量剑");
			}
			currentPlayer->changeWeapon("能量剑");
			showWeapon();
			continue;
		}
		else if (c == '2')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("重锤") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "重锤");
			}
			currentPlayer->changeWeapon("重锤");
			showWeapon();
			continue;
		}
		else if (c == '3')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("激光枪") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "激光枪");
			}
			currentPlayer->changeWeapon("激光枪");
			showWeapon();
			continue;
		}
		else if (c == '4')
		{
			useProp();
		}
		else if (c == '5')
		{
			cout << "\n敌方回合" << endl;
			cout << currentEnemy->getType() << "对玩家攻击" << endl;
			playrDamage = enemyAttack(*currentEnemy, *currentPlayer);
			if (updateGameState() == 2)
				cout << playrDamage << endl;
			break;
		}
		else if (c == ' ')
		{
			playrAtt = playerAttack(*currentPlayer, *currentEnemy);
			cout << playrAtt << endl;
			int r = updateGameState();
			if (r == 1)
				return 1;
			if (stat == 1)
			{
				stat = 0;
				continue;
			}
			else if (stat == 2)
			{
				stat = 0;
				return 4;
			}
			else
			{
				cout << "\n敌方回合" << endl;
				cout << currentEnemy->getType() << "对玩家攻击" << endl;
				playrDamage = enemyAttack(*currentEnemy, *currentPlayer);
				if (updateGameState() == 2)
					cout << playrDamage << endl;
				break;
			}
		}
		else if (c == 27)
		{
			showEnd();
			exit(0);
		}
	}
	return 0;
}
