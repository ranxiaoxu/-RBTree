#include<iostream>
#include<stdlib.h>
#include"RBTree.h"
using namespace std;

void test()
{
	RBTree<int,int> t;
	t.Insert(2,2);
	t.Insert(1,1);
	t.Insert(5,5);
	t.Insert(3,3);
	t.Insert(4,4);
	t.Insert(6,6);
	t.InOrder();

}
int main()
{
	test();
	system("pause");
	return 0;
}