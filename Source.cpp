#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <boost\tokenizer.hpp>
#include <locale>

using namespace std;

string read();
vector<string> split(const string&, const char*);
void print(const char&, const char*);
void print(const string&, const char*);

int main()
{
	setlocale(LC_ALL, "Russian");
	string text = read();
	cout << text << endl;
	vector<string> numbers = split(text, ";*:-+() ");
	vector<string> other = split(text, "XVI");
	bool isNumberFirst = false;

	if (text.find(numbers.front()) < text.find(other.front())) {
		isNumberFirst = true;
	}

	for (size_t i = 0, j = 0; i < numbers.size() || j < other.size(); i++, j++)
	{
		if (isNumberFirst && i < numbers.size() || !isNumberFirst && i < numbers.size())
		{
			print(numbers[i], "Число");
		}
		if (j < other.size()) 
		{
			for (auto symbol = other[j].begin(); symbol != other[j].end(); symbol++)
			{
				if (*symbol == '('){
					print(*symbol, "Раскрытие скобки");
				} else if (*symbol == ')') {
					print(*symbol, "Закрытие скобки");
				} else if (*symbol == '*') {
					print(*symbol, "Знак умножения");
				} else if (*symbol == ':') {
					print(*symbol, "Знак деления");
				} else if (*symbol == '+') {
					print(*symbol, "Знак сложения");
				} else if (*symbol == '-') {
					print(*symbol, "Знак вычитания");
				} else if (*symbol == ';') {
					print(*symbol, "Точка с запятой");
				}
			}
		}
	}
	return 0;
}

string read()
{
	string text;
	ifstream fin("input.txt");
	fin >> text;
	return text;
}

vector<string> split(const string& text, const char* delimiters)
{
	vector<string> result;
	boost::char_separator<char> sep(delimiters);
	boost::tokenizer<boost::char_separator<char>> tok(text, sep);
	for (auto iter = tok.begin(); iter != tok.end(); iter++) {
		result.push_back(*iter);
	}
	return result;
}

void print(const char& symbol, const char* type)
{
	cout << setw(10) << symbol << string(10, ' ') << type << "\n";
}

void print(const string& number, const char* type)
{
	cout << setw(10) << number << string(10, ' ') << type << '\n';
}
