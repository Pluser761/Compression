#include <iostream>
#include <fstream>
#include <string>
#include "HaphmannLib.h"

using namespace std;

int main()
{
	string s = "file.pdf";

	get_tree(s);

	system("pause");
	return 0;
}