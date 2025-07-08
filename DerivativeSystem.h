#pragma once

#include <iostream>
#include <string>
#include <map>

//派生系统类
class DerivativeSystem {
private:
	std::map<std::pair<std::string, std::string>, double> derivativeActionMapping;//派生动作映射
public:
	double performDerivativeAction(std::string name1, std::string name2);//执行派生动作
	void add(std::string name1, std::string name2, double v);//添加派生动作
};