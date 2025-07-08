#pragma once

#include <iostream>
#include <string>

#ifndef WEAPON
#define WEAPON

//������
class Weapon {
private:
	std::string name;//������
	int damage;//�˺�
	int cooldown;//��ȴʱ��
	int useTime = -50;//ʹ�õ�ʱ��
	std::string Feature;//��Բ�ͬ�������͵�����
	int compatibilityBonus=0;//�����Լӳ�
public:
	//��ʼ��
	Weapon(std::string name, int damage, int cooldown) : name(name), damage(damage), cooldown(cooldown) {}
	void setFeature(std::string Feature);
	std::string getFeature();
	void setCompatibilityBonus(int compatibilityBonus);
	int getCompatibilityBonus();
	int attack();//����
	void setUseTime(int time);//����ʹ�õ�ʱ��
	int coolOk(int time);//�Ƿ���ȴ���
	std::string getName();//��ȡ������
	int getDamage();//��ȡ�˺�
};
#endif

