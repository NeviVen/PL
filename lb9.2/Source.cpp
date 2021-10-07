#include "Header.h"
#include <iostream>
using namespace std;
obj one;
obj two;
int a = 123;
bool b = true;
void obj::set_ab() {
	this->arg1 = a;
	this->arg2 = b;
}
void obj::out() {
	cout << this->arg1 << endl << this->arg2 << endl;
}
void change_args() {
	one.set_ab();
	two.set_ab();
}
int obj::arg1 = 0;
bool obj::arg2 = false;

#include "Header.h"
#include <iostream>
using namespace std;
int main()
{
	extern obj one;
	extern obj two;
	obj three;


	change_args();
	one.out();
	two.out();
}