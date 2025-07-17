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
		s = "Weapon cooling down, remaining time: " + to_string(r) + " seconds";
		return s;
	}
	currentWeapon->setUseTime(nowTime);
	if (&pl != NULL && &target != NULL)
	{
		int a = pl.attack();
		if (currentEnemy->getType().compare("Alien Infected") == 0 && currentWeapon->getName().compare("Energy Sword") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "Using " << currentWeapon->getFeature() << ": Energy Sword counters " << currentEnemy->getType() << endl;
		}
		else if (currentEnemy->getType().compare("Mutant Human") == 0 && currentWeapon->getName().compare("Heavy Hammer") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "Using " << currentWeapon->getFeature() << ": Heavy Hammer counters " << currentEnemy->getType() << endl;
		}
		else if (currentEnemy->getType().compare("Mechanical Lifeform") == 0 && currentWeapon->getName().compare("Laser Gun") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "Using " << currentWeapon->getFeature() << ": Laser Gun counters " << currentEnemy->getType() << endl;
		}
		s = "Launching attack, using weapon: " + currentWeapon->getName() + "\n";
		if (change == 1)
		{
			//int adda = static_cast<int>(round(a * addatt));//这个地方 double转到int 可能丢失数据
			int adda = round(a * addatt);
			int ta = a;
			a = a + adda;
			if (adda > 0)
				s += currentWeapon->getName() + " weapon deals " + to_string(ta) + " damage, weapon switch deals " + to_string(adda) + " damage\n";
			change = 0;
			addatt = 0;
		}
		int rec = target.takeDamage(a);
		s += "Total damage dealt: " + to_string(a) + "\n" + "Monster remaining HP: " + to_string(rec);
		if (rec == 0)
		{
			s += "\nDefeated " + target.getType() + ", gained " + to_string(currentEnemy->getEXP()) + " EXP";
			stat = 2;
			beat++;
			int random_number1 = uid(dr);
			if (random_number1 == 0)
			{
				currentPlayer->joinBag("EnergyShield");
				gain = "Energy Shield (blocks 70% damage)";
			}
			else if (random_number1 == 1)
			{
				currentPlayer->joinBag("potion");
				gain = "Potion (attack +20)";
			}
			else if (random_number1 == 2)
			{
				currentPlayer->joinBag("Medical");
				gain = "Medical Kit (restores HP)";
			}
			s += "\nMonster dropped item: " + gain;
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
			s = "Player takes " + to_string(r) + " damage";
		}
	}
	return s;
}

void GameController::displayStatus()
{
	cout << "Player HP: " << currentPlayer->getHealth() << endl;
	cout << "Player Level: " << currentPlayer->getGrade() << endl;
	if (currentPlayer->getStackeddamage() > 0)
		cout << "Attack Bonus: " << currentPlayer->getStackeddamage() << endl;
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
	Weapon w1("Energy Sword", 50, 10);//创建对象,武器名、武器伤害、冷却时间
	w1.setCompatibilityBonus(100);  //设置克制敌人时增加的攻击力
	w1.setFeature("Fast Attack Weapon");
	Weapon w2("Heavy Hammer", 20, 5);
	w2.setCompatibilityBonus(300);
	w2.setFeature("Heavy Strike Weapon");
	Weapon w3("Laser Gun", 80, 20);
	w3.setCompatibilityBonus(500);
	w3.setFeature("Piercing Weapon");
	//添加派生动作
	ds.add("Energy Sword", "Heavy Hammer", 0.38);//能量剑切换到重锤增加38%伤害
	ds.add("Energy Sword", "Laser Gun", 0.38);
	ds.add("Heavy Hammer", "Energy Sword", 0.25);
	ds.add("Heavy Hammer", "Laser Gun", 0.25);
	ds.add("Laser Gun", "Heavy Hammer", 0.5);
	ds.add("Laser Gun", "Energy Sword", 0.5);
	pl->addWeaponToInventory(w1);
	pl->addWeaponToInventory(w2);
	pl->addWeaponToInventory(w3);
	pl->changeWeapon("Energy Sword");
	Enemy* en1 = new Enemy("", 0, 10, 0);
	currentEnemy = en1;
	currentPlayer = pl;
	currentWeapon = pl->getCurrentWeapon();
	updateGameState();
}

void GameController::showEnemy()
{
	cout << "Enemy: " << currentEnemy->getType() << " HP: " << currentEnemy->getHealth() << endl;
}

void GameController::showEnd()
{
	std::cout << "Level: " << currentPlayer->getGrade() << std::endl;
	std::cout << "Kills: " << beat << std::endl;
	cout << "Items obtained: ";
	currentPlayer->showBag();
}

int GameController::updateGameState()
{
	if (currentPlayer->getHealth() <= 0)
	{
		cout << "Player died" << endl;
		showEnd();
		cout << "1.Revive 2.Exit game" << endl;
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
			cout << "Defeated all monsters" << endl;
			showEnd();
			cout << "1.Play again 2.Exit game" << endl;
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
			string type = "Alien Infected";
			en = new Enemy(type, 400, 10, 50);
		}
		else if (random_number == 1)
		{
			string type = "Mutant Human";
			en = new Enemy(type, 800, 20, 75);
		}
		else if (random_number == 2)
		{
			string type = "Mechanical Lifeform";
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
		scurrentWeapon = currentWeapon->getName() + " Ready";
	}
	else
	{
		scurrentWeapon = currentWeapon->getName() + " Cooling down, remaining time: " + to_string(stime);
	}
	cout << "Current weapon: " << scurrentWeapon << endl;
	scurrentWeapon = "";
}

void GameController::useProp()
{
	string rec = currentPlayer->selectProp();
	string pp;
	if (prop == 0)
	{
		pp = "Energy Shield, blocks 70% damage";
		cout << "Using item: " << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
	else if (prop == 1)
	{
		pp = "Potion, attack power enhanced";
		cout << "Using item: " << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
	else if (prop == 2)
	{
		pp = "Medical Kit, HP fully restored";
		cout << "Using item: " << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
}

int GameController::executePlayerAction()
{
	cout << "Player turn" << endl;
	showEnemy();
	if (sprop == 1)
	{
		cout << "Use item from inventory? (yes/no): ";
		string scin;
		cin >> scin;
		if (scin.compare("yes") == 0)
		{
			useProp();
		}
		sprop = 0;
	}
	displayStatus();
	cout << "1.Energy Sword 2.Heavy Hammer 3.Laser Gun 4.Use item 5.Skip turn Space:Attack ESC:Exit game" << endl;
	while (1)
	{
		char c = getch();
		if (c == '1')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("Energy Sword") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "Energy Sword");
			}
			currentPlayer->changeWeapon("Energy Sword");
			showWeapon();
			continue;
		}
		else if (c == '2')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("Heavy Hammer") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "Heavy Hammer");
			}
			currentPlayer->changeWeapon("Heavy Hammer");
			showWeapon();
			continue;
		}
		else if (c == '3')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("Laser Gun") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "Laser Gun");
			}
			currentPlayer->changeWeapon("Laser Gun");
			showWeapon();
			continue;
		}
		else if (c == '4')
		{
			useProp();
		}
		else if (c == '5')
		{
			cout << "\nEnemy turn" << endl;
			cout << currentEnemy->getType() << " attacks player" << endl;
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
				cout << "\nEnemy turn" << endl;
				cout << currentEnemy->getType() << " attacks player" << endl;
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