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

//��Ϸ������
class GameController {
private:
	Player* currentPlayer = NULL;//��ǰ���
	Enemy* currentEnemy = NULL;//��ǰ����
	string playrAtt = "";//Ҫ�������ҹ����ַ���
	string playrDamage = "";//Ҫ�������������ַ���
	string scurrentWeapon = "";//��ǰ������
	string gain = ""; //��õĵ���
	Weapon* currentWeapon = NULL;//��ǰ����
	int change = 0;//�Ƿ񴥷���������
	double addatt = 0;//�����������ӵĹ�����
	int beat = 0;//��ɱ����
	int stat = 0;//�������״̬
	DerivativeSystem ds;//������������
	std::default_random_engine dr;//�������������
	std::uniform_int_distribution<int> uid;//�������������
	std::vector<int> nums = { 0, 1, 2 };//��ʾ���ֹ����˳��
	int inums = 0;//��ǰ���ֵĹ�
	int sprop = 0;//������߱�־
public:
	int volatile nowTime = 0;//��ǰʱ��
	string playerAttack(Player& pl, Enemy& target);//��ҹ�������
	string enemyAttack(Enemy& target, Player& pl);//���˹������
	void displayStatus();//��ʾ���״̬
	void startGame();//��ʼ��Ϸ
	int updateGameState();//����״̬
	int executePlayerAction();//ִ����Ҷ���
	void showEnemy();//��ʾ��ǰ����
	void showWeapon();//��ʾ����
	void useProp();//ʹ�õ���
	void showEnd();//����ʱ����ʾ
};

