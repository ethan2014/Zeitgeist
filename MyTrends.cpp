#include "MyTrends.hpp"

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
//	sort_start = words.end();
}

void MyTrends::increaseCount(std::string s, unsigned int amount)
{
	auto iterator = word_count.find(s);

	if (iterator == word_count.end()) {
		add_word(s, amount, iterator);
	} else {
		increment_word(s, amount, iterator);
	}
}

void MyTrends::add_word(std::string s, unsigned int amount,
			std::unordered_map<std::string, unsigned int>::iterator &it)
{
	// add word to our count list
	word_count[s] = amount;
//	it->second = amount;
	
	std::pair<std::string, unsigned int> pair = std::make_pair(s, amount);

	// add this word and its count to the list of words
	words.push_back(pair);

	// get the position of this new item
	unsigned int pos = words.size() - 1;
	unsigned int temp = pos - 1;

	// make sure this item isnt already the highest item
	if (pos == 0) {
		return;
	}

	// if the item to the left of ours is smaller than ours we need
	// to sort.  the current start position for sorting must also be
	// larger than the position of this item
	if (compare(words[pos], words[temp])) {
		should_sort = true;

		while (temp != 0 && compare(words[pos], words[temp])) {
			temp--;
		}
	}

	// temp is now the distance between our item in the list and the first
	// item to its left that is larger than it, we need to convert this number
	// to a distance from the start of the list
	if (temp < sort_start) {
		sort_start = temp;
	}

	if (pos > sort_end) {
		sort_end = pos;
	}

	/*
	if (compare(words[pos], words[pos - 1])) {
		// we only need to sort the list if the item we just added is
		// larger than the one to its left

		unsigned int temp = pos - 1;
		std::vector< std::pair<std::string, unsigned int> >::iterator larger_it;

		while (compare(words[pos], words[temp]) && temp != 0) {
			temp--;
		}

		larger_it = (words.end() - 1) - temp;
		
		std::sort(larger_it, words.end(), compare);
//		std::sort(words.begin(), words.end(), compare);
	}
	*/
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

	unsigned int pos = std::distance(words.begin(), item_it);
	unsigned int temp = pos - 1;

	if (pos == 0) {
		return;
	}

	// if the item to the left of ours is smaller than ours we need
	// to sort.  the current start position for sorting must also be
	// larger than the position of this item
	if (compare(words[pos], words[temp])) {
		should_sort = true;

		while (temp != 0 && compare(words[pos], words[temp])) {
			temp--;
		}
	}

	// temp is now the distance between our item in the list and the first
	// item to its left that is larger than it, we need to convert this number
	// to a distance from the start of the list
	if (temp < sort_start) {
		sort_start = temp;
	}

	if (pos > sort_end) {
		sort_end = pos;
	}

	/*
	if (item_it == words.begin()) {
		return;
	}

	if (compare(*item_it, *(item_it - 1))) {
		std::vector< std::pair<std::string, unsigned int> >::iterator larger_it = item_it - 1;

		while (compare(*item_it, *larger_it) && larger_it != words.begin()) {
			--larger_it;
		}
		
		std::sort(larger_it, item_it, compare);
//		std::sort(words.begin(), words.end(), compare);
	}
	*/
}

unsigned int MyTrends::getCount(std::string s)
{
	return word_count[s];
}

std::string MyTrends::getNthPopular(unsigned int n)
{
	if (should_sort) {
		std::sort(words.begin() + sort_start, words.begin() + sort_end, compare);
		should_sort = false;
		sort_start = words.size();
		sort_end = 0;
	}
	
	return words[n].first;
}

unsigned int MyTrends::numEntries()
{
	words.size();
}

static bool compare(std::pair<std::string, unsigned int> &p1,
		    std::pair<std::string, unsigned int> &p2)
{
	if (p1.second == p2.second) {
		return p1.first < p2.first;
	}

	return p1.second > p2.second;
}
