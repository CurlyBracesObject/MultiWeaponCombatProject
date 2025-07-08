#pragma once

#include <iostream>
#include <string>
#include <map>

//����ϵͳ��
class DerivativeSystem {
private:
	std::map<std::pair<std::string, std::string>, double> derivativeActionMapping;//��������ӳ��
public:
	double performDerivativeAction(std::string name1, std::string name2);//ִ����������
	void add(std::string name1, std::string name2, double v);//�����������
};