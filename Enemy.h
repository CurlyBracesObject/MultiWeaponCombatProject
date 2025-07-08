#pragma once

#include <iostream>  
#include <string>  

#ifndef ENEMY
#define ENEMY

//������
class Enemy {
private:
	std::string type;        // �������� 
	int health;              // ����Ѫ��  
	int attackPower;         // ���˹�����  
	int EXP;                //��ܵ��˻�õľ���
public:
	// ��ʼ�� 
	Enemy(std::string type, int health, int attackPower, int EXP)
		: type(type), health(health), attackPower(attackPower), EXP(EXP) {}

	int getEXP() const {
		return EXP;
	}

	// ��ȡ����
	std::string getType() const {
		return type;
	}

	// ��ȡѪ��   
	int getHealth() const {
		return health;
	}

	// ��ȡ������  
	int getAttackPower() const {
		return attackPower;
	}

	// ����
	int attack();

	// ����
	int takeDamage(int damage);
};
#endif

