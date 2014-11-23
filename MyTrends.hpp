#include "Trends.h"

#include <vector>
#include <map>

class MyTrends : public Trends {
public:
	virtual void increaseCount(std::string s, unsigned int amount);
	virtual unsigned int getCount(std::string s);
	virtual std::string getNthPopular(unsigned int n);
	virtual unsigned int numEntries();

protected:
	std::vector< std::pair<std::string, int> > words;

	std::unordered_map<std::string, int> word_count;

	virtual bool compare(std::pair< std::string, int> p1,
			     std::pair< std::string, int> p2);
};
