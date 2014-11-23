#include "MyTrends.hpp"

#include <algorithm>

void MyTrends::increaseCount(std::string s, unsigned int amount)
{

}

unsigned int MyTrends::getCount(std::string s)
{

}

std::string MyTrends::getNthPopular(unsigned int n)
{

}

unsigned int MyTrends::numEntries()
{
	words.size();
}

bool MyTrends::compare(std::pair<std::string, int> &p1,
		       std::pair<std::string, int> &p2)
{
	if (p1.second == p2.second) {
		return p1.first < p2.first;
	}

	return p1.second > p2.second;
}
