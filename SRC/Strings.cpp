#include "Strings.h"
#include <iostream>
using namespace std;

char* Strings::strdupl(const char* s) {
	//length of source
	int len = strlen(s) + 1;
	//allocate memory enough for copy
	char* dest = nullptr;
	try {
		dest = new char[len];
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what();
		exit(1);
	}
	for (int i = 0; i < len; i++)
		dest[i] = s[i];
	return dest;
}
