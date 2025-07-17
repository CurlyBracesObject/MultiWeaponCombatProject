#include "DerivativeSystem.h"
double DerivativeSystem::performDerivativeAction(std::string name1, std::string name2)
{
	std::pair<std::string, std::string> pr(name1, name2);
	auto it = derivativeActionMapping.find(pr);
	while (it != derivativeActionMapping.end())
	{
		std::pair<std::string, std::string> tp = it->first;
		if (name1.compare(tp.first) == 0 && name2.compare(tp.second) == 0)
		{
			std::cout << "Derivative action increases weapon " << name2 << " damage by " << it->second * 100 << "%" << std::endl;
			return it->second;
		}
	}
	return 0;
}
void DerivativeSystem::add(std::string name1, std::string name2, double v)
{
	std::pair<std::string, std::string> pr(name1, name2);
	derivativeActionMapping[pr] = v;
}