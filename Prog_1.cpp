#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

char abc[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

void mapOrder(map<char, vector < string >> &map)
{
	for (int k = 0; k < map.size(); k++) {
		vector < string > list = map[abc[k]];

		sort(list.begin(), list.end());

		map[abc[k]] = list;
	}
}

int mapSize(map<char, vector < string >> map)
{
	int size=0;
	for (int k = 0; k < map.size(); k++) {
		size += map[abc[k]].size();
	}
	return size;
}

void mapDups(map<char, vector < string >> &map)
{
	for (int k = 0; k < map.size(); k++) {
		vector < string > list = map[abc[k]];
		
		int i = 0, size = list.size() - 1, c= 0;

		while (i < size)
		{		
			string word0 = list[i];
			string word1 = list[i + 1];
			if (word0 == word1)
			{
				list.erase(list.begin()+i+1);
				c++;
			}
			else i++;
			if (c % 100 == 0 && c != 0)	cout << '.';
			size = list.size() - 1;
		}
		map[abc[k]] = list;
	}
	cout << endl << endl;
}

int main()
{
	string file, file_word_list, line, word;
	map<char, vector < string >> m;
	size_t pos, i;
	string alf = "ABCDEFGHIJLMNOPQRSTUVWXYZ";
	int cont = 0;
	int contL = 0;

	cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
	cout << "======================================" << endl << endl;
	cout << "Dictionary file ? ";
	cin >> file;
	cout << "Word list file ? ";
	cin >> file_word_list; cout << endl;
	cout << "Extracting simple words from file "<< file << "," << endl;
	cout << "beginning with letter ..." << endl << endl;

	ifstream f(file);

	while ( getline(f,line) )
	{
		pos = line.find_first_not_of("QWERTYUIOPASDFGHJKLZXCVBNM ;-'");
		if (pos == string::npos)
		{

			
			for (i = 0; i < line.length(); i++)
			{
				if (line[i] >= 'A' && line[i] <= 'Z')
				{
					word = word + line[i];
				}
				else if (line[i] == '-' || line[i] == '\'' || line[i] == ' ')
				{
					word.clear();
					i = line.find_first_of(";", i);
					if (i == string::npos)
						i = line.length();
					else if (line[i + 1] == ' ')
						i++;
					
				}
				else if (line[i] == ';')
				{
					//imprimir pontos//
					if (word[0] == alf[contL])
					{
						if (m.empty())
						{
							cout << 'A' << endl;
							cont = 1;
						}
						else
						{
							cont++;
							if (cont % 100 == 0 && cont != 0)
								cout << '.';
						}
					}
					else if (word[0] == alf[contL + 1])
					{
						contL++;
						cout << endl << word[0] << endl;
						cont = 1;
					}
					//********************************//
					m[word.at(0)].push_back(word);
					word.clear();
					if (line[i + 1] == ' ')
						i = i + 1;
					
				}
					
			}
			if (word.length() != NULL)
			{
				//imprimir pontos//
				if (word[0] == alf[contL])
				{
					if (m.empty())
					{
						cout << 'A' << endl;
						cont = 1;
					}
					else
					{
						cont++;
						if (cont % 100 == 0 && cont != 0)
							cout << '.';
					}
				}
				else if (word[0] == alf[contL + 1])
				{
					contL++;
					cout << endl << word[0] << endl;
					cont = 1;
				}
				//********************************//
				m[word.at(0)].push_back(word);
				word.clear();
			}
			
		}
		line.clear();	

	}

	f.close();

	mapOrder(m);

	cout << endl << endl << "Number of simple words = " << mapSize(m)<< endl << endl << "Sorting words ..." << endl << endl;

	cout << "Removing duplicate words ..." << endl << endl;

	mapDups(m);

	cout << "Number of non - duplicate simple words = " << mapSize(m) << endl << endl;

	cout << "Saving words into file " << file_word_list << " ..." << endl << endl;
	
	ofstream f_lista(file_word_list);

	for (int k = 0; k < m.size(); k++) {
		vector < string > list = m[abc[k]];
		for (i = 0; i < m[abc[k]].size(); i++) {			
			f_lista << list[i] << endl;
		}
	}

	f_lista.close();

	cout << "End of processing." << endl << endl;
	


}