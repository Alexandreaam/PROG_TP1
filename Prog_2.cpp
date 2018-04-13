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

vector < string > scramble_find(vector < string > &list, string letters)
{
	vector < int > cont_letter;
	string letters1 = letters, l_final;
	vector < string > words;
	vector < int > cont_final;
	int cont = 0;
	size_t i=0;

	while( letters1.size() != 0)
	{
		char letter = letters1[i];
		while (i != string::npos)
		{
			cont++;
			letters1.erase(letters1.begin() + i);
			i = letters1.find_first_of(letter);

		}
		l_final = l_final + letter;
		cont_letter.push_back(cont);
		cont = 0;
		i = 0;
	} 

	for (i = 0; i < list.size(); i++)
	{
		size_t pos = list[i].find_first_not_of(letters);
		if (pos == string::npos)
			words.push_back(list[i]);
	}	
	
	int j = 0, k=0;
	while (k < words.size())
	{
		string w = words[k];
		j = 0;
		while (w.size() != 0)
		{
			char letter = l_final[j];
			i = w.find_first_of(letter);

			while (i != string::npos)
			{
				cont++;
				w.erase(w.begin() + i);
				i = w.find_first_of(letter);

			}
			cont_final.push_back(cont);
			cont = 0;
			j++;
		
		}
		if (cont_final != cont_letter)
			words.erase(words.begin() + k);
		else
			k++;

		cont_final.clear();
	}

	return words;
}

/*ANEXO C*/bool wildcardMatch(const char *str, const char *strWild)
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

int frequency(map<char, vector < string >> &m, char letter)
{
	int k, i, cont = 0;
	vector < string > list;
	string word;
	size_t pos;

	for (k = 0; k < 26; k++)
	{
		list = m[abc[k]];
		for (i = 0; i < list.size(); i++)
		{
			word = list[i];
			pos = word.find_first_of(letter);
			while (pos != string::npos)
			{
				cont++;
				pos = word.find_first_of(letter, pos +1);
			}
		}
	}
	// menor frequencia: J - 1251, TEM 2 J' in Larger set//
	return (int)((2 * cont) / 1251);
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
			cout << "The word " << word << " exist." <<endl;
		else
			cout << "The word " << word << " don't exist." << endl;
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
		//cout << "Number of words with the same size: " << words.size() << endl;
		words = scramble_find(words, letters);
		cout << "Number of words that can be built: " << words.size() << endl;
		cout << "Words: ";

		for (int i = 0; i < words.size(); i++)
			cout << words[i] << " ";
		cout << endl;
	

	}
	else if (op == 4)
	{
		string larger_set;
		string s;
		string word, set;
		int freq = 0;
		int k, i, N, num;

		cout << "Creating larger set ..." << endl;
		for ( k = 0; k < 26; k++)
		{
			s = abc[k];
			freq = frequency(m, abc[k]);
			for (i = 0; i < freq; i++)
			{
				larger_set = larger_set +s;
			}
		}

		cout << endl << "Size of the set, N: ";
		cin >> N;

		srand(time(NULL));
		while (N != 0) 
		{
			num = rand() % (larger_set.size());
			//cout << num<< endl;
			N--;
			set = set + larger_set[num];
		}
		
		cout << endl << "  Set: " << set << endl;
		cout << "  Try to build a word: ";
		cin >> word;

		if (match(word, m) == true)
			cout << endl << "Correct! The word " << word << " exist." << endl;
		else
			cout << "Sorry... the word " << word << " don't exist." << endl;

		
	}
	else if (op == 5)
	{
		string s1, s2;
		vector < string > list;
		vector < string > words;
		size_t i, k;

		cout << "String: ";
		cin >> s1;
		
		for (i = 0; i < 26; i++)
		{
			if(abc[i] == s1[0])
				list = m[abc[i]];
		}

		if (list.size() != 0)// string s1 começa por letra//
		{
			for (i = 0; i < list.size(); i++)
			{
				s2 = list[i];
				if (wildcardMatch(s2.c_str(), s1.c_str()) == true)
					words.push_back(s2);
			}
		}
		else// string s1 começa por * ou ?//
		{
			for (k = 0; k < 26; k++)
			{
				list = m[abc[k]];
				for (i = 0; i < list.size(); i++)
				{
					s2 = list[i];
					if (wildcardMatch(s2.c_str(), s1.c_str()) == true)
						words.push_back(s2);
				}

			}
		}
		cout << "Match with: "<< endl;
		for (i = 0; i < words.size(); i++)
			cout << "	" << words[i] << endl;
		
	}
	else
		cout << endl << "ERRO" << endl;
}