/*****
 * Author   : brinkmwj
 * Date     : 2009-10-04
 * Sources  : All code is original
 * Purpose  : The purpose of this file is to do some VERY rudimentary timing of your increaseCount
 *            method. For the QUALITY measures I am also going to test getCount, so you might want
 *            to design some way to test out the running time of your getCount as well!
 */
#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "MyTrends.hpp"
//#include "smarterTrends.h" //You will need to change this to match your own class
#include "utilities.h"

#define TRENDS MyTrends()

/**
 * This tests a simple (but unlikely) use case, which is to read in all the data, and then print out the data in sorted order
 * based on popularity.
 *
 * Compare your 28885.txt.out to 28885_txt.out, using diff,s to see if your code is producing correct output.
 */
double useCase_addAllThenGetInOrder(){
	Trends* tr = new TRENDS; //You will need to change this to match your own class!

	std::vector<std::string> wordlist = getWordList("data/28885.txt");

	//We only want to time how long addToTrends takes, so we get
	// the starting time, which is the clock time, in milliseconds
	double start = getTimeInMillis();
	//Now add all the words to the Trends data structure
	for(unsigned int i=0; i<wordlist.size(); i++){
		tr->increaseCount(wordlist[i],1);
	}
	//Now get the end time
	double end = getTimeInMillis();
	std::cout << "increaseCount time: " << (end-start)/wordlist.size() << " ms per word" << std::endl;

	//Now we will print out the complete results. This could be REALLY clow, if
	// your getNthPopular is not a little bit smart.
	std::string outfname = "data/28885.txt.out.smarter";
	std::ofstream out(outfname.c_str());

	start = getTimeInMillis();
	for(unsigned int i=0; i< tr->numEntries(); i++){
		std::string s = tr->getNthPopular(i);
		out << tr->getCount(s) << ": " << s << std::endl;
	}
	out.close();
	end = getTimeInMillis();
	std::cout << "getNth followed by getCount, time: " << (end - start) / tr->numEntries() << " ms per entry" << std::endl;

	delete tr;

	return end - start;
}

void usecase_add_and_get_random_word(void)
{
	std::cout << "--- begin test: add item and get random word count ---" << std::endl;
	
	std::random_device rd;
	std::default_random_engine rand(rd());

	Trends *tr = new TRENDS;

	std::vector<std::string> words = getWordList("data/28885.txt");

	std::ofstream out("data/28885.txt.out");

	std::cout << "words to be added: " << words.size() << std::endl;

	double start = getTimeInMillis();
	for (int i = 0; i < words.size(); i++) {
		tr->increaseCount(words[i], 1);
		int num = rand() % tr->numEntries();
		out << tr->getNthPopular(num) << std::endl;
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "add word then get random nth popular: " << (end - start) / words.size() << " ms per word"
		  << " total time: " << (end - start) << " ms" << std::endl;
	std::cout << "--- end test ---" << std::endl;

	delete tr;
}

void usecase_add_and_get_most_popular(void)
{
	std::cout << "--- begin test: add item and get most popular ---" << std::endl;

	std::random_device rd;
	std::default_random_engine rand(rd());
	
	Trends *tr = new TRENDS;

	std::vector<std::string> words = getWordList("data/28885.txt");

	std::ofstream out("data/28885.txt.out");

	std::cout << "words to be added: " << words.size() << std::endl;

	double start = getTimeInMillis();
	for (int i = 0; i < words.size(); i++) {
		tr->increaseCount(words[i], 1);
		out << tr->getNthPopular(0) << std::endl;
	}

	double end = getTimeInMillis();

	out.close();

	std::cout << "add word then get random most popular: " << (end - start) / words.size() << " ms per word"
		  << " total time: " << (end - start) << " ms" << std::endl;
	std::cout << "--- end test ---" << std::endl;

	delete tr;
}

void usecase_add_all_add_to_random(void)
{
	std::cout << "--- begin test: add all items then increment random words by random amounts ---" << std::endl;
	
	Trends *tr = new TRENDS;

	std::vector<std::string> words = getWordList("data/28885.txt");

	std::ofstream out("data/28885.txt.out");

	std::cout << "words to be added: " << words.size() << std::endl;

	double start = getTimeInMillis();
	for (int i = 0; i < words.size(); i++) {
		tr->increaseCount(words[i], 1);
	}

	double end = getTimeInMillis();

	std::cout << "add all words: " << (end - start) / words.size() << " ms per word"
		  << " total time: " << (end - start) << " ms" << std::endl;

	start = getTimeInMillis();
	for (int i = 0; i < words.size(); i++) {
		int word_num = rand() % tr->numEntries();
		std::string word = tr->getNthPopular(word_num);
		tr->increaseCount(word, 1);
		out << tr->getNthPopular(0) << std::endl;
	}
	end = getTimeInMillis();

	std::cout << "add 1 to random word and get most popular: " << (end - start) / words.size()
		  << " ms per word, total time: " << (end - start) << " ms" << std::endl;
	std::cout << "--- end test ---" << std::endl;

	delete tr;
}

/*
 * The only purpose of main() is to call processFile with increasingingly larger and larger
 * files. A larger file will give a more accurate sense of how fast addToTrends is, but at some
 * point it may take so long to do the getNthPopular, that we aren't willing to wait for it to finish.
 */
int main(){
	/* The data files are books from project Gutenberg. I have provided the inputs, as well as my outputs
	 * in the starter files */

	useCase_addAllThenGetInOrder();

	usecase_add_and_get_random_word();
	usecase_add_and_get_most_popular();
	usecase_add_all_add_to_random();

	return 0;
}
