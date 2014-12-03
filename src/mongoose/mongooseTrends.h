#include "../Trends.h"
#include <vector>
#include <unordered_map>

class mongooseTrends : public Trends {
public: 
	unsigned int numEntries();
	unsigned int getCount(std::string s);
	virtual void increaseCount(std::string s, unsigned int amount);
	virtual std::string getNthPopular(unsigned int n);
    virtual void add(std::string s, unsigned int n);
	virtual void increment_word(std::string s, unsigned int n, std::unordered_map<std::string, unsigned int>::iterator &iterator);
	bool isSorted;
    
    
    
    
    protected:
    std::vector<std::pair<std::string, unsigned int> > sortedArray;
    std::unordered_map<std::string, unsigned int> hashTable;

};
