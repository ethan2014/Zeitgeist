#include "Trends.h"

#include <vector>
#include <unordered_map>
#include <iterator>

class MyTrends : public Trends {
public:
	MyTrends();
	virtual void increaseCount(std::string s, unsigned int amount);
	virtual unsigned int getCount(std::string s);
	virtual std::string getNthPopular(unsigned int n);
	virtual unsigned int numEntries();

protected:
	bool should_sort;
	unsigned int sort_start;
	unsigned int sort_end;

//	std::vector< std::pair<std::string, unsigned int> >::iterator sort_start;
	
	std::vector< std::pair<std::string, unsigned int> > words;

	std::unordered_map<std::string, unsigned int> word_count;

//	virtual bool compare(std::pair< std::string, unsigned int> &p1,
//			     std::pair< std::string, unsigned int> &p2);

	virtual void add_word(std::string s, unsigned int amount);

	virtual void increment_word(std::string s, unsigned int amount,
				    std::unordered_map<std::string, unsigned int>::iterator &it);
};
