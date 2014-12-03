#include <vector>
#include <string>
#include "../Trends.h"
#include "LinkedList.h"
#include "hashTable.h"

class siegerTrends : public Trends{
public:
	virtual void increaseCount(std::string s, unsigned int amount);
	virtual unsigned int getCount(std::string s);
	virtual std::string getNthPopular(unsigned int n);
	virtual unsigned int numEntries();
	bool isSorted;
	siegerTrends() { isSorted = false; }

//protected:
	
	std::vector<std::pair<std::string, int> > wordCountVector;
	HashTable<std::string, int> wordTable;
	LinkedList<int> frequencyList;

};
