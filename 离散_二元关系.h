#pragma once
#include "离散_集合作业.h"
using namespace std;



class Binary_relationship
{
public:
	Binary_relationship();
	Binary_relationship(SET &S);
	Binary_relationship(SET &S1, SET &S2);
	Binary_relationship E(SET &S);
	Binary_relationship I(const SET &S);
	SET domR(const Binary_relationship &br);
	~Binary_relationship();


private:
	SET Date;
};

Binary_relationship::Binary_relationship()
{
}

inline Binary_relationship::Binary_relationship(SET &S)
{
	Date = S * S;
}

inline Binary_relationship Binary_relationship::E(SET &S)
{
	Date = S * S;
	return *this;
}

inline Binary_relationship Binary_relationship::I(const SET& S)
{
	for (int i : S.IS)
		Date.push(ordinal_pair(i, i));
	for (char ch : S.CHS)
		Date.push(ordinal_pair(ch, ch));
	for (string s : S.STRS)
		Date.push(ordinal_pair(s, s));
	for (SET T : S.SETS)
		Date.push(ordinal_pair(T, T));
	for (ordinal_pair op : S.OPS)
		Date.push(ordinal_pair(op, op));
	return *this;

}

inline Binary_relationship::Binary_relationship(SET &S1, SET &S2)
{
	Date = S1 * S2;
}

inline SET Binary_relationship::domR(const Binary_relationship &br)
{
	SET temp;
	for(ordinal_pair T:br.Date.OPS)
		switch (T.type1)
		{
		case Int:
			temp.push(*T.I[0]);
		case Char:
			temp.push()
		default:
			break;
		}
	return SET();
}

inline Binary_relationship::~Binary_relationship()
{
}
