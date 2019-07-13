#include <iostream>
#include <fstream>
#include <string>
#include "HaphmannLib.h"
#include <windows.h>
#include <locale>

using namespace std;

//int main()
//{
//	string s = "file.pdf";
//
//	ifstream fin(s, ifstream::in | ifstream::binary);
//	ofstream fout("archive_" + s.substr(0, s.length() - 3) + "arc", ofstream::out);
//
//	char c;
//	fin >> c;
//	for ( int i = 0; i < sizeof(fin); i++, fin >> c)
//	{
//		fout << c << " | ";
//	}
//
//	fin.close();
//
//	system("pause");
//	return 0;
//}



int main()
{
	string s = "file.pdf";
	map<char, string> coll;

	//get_tree(s).codes_collection(coll, "1");
	tree(s).codes_collection(coll, "1");

	fstream fin(s, ifstream::in | ifstream::binary);
	fstream fout("archive_" + s.substr(0, s.length() - 3) + "arc", ofstream::out);

	fout << s.substr(5, s.length()) << endl; //формат файла
	for (auto it = coll.begin(); it != coll.end(); ++it) //дерево с разделителем :
		fout << it->first << ":" << it->second << endl;
	fout << "%%%" << endl; //конец алфавита

	char byte, c;
	fin.read(&byte, sizeof(char));
	for ( int i = 0; i < sizeof(fin)/ sizeof(char); i++, fin.read(&byte, sizeof(char))) //чтение всех байтов fin
		fout << coll.find((char)byte)->second << "_"; //поиск файла в коллекции map

	coll.clear();
	fin.close();
	fout.close();


	return 0;



	map<string, char> uncoll;
	fin.open("archive_" + s.substr(0, s.length() - 3) + "arc", ifstream::in);
	getline(fin, s);
	fout.open("unarchived." + s, ofstream::out | ofstream::binary);

	for (fin >> s; s != "%%%"; fin >> s)//воссоздание дерева
	{
		cout << s << endl;
		uncoll.insert(pair<string, char>(s.substr(2, s.length()), s[0]));
		//system("pause");
	}
	
	string temp = "";
	for (fin >> c; !fin.eof(); fin >> c)
	{
		if (c != '_')
		{
			temp += c;
		}
		else
		{
			fout << uncoll.find(temp)->second;
			temp = "";
		}
	}

	fin.close();
	fout.close();

	//system("pause");
	return 0;
}
