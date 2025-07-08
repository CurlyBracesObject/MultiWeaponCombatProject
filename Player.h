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
	int health;                          // Ѫ��
	int stackeddamage = 0;               // ʹ��ҩˮ���ӵ��˺�
	int shield = 0;                      // ʹ�����������ӵĻ���
	int grade = 1;                       // �ȼ�
	int maxhealth = 100;                          // ���Ѫ��
	Weapon* currWeapon;                  // ��ǰ����
	std::vector<Weapon> weaponInventory; // ������
	std::map<std::string, int> bag;      // ����
	int EXP = 0;

public:
	// ��ʼ��
	Player(int initialHealth) : health(initialHealth), currWeapon(nullptr) {}
	// ��ȡѪ��
	int getHealth();
	//����
	void revive();
	//���Ӿ���
	void addEXP(int aEXP);
	//��ȡʹ��ҩˮ���ӵ��˺�
	int getStackeddamage();
	// ��������
	void showBag();
	// ѡ�����
	std::string selectProp();
	// ������Ѫ��+10
	void upGrade();
	// ������ߵ�����
	void joinBag(std::string name);
	// ʹ�õ���
	void useProp(std::string& name);
	// ��ȡ�ȼ�
	int getGrade();
	// ��������
	void changeWeapon(const std::string& weaponName);

	// ����
	int attack();
	// ����
	int takeDamage(int amount);
	// ��ȡ��ǰ����
	Weapon* getCurrentWeapon() const;

	// ���������������
	void addWeaponToInventory(Weapon& weapon);
};
#endif

