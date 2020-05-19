#include <iostream>
#include <fstream>
#include "离散_集合作业.h"
using namespace std;
//包含两个类：SET（集合）、ordinal_pair（序偶）
//支持的数据类型：int,char,string,SET,ordinal_pair
//支持不同类型数据混合储存
//支持的运算：交（&&）、并（+）、差（-）、对称差（Symmetrical_difference(SET 1,SET2)）、幂集（SET.power()）、笛卡尔积（*）
//支持输出流<<操作，可直接将结果用cout输出

int main()
{
	ifstream input1("input1.txt");
	ifstream input2("input2.txt");

	SET SET0 = {};
	cout << "SET0:" << SET0 << endl;

	SET SET1;
	if (input1)
	{
		input1 >> SET1;
		cout << "SET1:" << SET1 << endl;
	}
	else
		cout << "input1 open failed" << endl;

	ordinal_pair op1 = {25, "Hello,world!"};
	cout << "op1:" << op1 << endl;
	;

	SET SET2;
	if (input2)
	{
		input2 >> SET2;
		SET2.push(op1);
		cout << "SET2:" << SET2 << endl;
		;
	}
	else
		cout << "input2 open failed" << endl;

	input1.close();
	input2.close();

	SET SET3 = {1, 3, 5, 7};
	SET3.push({'H', 'l'});
	SET3.push(SET1);
	SET3.push(op1);
	cout << "SET3:" << SET3 << endl;

	SET SET4 = SET1 - SET3;
	cout << "SET4:" << SET4 << endl;

	SET SET5 = SET1 + SET3;
	cout << "SET5:" << SET5 << endl;

	SET SET6 = SET1 && SET3;
	cout << "SET6:" << SET6 << endl;

	SET SET7 = Symmetrical_difference(SET1, SET3);
	cout << "SET7:" << SET7 << endl;

	SET SET8 = SET4.power();
	cout << "SET8:" << SET8 << endl;

	SET SET9 = SET5 * SET6;
	cout << "SET9:" << SET9 << endl;

	cout << endl;

	SET::iterator its = SET5.begin(); //迭代器
	++its;
	cout << *its << endl;
	for (SET T : SET5)
		cout << T << " ";

	return 0;
}
