#pragma once
#include <list>
#include <algorithm>

using namespace std;

class node
{
private:
	char letter;
	char second_letter;
	int quantity;
public:
	node()
	{

	}
	node(char l)
	{
		letter = l;
		quantity = 1;
	}
	~node()
	{}
	void operator++(int)
	{
		quantity++;
	}
	bool const operator==(const node& st)
	{
		return (st.letter == letter);
	}
	bool const operator==(const char& st)
	{
		return (st == letter);
	}
	char const get_letter() { return letter; }
	int const get_quantity() { return quantity; }

};

struct branch
{
	node data;
	branch *l, *r;
};

list<node> letters; //алфавит

void writer()
{
	for_each(letters.begin(), letters.end(), [](node n)
	{
		cout << n.get_letter() << " = " << n.get_quantity() << endl;
	}
	);
}

list<int> code(string s)
{
	char *st = new char[s.length()+1];

	for (int i = 0; i < s.length(); i++)
		st[i] = s[i];
	st[s.length()] = '\0';

	ifstream fin(st, ifstream::in);
	ofstream fout("Text.txt", ofstream::out);
	char c;

	for (fin >> c; !fin.eof(); fin >> c)
	{
		//fout << c;
		list<node>::iterator finder = find(letters.begin(), letters.end(), c);
		if (finder == letters.end())
		{
			letters.push_back(node(c));
		}
		else
			(*finder)++;
	}

	writer();
	

	return list<int>();
}

