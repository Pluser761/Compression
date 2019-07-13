#pragma once
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class tree
{
private:
	char letter;  // данные
	int quantity; // 
public:
	tree *first;
	tree *second;

	tree()
	{

	}
	tree(string file_name)
	{
		char *st = new char[file_name.length() + 1];

		for (int i = 0; i < file_name.length(); i++)
			st[i] = file_name[i];
		st[file_name.length()] = '\0';

		ifstream fin(st, ifstream::in | ifstream::binary);
		list<tree> letters; //алфавит-список
		char c;

		for (fin >> c; !fin.eof(); fin >> c) //создание алфавита-списка из файла
		{
			cout << c << endl;
			list<tree>::iterator finder = find(letters.begin(), letters.end(), tree(c));
			if (finder == letters.end())
				letters.push_back(tree(c));
			else
				(*finder)++;
		}

		while (letters.size() != 1) //проход по алфавиту-списку до единственного искомого tree
		{
			letters.sort([](tree &first, tree &second) -> bool
			{
				return (first.get_quantity() < second.get_quantity());
			});

			tree inserter(next(letters.begin(), 0), next(letters.begin(), 1));
			letters.pop_front();
			letters.pop_front();
			letters.push_front(inserter);
		}

		*this = letters.front();
	} // ***********
	tree(char l)
	{
		letter = l;
		quantity = 1;
		first = nullptr;
		second = nullptr;
	}
	tree(char l, int n)
	{
		letter = l;
		quantity = n;
		first = nullptr;
		second = nullptr;
	}
	tree(list<tree>::iterator t1, list<tree>::iterator t2)
	{
		quantity = 0;

		if (t1->quantity == 0)
			first = new tree(t1->first, t1->second);
		else
			first = new tree(t1->letter, t1->quantity);

		if (t2->quantity == 0)
			second = new tree(t2->first, t2->second);
		else
			second = new tree(t2->letter, t2->quantity);
	}
	tree(tree* t1, tree* t2)
	{
		if (t1->quantity == 0)
			first = new tree(t1->first, t1->second);
		else
			first = new tree(t1->letter, t1->quantity);

		if (t2->quantity == 0)
			second = new tree(t2->first, t2->second);
		else
			second = new tree(t2->letter, t2->quantity);
	}
	~tree()
	{

	}

	void operator++(int)
	{
		this->quantity++;
	}
	bool const operator==(const tree& st)
	{
		return (st.letter == letter);
	}
	friend ostream& operator<<(ostream& out, const tree& st)
	{
		if (st.first)
			out << *(st.first);
		if (st.quantity != 0)
			out << "\"" << st.letter << "\"" << endl;
		if (st.second)
			out << *(st.second);
		return out;
	}

	char const get_letter()
	{
		if (quantity != 0) return this->letter;
		else exit(1);
	}
	int const get_quantity()
	{
		if (quantity == 0) return first->get_quantity() + second->get_quantity();
		else return this->quantity;
	}
	void codes_collection(map<char, string> &ret, string s)
	{
		if (quantity == 0)
		{
			first->codes_collection(ret, s + '0');
			second->codes_collection(ret, s + '1');
		}
		else
		{
			ret.insert(pair<char, string>(this->letter, s));
		}
	}
};

tree get_tree(string s)
{
	char *st = new char[s.length()+1];

	for (int i = 0; i < s.length(); i++)
		st[i] = s[i];
	st[s.length()] = '\0';

	ifstream fin(st, ifstream::in | ifstream::binary);
	list<tree> letters; //алфавит
	char byte;
	fin.read(&byte, sizeof(char));

	for (int i = 0; i < sizeof(fin); i++, fin.read(&byte, sizeof(char)))
	{
		cout << byte << endl;
		list<tree>::iterator finder = find(letters.begin(), letters.end(), tree(byte));
		if (finder == letters.end())
			letters.push_back(tree(byte));
		else
			(*finder)++;
	}

	while (letters.size() != 1)
	{
		letters.sort([](tree &first, tree &second) -> bool
		{
			return (first.get_quantity() < second.get_quantity());
		});

		tree inserter(next(letters.begin(), 0), next(letters.begin(), 1));
		letters.pop_front();
		letters.pop_front();
		letters.push_front(inserter);
	}
	
	//output letters


	return letters.front();
}

