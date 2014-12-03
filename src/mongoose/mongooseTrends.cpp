#include "mongooseTrends.h"

#include <algorithm>

static bool compareFunc(std::pair<std::string, unsigned int> i, std::pair<std::string, unsigned int> j);

bool isSorted = false;

unsigned int mongooseTrends::getCount(std::string s)	{
    
    //should loop through the array and return the count of the wanted string else return 0.
    //assuming you want to know the count of something at the top of the array
    //this function will be fast.
    for (unsigned int i = 0; i < sortedArray.size(); i++)	{
        if (sortedArray.at(i).first == s)	{
            return sortedArray.at(i).second;
        }
    }
	return 0;
}

unsigned int mongooseTrends::numEntries()	{
    
	return sortedArray.size();
}

std::string mongooseTrends::getNthPopular(unsigned int n)	{
    
    if(!isSorted)	{
		std::sort(sortedArray.begin(), sortedArray.end(), compareFunc);
		isSorted = true;
	}

    std::string ret = sortedArray[n].first;

    return ret;
    
}

static bool compareFunc(std::pair<std::string, unsigned int> i, std::pair<std::string, unsigned int> j) {
    
    if (i.second == j.second){
        return (i.first < j.first);
    }
    
    return (i.second > j.second);
}

void mongooseTrends::increaseCount(std::string s, unsigned int amount)	{
    
	//case 1: String s is not in the hashTable/Array. Create s and set count to amount (regular case)
	
	auto place = hashTable.find(s);	//http://en.cppreference.com/w/cpp/container/unordered_map/find

	isSorted = false;

	if (hashTable.count(s) == 0)	{
		add(s, amount);
	}
	else
	{
		increment_word(s, amount, place);
	}
    
	//case 2: String s is already in the hashTable and array. Add amount to its count(increment word function)
}

void mongooseTrends::add(std::string s, unsigned int n){
    
    std::pair<std::string, unsigned int> addition (s, n);
    
    hashTable.insert(addition);
    sortedArray.push_back(addition);
    
}

void mongooseTrends::increment_word(std::string s, unsigned int n, std::unordered_map<std::string, unsigned int>::iterator &place)	{
    
	place->second += n;
	bool cont = true;
	
	//relies on the assumption that more often than not, you're going to be incrementing words at the beginning of the sorted array
	for (unsigned int i = 0; i < sortedArray.size() && cont; i++)	{
		if (sortedArray.at(i).first == s)	{
			sortedArray.at(i).second += n;
			cont = false;
		}
	}
}



