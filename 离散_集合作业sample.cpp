#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>
#include <set>
#include "离散_二元关系.h"
using namespace std;
//包含两个类：SET（集合）、ordinal_pair（序偶）
//支持的数据类型：int,char,string,SET,ordinal_pair
//支持不同类型数据混合储存
//支持的运算：交（&&）、并（+）、差（-）、对称差（Symmetrical_difference(SET 1,SET2)）、幂集（SET.power()）、笛卡尔积（*）
//支持输出流<<操作，可直接将结果用cout输出

int main()
{
	ifstream input1;
	ifstream input2;
	ifstream input3;
	ifstream input4;
	ifstream input5;
#if 1
	input1.open("input1");
	input2.open("input2");

	SET SET0 = {};
	cout << "SET0:" << SET0 << endl;

	SET SET1;
	if (input11)
	{
		input11 >> SET1;
		cout << "SET1:" << SET1 << endl;
	}
	else
		cout << "input1 open failed" << endl;

	ordinal_pair op1 = { 25, string("Hello,world!")};
	cout << "op1:" << op1 << endl;

	SET SET2;
	if (input22)
	{
		input22 >> SET2;
		SET2.push(op1);
		cout << "SET2:" << SET2 << endl;
	}
	else
		cout << "input2 open failed" << endl;

	input11.close();
	input22.close();

	SET SET3 = { 1, 3, 5, 7 };
	SET3.push({ 'H', 'l' });
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
	for (Date T : SET5)
		cout << T << " ";
#endif // 集合演示

	std::cout << std::endl << std::endl;

#if 1
	input1.open("input1.txt");
	input2.open("input2.txt");
	input3.open("input3.txt");
	input4.open("input4.txt");
	input5.open("input5.txt");
	

	SET S1;
	SET S2;
	if (!input1)
		std::cout << "input1.txt open failed!" << endl;
	else
		input1 >> S1;
	if (!input2)
		std::cout << "input2.txt open failed!" << endl;
	else
		input2 >> S2;

	input1.close();
	input2.close();

	Binary_relationship BR1(S1);	 //S1上的二元关系
	Binary_relationship BR2(S1, S2); //S1到S2的二元关系
	Binary_relationship BR3, BR4, BR5, BR6, BR7;
	SET SET10, SET11, SET12;
	BR3 = Binary_relationship::E(S1);		  //全域
	BR4 = Binary_relationship::I(S1);		  //恒等
	BR5 = Binary_relationship::L(S1);		  //小于或等于
	BR6 = Binary_relationship::D(S2);		  //整除
	BR7 = Binary_relationship::R(S1.power()); //包含
	SET10 = Binary_relationship::domR(BR6);	  //定义域
	SET11 = Binary_relationship::ranR(BR6);	  //值域
	SET12 = Binary_relationship::fldR(BR6);	  //并集

	Binary_relationship BR11, BR12, BR13;

	if (!input3)
		std::cout << "input3.txt open failed!" << endl;
	else
	{
		ordinal_pair temp;
		while (input3 >> temp)
			BR11.push(temp);
		input3.close();
	}

	if (!input4)
		std::cout << "input4.txt open failed!" << endl;
	else
	{
		ordinal_pair temp;
		while (input4 >> temp)
			BR12.push(temp);
		input4.close();
	}

	if (!input5)
		std::cout << "input4.txt open failed!" << endl;
	else
	{
		ordinal_pair temp;
		while (input5 >> temp)
			BR13.push(temp);
		input5.close();
	}

	std::cout << "BR1:" << BR1 << endl
			  << "BR2:" << BR2 << endl
			  << endl
			  << "BR3:" << BR3 << endl
			  << endl
			  << "BR4:" << BR4 << endl
			  << endl
			  << "BR5:" << BR5 << endl
			  << endl
			  << "BR6:" << BR6 << endl
			  << endl
			  << "BR7:" << BR7 << endl
			  << endl
			  << "SET10:" << SET10 << endl
			  << endl
			  << "SET11:" << SET11 << endl
			  << endl
			  << "SET12:" << SET12 << endl
			  << endl
			  //自反、反自反
			  << "BR11自反？ " << BR11.Reflexive(S1) << endl
			  << endl
			  << "BR11反自反？ " << BR11.Anti_reflexive(S1) << endl
			  << endl
			  << "BR12自反？ " << BR12.Reflexive(S1) << endl
			  << endl
			  << "BR12反自反？ " << BR12.Anti_reflexive(S1) << endl
			  << endl
			  << "BR13自反？ " << BR13.Reflexive(S1) << endl
			  << endl
			  << "BR13反自反？ " << BR13.Anti_reflexive(S1) << endl
			  << endl
			  << "BR11对称？ " << BR11.Symmetry(S1) << endl
			  << endl
			  << "BR11反对称？ " << BR11.Antisymmetric(S1) << endl
			  << endl
			  << "BR12对称？ " << BR12.Symmetry(S1) << endl
			  << endl
			  << "BR12反对称？ " << BR12.Antisymmetric(S1) << endl
			  << endl
			  << "BR13对称？ " << BR13.Symmetry(S1) << endl
			  << endl
			  << "BR13反对称？ " << BR13.Antisymmetric(S1) << endl
			  << endl;

#endif // 二元关系演示

#if 0
	input1.open("g1.txt");
	input2.open("g2.txt");
	SET SET13;
	if (input1)
	{
		input1 >> SET13;
		std::cout << "SET13: " << SET13 << endl;
		input1.close();
	}
	else
		std::cout << "g1.txt open fail!" << endl;

	MSET MS1;
	Date t1;
	if (input2)
	{
		while (input2 >> t1)
		{
			MSET t2({ t1 });
			input2 >> t1;
			t2.push(t1);
			MS1.push(t2);
		}
		std::cout << "MS1: " << MS1 << endl;
		input2.close();
	}
	else
		std::cout << "g2.txt open fail!" << endl;
	

	Graphs G1(SET13, MS1);
	std::cout << "G1: " << G1 << endl;
	std::cout << "E_size: " << G1.E_size() << endl;
	std::cout << "V_size: " << G1.V_size() << endl;
	std::cout << "EG_empty? " << G1.EG_empty() << endl;
	std::cout << "Figure_empty? " << G1.Figure_empty() << endl;
	std::cout << "Associations: " << Graphs::Associations(Date(1), MSET({ 1,1 })) << endl;
	std::cout << "V_Adjacent? " << G1.V_Adjacent(Date(1), Date(4)) << endl;
	std::cout << "E_Adjacent? " << Graphs::E_Adjacent(MSET({ 1,2 }), MSET({ 2,3 })) << endl;
	std::cout << "E_Adjacent? " << Graphs::E_Adjacent(ordinal_pair(1, 2), ordinal_pair(3, 2)) << endl;
	std::cout << "link_branch: " << G1.link_branch();;

#endif

	//void *T;
	//T = (void*)new SET;
	//*(SET*)T = {1,2};
	//std::cout << *(SET*)T << std::endl;

	//delete T;
	//T = (void*)new int;
	//*(int*)T = 10;
	//std::cout << *(int*)T;
	
	return 0;
}
