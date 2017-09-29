/*
Author:	Daniel
Date:	28-09-2017
*/

#include <iostream>
#include "Array.hpp"

using namespace exercise;
using namespace std;

int main() {

	Array a(5);

	a.push_back(3);
	a.pop_back();
	a.insert(2, 5);
	//a.clear();

	//cout << a.get_size();

	a.get_item(3) = 8;

	for (size_t i = 0; i < a.get_size(); i++) {
		cout << a.get_item(i) << endl;
	}

	return 0;
}