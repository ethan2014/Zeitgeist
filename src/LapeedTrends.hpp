/*
 * LapeedTrends
 *
 * This program stores a list of words with the amount of times that word
 * has been added, it is used to keep track of 'trending' words in the input
 *
 * Copyright (C) 2014 Ethan Lape
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Trends.h"

#include <vector>
#include <unordered_map>
#include <iterator>

class LapeedTrends : public Trends
{
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

	std::vector< std::pair<std::string, unsigned int> > words;

	std::unordered_map<std::string, unsigned int> word_count;

	virtual void add_word(const std::string &s, unsigned int amount);

	virtual void increment_word(const std::string &s, unsigned int amount,
				    const std::unordered_map<std::string, unsigned int>::iterator &it);

	virtual void find_first_largest(unsigned int pos);
};
