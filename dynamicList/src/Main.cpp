/*
Author: Daniel Fernández
Date: 03/10/2017
*/

#include <iostream>
#include "List.h"

using exercise::List;
using namespace std;

void dump(List & list)
{
	if (!list.empty())
	{
		cout << "[#" << list.size() << "]: ";

		for (List::Iterator i = list.begin(); i != list.end(); ++i)
		{
			cout << *i << ", ";
		}
	} else
		cout << "[EMPTY]";

	cout << endl;
}

int main()
{
	List list;

	list.pushBack(2);
	list.pushFront(0);
	list.insert(list.begin(), 1);
	list.insert(list.end(), 3);

	dump(list);

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

	List::Iterator i = list.begin();

	i++;

	list.erase(i);

	dump(list);

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

	list.popFront();
	list.popBack();

	dump(list);

	// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

	list.pushBack(0);
	list.pushBack(0);
	list.pushBack(0);

	list.clear();

	dump(list);

	cin.get();

	return 0;
}


//int main() {
//
//	List list;
//
//	list.pushFront(1);
//	list.pushFront(2);
//	list.pushBack(3);
//
//	for (List::Iterator i = list.begin(); i != list.end(); ++i) {
//		cout << *i << ", ";
//	}
//	cout << endl;
//
//	return 0;
//}