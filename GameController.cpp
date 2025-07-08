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
		s = "������ȴ�У�ʣ����ȴʱ��:" + to_string(r) + "��";
		return s;
	}
	currentWeapon->setUseTime(nowTime);
	if (&pl != NULL && &target != NULL)
	{
		int a = pl.attack();
		if (currentEnemy->getType().compare("���Ǹ�Ⱦ����") == 0 && currentWeapon->getName().compare("������") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "ʹ��" << currentWeapon->getFeature() << ":������ ����" << currentEnemy->getType() << endl;
		}
		else if (currentEnemy->getType().compare("��������") == 0 && currentWeapon->getName().compare("�ش�") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "ʹ��" << currentWeapon->getFeature() << ":�ش� ����" << currentEnemy->getType() << endl;
		}
		else if (currentEnemy->getType().compare("��е������") == 0 && currentWeapon->getName().compare("����ǹ") == 0)
		{
			a += currentWeapon->getCompatibilityBonus();
			cout << "ʹ��" << currentWeapon->getFeature() << ":����ǹ ����" << currentEnemy->getType() << endl;
		}
		s = "���𹥻�,ʹ������:" + currentWeapon->getName() + "\n";
		if (change == 1)
		{
			//int adda = static_cast<int>(round(a * addatt));//����ط� doubleת��int ���ܶ�ʧ����
			int adda = round(a * addatt);
			int ta = a;
			a = a + adda;
			if (adda > 0)
				s += currentWeapon->getName() + "�������" + to_string(ta) + "���˺�,�����л����" + to_string(adda) + "���˺�\n";
			change = 0;
			addatt = 0;
		}
		int rec = target.takeDamage(a);
		s += "�ܹ����" + to_string(a) + "���˺�\n" + "����ʣ��" + to_string(rec) + "��Ѫ";
		if (rec == 0)
		{
			s += "\n���" + target.getType() + ",���" + to_string(currentEnemy->getEXP()) + "����";
			stat = 2;
			beat++;
			int random_number1 = uid(dr);
			if (random_number1 == 0)
			{
				currentPlayer->joinBag("EnergyShield");
				gain = "������(�ɵֵ�70%�˺�)";
			}
			else if (random_number1 == 1)
			{
				currentPlayer->joinBag("potion");
				gain = "ҩˮ(��������20)";
			}
			else if (random_number1 == 2)
			{
				currentPlayer->joinBag("Medical");
				gain = "ҽҩ��(�ָ�HP)";
			}
			s += "\n����������:" + gain;
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
			s = "����ܵ�" + to_string(r) + "���˺�";
		}
	}
	return s;
}

void GameController::displayStatus()
{
	cout << "���Ѫ����" << currentPlayer->getHealth() << endl;
	cout << "��ҵȼ���" << currentPlayer->getGrade() << endl;
	if (currentPlayer->getStackeddamage() > 0)
		cout << "�������ӳɣ�" << currentPlayer->getStackeddamage() << endl;
}

void GameController::startGame()
{
	inums = 0;
	beat = 0;
	sprop = 0;
	playrAtt = "";       // Ҫ�������ҹ����ַ���
	playrDamage = "";    // Ҫ�������������ַ���
	scurrentWeapon = ""; // ��ǰ������
	gain = "";           // ��õĵ���
	uid = std::uniform_int_distribution<int>(0, 2);
	dr.seed(time(NULL));                      // ʹ�õ�ǰʱ����Ϊ�����������������
	srand(time(NULL));                        // ʹ�õ�ǰʱ����Ϊ�����������������
	//random_shuffle(nums.begin(), nums.end()); // ���ҹ������˳��
	Player* pl = new Player(100);
	Weapon w1("������", 50, 10);//��������,�������������˺�����ȴʱ��
	w1.setCompatibilityBonus(100);  //���ÿ��Ƶ���ʱ���ӵĹ�����
	w1.setFeature("���ٹ�������");
	Weapon w2("�ش�", 20, 5);
	w2.setCompatibilityBonus(300);
	w2.setFeature("�ػ�������");
	Weapon w3("����ǹ", 80, 20);
	w3.setCompatibilityBonus(500);
	w3.setFeature("��͸������");
	//�����������
	ds.add("������", "�ش�", 0.38);//�������л����ش�����38%�˺�
	ds.add("������", "����ǹ", 0.38);
	ds.add("�ش�", "������", 0.25);
	ds.add("�ش�", "����ǹ", 0.25);
	ds.add("����ǹ", "�ش�", 0.5);
	ds.add("����ǹ", "������", 0.5);
	pl->addWeaponToInventory(w1);
	pl->addWeaponToInventory(w2);
	pl->addWeaponToInventory(w3);
	pl->changeWeapon("������");
	Enemy* en1 = new Enemy("", 0, 10, 0);
	currentEnemy = en1;
	currentPlayer = pl;
	currentWeapon = pl->getCurrentWeapon();
	updateGameState();
}

void GameController::showEnemy()
{
	cout << "����:" << currentEnemy->getType() << " Ѫ��:" << currentEnemy->getHealth() << endl;
}

void GameController::showEnd()
{
	std::cout << "�ȼ���" << currentPlayer->getGrade() << std::endl;
	std::cout << "��ɱ������" << beat << std::endl;
	cout << "��õ���:";
	currentPlayer->showBag();
}

int GameController::updateGameState()
{
	if (currentPlayer->getHealth() <= 0)
	{
		cout << "�������" << endl;
		showEnd();
		cout << "1.���� 2.�˳���Ϸ" << endl;
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
			cout << "���ȫ������" << endl;
			showEnd();
			cout << "1.���� 2.�˳���Ϸ" << endl;
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
			string type = "���Ǹ�Ⱦ����";
			en = new Enemy(type, 400, 10, 50);
		}
		else if (random_number == 1)
		{
			string type = "��������";
			en = new Enemy(type, 800, 20, 75);
		}
		else if (random_number == 2)
		{
			string type = "��е������";
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
		scurrentWeapon = currentWeapon->getName() + " ����";
	}
	else
	{
		scurrentWeapon = currentWeapon->getName() + " ��ȴ�У�ʣ����ȴʱ��:" + to_string(stime);
	}
	cout << "��ǰ������" << scurrentWeapon << endl;
	scurrentWeapon = "";
}

void GameController::useProp()
{
	string rec = currentPlayer->selectProp();
	string pp;
	if (prop == 0)
	{
		pp = "�����ܣ��ֵ�%70ɱ��";
		cout << "ʹ�õ���:" << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
	else if (prop == 1)
	{
		pp = "ҩˮ����������ǿ";
		cout << "ʹ�õ���:" << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
	else if (prop == 2)
	{
		pp = "ҽҩ�䣬Ѫ���ָ���";
		cout << "ʹ�õ���:" << pp << endl;
		currentPlayer->useProp(rec);
		prop = -1;
	}
}

int GameController::executePlayerAction()
{
	cout << "�ҷ��غ�" << endl;
	showEnemy();
	if (sprop == 1)
	{
		cout << "�Ƿ�ʹ�ñ��������Ʒ?(yes/no):";
		string scin;
		cin >> scin;
		if (scin.compare("yes") == 0)
		{
			useProp();
		}
		sprop = 0;
	}
	displayStatus();
	cout << "1.������ 2.�ش� 3.����ǹ 4.ʹ�õ��� 5.����ս �ո�:���� ESC:�˳���Ϸ" << endl;
	while (1)
	{
		char c = getch();
		if (c == '1')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("������") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "������");
			}
			currentPlayer->changeWeapon("������");
			showWeapon();
			continue;
		}
		else if (c == '2')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("�ش�") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "�ش�");
			}
			currentPlayer->changeWeapon("�ش�");
			showWeapon();
			continue;
		}
		else if (c == '3')
		{
			change = 1;
			if (currentPlayer->getCurrentWeapon()->getName().compare("����ǹ") != 0)
			{
				addatt = ds.performDerivativeAction(currentPlayer->getCurrentWeapon()->getName(), "����ǹ");
			}
			currentPlayer->changeWeapon("����ǹ");
			showWeapon();
			continue;
		}
		else if (c == '4')
		{
			useProp();
		}
		else if (c == '5')
		{
			cout << "\n�з��غ�" << endl;
			cout << currentEnemy->getType() << "����ҹ���" << endl;
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
				cout << "\n�з��غ�" << endl;
				cout << currentEnemy->getType() << "����ҹ���" << endl;
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
