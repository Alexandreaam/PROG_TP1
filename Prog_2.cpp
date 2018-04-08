#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <ctime>

using namespace std;

char abc[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

bool match(string word, map<char, vector < string >> &map)
{
	vector < string > list = map[word.at(0)];
	int i = 0, size = list.size() - 1;
	while (i < size)
	{
		string wordS = list[i];
		//cout << "Looking at: " << wordS << endl;
		if (word == wordS)
		{
			return true;
		}
		else i++;
	}
	return false;
}
vector < string > wordsSized(map<char, vector < string >> &map, int wordSize) {
	vector < string > final;
	for (int k = 0; k < map.size(); k++) {
		vector < string > list = map[abc[k]];

		int i = 0, size = list.size() - 1;

		while (i < size)
		{
			if (list[i].size() == wordSize) {
				final.push_back(list[i]);
			}
			i++;
		}

	}
	return final;
}

vector < string > checkLetters(vector < string > list, string word) {
	for (int i = 0; i < list.size(); i++) {
		string cWord = list[i];
		string tempWord = word;
		while (tempWord.size() > 0) {

		}

	}
}

string scramble(string word) {
	string final;
	srand(time(NULL));
	while (word.size() != 0) {
		int num = rand() % (word.size());
		final.push_back(word[num]);
		word.erase(word.begin() + num);
	}
	return final;
}

//ANEXO C
bool wildcardMatch(const char *str, const char *strWild)
{
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild)
	{
		// Single wildcard character
		if (*strWild == '?')
		{
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			// Need to do some tricks.
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.
			// Because we eat one character from the match string,
			// the recursion will stop.
			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;
			// 2. Chance we eat the next character and try it again,
			// with a wildcard * match. This is done by recursion.
			// Because we eat one character from the string,
			// the recursion will stop.
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		}
		else
		{
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}


int main()
{

	string file, word;
	vector < string > word_list;
	map<char, vector < string >> m;
	int op = 0;

	cout << "=====================PLAYWORDS=====================" << endl;
	cout << "Word list file ? ";
	cin >> file; cout << endl;

	cout << "Extracting ... " << endl << endl;
	ifstream f(file);

	while (getline(f, word)) {
		m[word.at(0)].push_back(word);
	}

	f.close();

	cout << "Choose one of the following actions: " << endl;
	cout << "	(1) If the word belongs to the word list" << endl; 
	cout << "	(2) Guess the word" << endl;
	cout << "	(3) All the words that can be built using the set of the given letters" << endl;
	cout << "	(4) Build a valid word" << endl;
	cout << "	(5) All the words that match the given string" << endl << endl;
	cout << "	Action: ";
	cin >> op;
	cout << endl;

	if (op == 1)
	{
		string word;

		cout << "Word: ";
		cin >> word;
		if (match(word, m) == true)
			cout << "Existe" << endl;
		else
			cout << " Nao existe" << endl;
	}
	else if (op == 2)
	{
		srand(time(NULL));
		int num = rand() % (m.size());
		int attempt = 3;
		vector < string > list = m[abc[num]];
		num = rand() % (list.size());
		string word = list[num];
		string scrambled = scramble(word);
		string guess;
		while (attempt != 0) {
			cout << "What is the original word?" << endl;
			//cout << "Pre-Scramble: " << word << endl;
			cout << "Scrambled: " << scrambled << endl;
			cin >> guess;
			if (guess == word) {
				cout << "Correct!" << endl;
				attempt = 0;
			}
			else {
				attempt--;
				if (attempt == 0) {
					cout << "You Lost!" << endl;
				}
				else {
					cout << "WRONG! You have " << attempt << " left." << endl;
				}
			}
		}
	}
	else if (op == 3)
	{
		string letters;
		cout << "Letters to use: ";
		cin >> letters;
		vector < string > words;
		words = wordsSized(m, letters.size());
		cout << "Number of words with the same size: " << words.size() << endl;
	}
	else if (op == 4)
	{


	}
	else if (op == 5)
	{

	}
	else
		cout << endl << "ERRO" << endl;
}