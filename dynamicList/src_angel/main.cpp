/*
	Autor: Ángel
	Fecha: 3.oct.2017
*/

#include <iostream>
#include "List.hpp"

using example::List;
using namespace std;

void dump (List & list)
{
    if (!list.empty ())
    {
        cout << "[#" << list.size () << "]: ";

	    for (List::Iterator i = list.begin(); i != list.end(); ++i)
	    {
		    cout << *i << ", ";
	    }
    }
    else
        cout << "[EMPTY]";

	cout << endl;
}
    
int main ()
{
	List list;

    list.push_back  (2);
    list.push_front (0);
    list.insert     (list.begin (), 1);
    list.insert     (list.end   (), 3);

    dump (list);

    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

    List::Iterator i = list.begin ();

    i++;

    list.erase (i);

    dump (list);

    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

    list.pop_front ();
    list.pop_back  ();

    dump (list);

    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

    list.push_back (0);
    list.push_back (0);
    list.push_back (0);

    list.clear ();

    dump (list);

    cin.get ();

	return 0;
}
