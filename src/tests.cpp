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

#include "utilities.h"

#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define TEST_ME

#ifdef TEST_ME
#include "LapeedTrends.hpp"
#define TRENDS_CLASS MyTrends
#define TESTING "My Trends"
static std::string OUT_FILE(".me");

#elif defined(TEST_ONE)
#include "sieger/ourTrends.h"
#define TRENDS_CLASS siegerTrends
#define TESTING "sieger"
static std::string OUT_FILE(".sieger");

#elif defined(TEST_TWO)
#include "scott/apsmTrends.h"
#define TRENDS_CLASS apsmTrends
#define TESTING "scott"
static std::string OUT_FILE(".scott");

#elif defined(TEST_THREE)
#include "mongoose/mongooseTrends.h"
#define TRENDS_CLASS mongooseTrends
#define TESTING "mongoose"
static std::string OUT_FILE(".mongoose");

#else
#include "smarterTrends.h"
#define TRENDS_CLASS smarterTrends
#define TESTING "smarter Trends"
static std::string OUT_FILE(".smart");

#endif

void test_adding(void)
{
	std::cout << "test: add all words" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");

	TRENDS_CLASS tr;
	
	double start = getTimeInMillis();

	for(unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
	}

	double end = getTimeInMillis();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_add_all_increment_all(void)
{
	std::cout << "test: add all words then increment every word by 1" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");

	TRENDS_CLASS tr;
	
	for (unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
	}

	double start = getTimeInMillis();

	for (unsigned int i = 0; i < words.size(); i++) {
		tr.increaseCount(words[i], 1);
	}

	double end = getTimeInMillis();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_add_all_increment_get_pop(void)
{
	std::cout << "test: add all words then increment every word by 1 then get the most "
		  << "popular word" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");
	std::ofstream out("data/28885.txt.out" + OUT_FILE);

	TRENDS_CLASS tr;
	
	for (unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
	}

	double start = getTimeInMillis();

	for (unsigned int i = 0; i < words.size(); i++) {
		tr.increaseCount(words[i], 1);
		std::string pop = tr.getNthPopular(0);
		out << pop << "\n";
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_print_words_in_order(void)
{
	std::cout << "test: add all words then print them in order (from most popular to least)" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");
	std::ofstream out("data/28885.txt.out" + OUT_FILE);

	TRENDS_CLASS tr;
	
	for(unsigned int i = 0; i < words.size(); i++) {
		tr.increaseCount(words[i], 1);
	}
	
	double start = getTimeInMillis();

	for(unsigned int i = 0; i < tr.numEntries(); i++) {
		out << tr.getNthPopular(i) << "\n";
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_print_words_in_order_with_count(void)
{
	std::cout << "test: add all words then print them in order with word count" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");
	std::ofstream out("data/28885.txt.out" + OUT_FILE);

	TRENDS_CLASS tr;
	
	for(unsigned int i = 0; i < words.size(); i++) {
		tr.increaseCount(words[i], 1);
	}
	
	double start = getTimeInMillis();

	for(unsigned int i = 0; i < tr.numEntries(); i++) {
		std::string word = tr.getNthPopular(i);
		out << tr.getCount(word) << " " << word << "\n";
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}


void test_add_get_most_pop(void)
{
	std::cout << "test: add a word then get most popular word" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");
	std::ofstream out("data/28885.txt.out" + OUT_FILE);

	TRENDS_CLASS tr;

	double start = getTimeInMillis();

	for(unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
		std::string temp = tr.getNthPopular(0);
		out << temp << " " << tr.getCount(temp) << "\n";
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_add_get_count_of_word(void)
{
	std::cout << "test: add a word then get the count of that word" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");
	std::ofstream out("data/28885.txt.out" + OUT_FILE);
	
	TRENDS_CLASS tr;

	double start = getTimeInMillis();

	for(unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
		unsigned int value = tr.getCount(words[i]);
		out << words[i] << " " << value << "\n";
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_add_all_get_count()
{
	std::cout << "test: add all words then get count of random words" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");
	std::ofstream out("data/28885.txt.out" + OUT_FILE);

	std::random_device rd;
	std::default_random_engine rand(rd());

	TRENDS_CLASS tr;

	for (unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
	}

	double start = getTimeInMillis();

	for (unsigned int i = 0; i < words.size(); i++) {
		std::string w = words[rand() % words.size()];
		unsigned int temp = tr.getCount(w);
		out << w << " " << temp << "\n";
	}	

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

void test_hardest(void)
{
	std::cout << "test: add all words, get a random nth popular word, increase that "
		  << "words count by 1 then get the most common word along with its count" << std::endl;
	
	std::vector<std::string> words = getWordList("data/28885.txt");

	std::random_device rd;
	std::default_random_engine rand(rd());

	TRENDS_CLASS tr;

	for (unsigned int i = 0; i < words.size(); i++){
		tr.increaseCount(words[i], 1);
	}

	double start = getTimeInMillis();

	for (unsigned int i = 0; i < words.size(); i++) {
		unsigned int temp = rand() % tr.numEntries();
		std::string word = tr.getNthPopular(temp);
		tr.increaseCount(word, 1);

		word = tr.getNthPopular(0);
		temp = tr.getCount(word);
	}

	double end = getTimeInMillis();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

int main(void)
{
	std::cout << "testing: " << TESTING << std::endl << std::endl;

	double start = getTimeInMillis();
	
	test_adding();
	test_add_all_increment_all();
	test_add_all_increment_get_pop();
	test_print_words_in_order();
	test_print_words_in_order_with_count();
	test_add_get_most_pop();
	test_add_get_count_of_word();
	test_add_all_get_count();
	test_hardest();

	double end = getTimeInMillis();

	std::cout << "total test time: " << (end - start) << " ms" << std::endl;
	
	return 0;
}
