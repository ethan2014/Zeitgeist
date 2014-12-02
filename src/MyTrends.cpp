#include "MyTrends.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

static bool compare(std::pair<std::string, unsigned int> &p1,
		    std::pair<std::string, unsigned int> &p2);

MyTrends::MyTrends()
{
	should_sort = false;
	sort_start = words.size();
	sort_end = 0;
}

void MyTrends::increaseCount(std::string s, unsigned int amount)
{
	auto iterator = word_count.find(s);

	if (iterator == word_count.end()) {
		add_word(s, amount);
	} else {
		increment_word(s, amount, iterator);
	}
}

void MyTrends::add_word(std::string s, unsigned int amount)
{
	// add word to our count list
	word_count[s] = amount;
	
	std::pair<std::string, unsigned int> pair = std::make_pair(s, amount);

	// add this word and its count to the list of words
	words.push_back(pair);

	// get the position of this new item
//	unsigned int pos = words.size() - 1;

	find_first_largest(words.size() - 1);
}

void MyTrends::increment_word(std::string s, unsigned int amount,
			      std::unordered_map<std::string, unsigned int>::iterator &it)
{
	// increment word count in our word count table
	it->second += amount;

	std::pair<std::string, unsigned int> pair = std::make_pair(s, amount);

	// find this item in the words list
	auto item_it = std::find_if(words.begin(), words.end(),
				    [&] (const std::pair<std::string, unsigned int> &p) {
					    return p.first == s;
				    });

	// increment its word count in the list
	item_it->second += amount;

//	unsigned int pos = std::distance(words.begin(), item_it);

	find_first_largest(std::distance(words.begin(), item_it));
}

void MyTrends::find_first_largest(unsigned int pos)
{
	// make sure this item isnt already the highest item
	if (pos == 0) {
		return;
	}

	// make sure its actually worth looking for sort start and end positions
	if (sort_start == 0 && sort_end == words.size() - 1) {
		return;
	}

	unsigned int temp = pos - 1;	

	// if the item at sort_start is already larger that at pos, we dont need
	// to look any further, the item at pos will be sorted
	if (sort_start < pos && compare(words[sort_start], words[pos])) {
		goto done;
	}

	// if the current start position of sorting is less than the position of
	// our item, we can start searching at sort_start
	if (sort_start < pos) {
		temp = sort_start;
	}

	should_sort = true;

	// keep looking to the left of pos until an item that is bigger is found
	while (temp != 0 && compare(words[pos], words[temp])) {
		temp--;
	}

	// temp is now a possible candidate for sort_start
	if (temp < sort_start) {
		sort_start = temp;
	}

done:
	// pos is now a possible candidate for sort_end
	if (pos > sort_end) {
		sort_end = pos;
	}
}

unsigned int MyTrends::getCount(std::string s)
{
	return word_count[s];
}

std::string MyTrends::getNthPopular(unsigned int n)
{
	if (should_sort) {
//		std::cout << words.size() << " " << (sort_end - sort_start) << std::endl;
		std::sort(words.begin() + sort_start, words.begin() + sort_end + 1, compare);
//		std::sort(words.begin(), words.end(), compare);
		should_sort = false;
		sort_start = words.size();
		sort_end = 0;
	}
	
	return words[n].first;
}

unsigned int MyTrends::numEntries()
{
	return words.size();
}

static bool compare(std::pair<std::string, unsigned int> &p1,
		    std::pair<std::string, unsigned int> &p2)
{
	if (p1.second == p2.second) {
		return p1.first < p2.first;
	}

	return p1.second > p2.second;
}
