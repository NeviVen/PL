#include "Header.h"

int main()
{
	LinkedList<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(121);
	lst.push_back(4);

	lst.insert(lst.find(2), 3);
	lst.pop(lst.find(121));

	lst.print();

	return 0;
}