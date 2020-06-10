#pragma once
#include "离散_集合作业.h"
#include <algorithm>
#include <iostream>


class Binary_relationship
{
public:
	Binary_relationship();									//构造
	Binary_relationship(initializer_list<ordinal_pair> op); //用序偶列表初始化
	void push(const ordinal_pair &op);						//添加元素
	Binary_relationship(SET &S);							//S的二元关系
	Binary_relationship(SET &S1, SET &S2);					//S1到S2的二元关系
	static Binary_relationship E(SET &S);					//全域关系
	static Binary_relationship I(const SET &S);				//恒等关系
	static Binary_relationship L(const SET &S);				//小于或等于关系
	static Binary_relationship D(const SET &S);				//整除关系
	static Binary_relationship R(const SET &S);				//包含关系
	static SET domR(const Binary_relationship &br);			//定义域
	static SET ranR(const Binary_relationship &br);			//值域
	static SET fldR(const Binary_relationship &br);			//并集
	bool Reflexive(const SET &S);							//s1自反
	bool Anti_reflexive(const SET &S);						//反自反
	bool Symmetry(SET S);									//对称
	bool Antisymmetric(SET S);								//反对称
	void Transfer(SET S) {};					//传递

	~Binary_relationship(); //析构

	friend ostream &operator<<(ostream &os, Binary_relationship &BR); //输出流<<重载

private:
	SET date;
};

Binary_relationship::Binary_relationship()
{
}

inline Binary_relationship::Binary_relationship(initializer_list<ordinal_pair> op)
{
	date.push(op);
}

inline void Binary_relationship::push(const ordinal_pair &op)
{
	date.push(op);
}

inline Binary_relationship::Binary_relationship(SET &S)
{
	date = S * S;
}

inline Binary_relationship Binary_relationship::E(SET &S)
{
	Binary_relationship Temp;
	Temp.date = S * S;
	return Temp;
}

inline Binary_relationship Binary_relationship::I(const SET &S)
{
	Binary_relationship temp;
	for (Date date : S.DATES)
		temp.date.push(ordinal_pair(date, date));
	/*for (char ch : S.CHS)
		temp.date.push(ordinal_pair(ch, ch));
	for (string s : S.STRS)
		temp.date.push(ordinal_pair(s, s));
	for (SET T : S.SETS)
		temp.date.push(ordinal_pair(T, T));
	for (ordinal_pair op : S.OPS)
		temp.date.push(ordinal_pair(op, op));*/
	return temp;
}

inline Binary_relationship Binary_relationship::L(const SET &S)
{
	Binary_relationship temp;
	/*if (S.CHS.size() > 0 || S.STRS.size() > 0 || S.SETS.size() > 0 || S.OPS.size() > 0 || S.IS.size() == 0)
		return Binary_relationship();*/

	for (Date i1 : S.DATES)
		for (Date i2 : S.DATES)
			if (i1 < i2 || i1 == i2)
				temp.date.push(ordinal_pair(i1, i2));
	return temp;
}

inline Binary_relationship Binary_relationship::D(const SET &S)
{
	Binary_relationship temp;
	/*if (S.CHS.size() > 0 || S.STRS.size() > 0 || S.SETS.size() > 0 || S.OPS.size() > 0 || S.IS.size() == 0)
		return Binary_relationship();*/
	for (Date i1 : S.DATES)
		for (Date i2 : S.DATES)
			if (i2 % i1 == 0)
				temp.date.push(ordinal_pair(i1, i2));
	return temp;
}

inline Binary_relationship Binary_relationship::R(const SET &S)
{
	Binary_relationship temp;
	/*if (S.CHS.size() > 0 || S.STRS.size() > 0 || S.OPS.size() > 0 || S.IS.size() > 0 || S.SETS.size() == 0)
		return Binary_relationship();*/
	
	for (Date T1 : S.DATES)
	{
		for (Date T2 : S.DATES)
		{
			if (T1.ty != Set || T2.ty != Set)
			{
				std::cout << "含有非集合元素！" << endl;
				return Binary_relationship();
			}
			SET::iterator it3 = T2.SETT->begin();
			for (; it3 != T2.SETT->end(); ++it3)
			{
				if (T1.SETT->find(*it3)==T1.SETT->end())
					break;
			}
			if (it3 == T2.SETT->end())
				temp.date.push(ordinal_pair(T1, T2));
		}
	}
	return temp;
}

inline Binary_relationship::Binary_relationship(SET &S1, SET &S2)
{
	date = S1 * S2;
}

inline SET Binary_relationship::domR(const Binary_relationship &br)
{
	SET temp;
	for (Date T : br.date.DATES)
		temp.push(T.OP->date[0]);
	return temp;
}

inline SET Binary_relationship::ranR(const Binary_relationship &br)
{
	SET temp;
	for (Date T : br.date.DATES)
		temp.push(T.OP->date[1]);
	return temp;
}

inline SET Binary_relationship::fldR(const Binary_relationship &br)
{
	SET temp = domR(br) + ranR(br);
	return temp;
}

inline bool Binary_relationship::Reflexive(const SET &S)
{
	for (Date i : S.DATES)
		if (date.find(Date(ordinal_pair(i, i)))==date.end())
			return false;
	return true;
}

inline bool Binary_relationship::Anti_reflexive(const SET &S)
{
	for (Date i : S.DATES)
		if (date.find(Date(ordinal_pair(i, i))) != date.end())
			return false;
	return true;
}

inline bool Binary_relationship::Symmetry(SET S)
{
	Binary_relationship temp = E(S);
	for (Date op : date.DATES)
		if (temp.date.find(op)==temp.date.end() || date.find(Date(op.OP->anti()))==temp.date.end())
			return false;
	return true;
}

inline bool Binary_relationship::Antisymmetric(SET S)
{
	Binary_relationship temp = E(S);
	for (Date op : date.DATES)
	{
		if (temp.date.find(op)!=temp.date.end())
		{
			if (date.find(Date(op.OP->anti()))!=date.end() && !(*op.OP == op.OP->anti()))
				return false;
		}
		else
			return false;
	}
	return true;
}

inline Binary_relationship::~Binary_relationship()
{
}

ostream &operator<<(ostream &os, Binary_relationship &BR)
{
	os << BR.date;
	// TODO: 在此处插入 return 语句
	return os;
}
