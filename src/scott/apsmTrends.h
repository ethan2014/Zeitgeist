#include "../Trends.h"
#include <unordered_map>
#include <array>

class apsmTrends : public Trends {
public:
	virtual void increaseCount(std::string s, unsigned int amount);
	virtual unsigned int getCount(std::string s);
	virtual std::string getNthPopular(unsigned int n);
	virtual unsigned int numEntries();
    apsmTrends();

protected:
	std::array<std::pair<std::string, unsigned int>, 10> topTen;
	std::unordered_map<std::string, unsigned int> wordTable;

    
private:
    virtual void swap(std::pair<std::string, unsigned int>, int);
    unsigned int numWords;
};

