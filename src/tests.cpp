#include "utilities.h"

#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MY_TEST

#ifdef MY_TEST
#include "MyTrends.hpp"
#define TRENDS_CLASS MyTrends
#define TESTING "My Trends"
static std::string OUT_FILE(".me");

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
		out << tr.getNthPopular(i) << std::endl;
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
		out << tr.getCount(word) << " " << word << std::endl;
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
		out << temp << " " << tr.getCount(temp) << std::endl;

		//	if (words[i] == "Adventures") {
		//		std::cout << "Adventures added at pos: " << i << std::endl;
		//		break;
		//	}
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
		out << words[i] << " " << value << std::endl;
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
		out << w << " " << temp << std::endl;
	}	

	double end = getTimeInMillis();

	out.close();

	std::cout << "time per item: " << (end - start) / words.size() << " ms " << std::endl
		  << "total time: " << (end - start) << " ms" << std::endl << std::endl;
}

int main(void)
{
	std::cout << "testing: " << TESTING << std::endl << std::endl;

	double start = getTimeInMillis();
	
//	test_adding();
//	test_print_words_in_order();
//	test_print_words_in_order_with_count();
	test_add_get_most_pop();
//	test_add_get_count_of_word();
//	test_add_all_get_count();

	double end = getTimeInMillis();

	std::cout << "total test time: " << (end - start) << " ms" << std::endl;
	
	return 0;
}
