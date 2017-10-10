/*
	Autor: Ángel
	Fecha: 3.oct.2017
*/

#include <iostream>
#include "List.hpp"
#include "Vector.hpp"

using namespace example;
using namespace std;

template< typename TYPE >
void dump (List< TYPE > & list)
{
    if (!list.empty ())
    {
        cout << "[#" << list.size () << "]: ";

		for (auto & item : list)
	    {
		    cout << item << ", ";
	    }
    }
    else
        cout << "[EMPTY]";

	cout << endl;
}
    
int main ()
{
	List< int > list;

	/*Vector< int,   3 > vector3i({ 0, 0, 0 });
	Vector< float, 3 > vector3f(vector3i);

	float f = vector3f;*/

    list.push_back  (2);
    list.push_front (0);
    list.insert     (list.begin (), 1);
    list.insert     (list.end   (), 3);

    dump (list);

    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

    auto i = list.begin ();

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
