#pragma once
#include "离散_集合作业.h"
using namespace std;



class Binary_elationship:private SET
{
public:
	Binary_elationship();
	Binary_elationship(SET &S);
	Binary_elationship(SET S1, SET S2);
	SET E(SET S);
	SET I(const SET& S);
	~Binary_elationship();


private:
};

Binary_elationship::Binary_elationship()
{
}

inline Binary_elationship::Binary_elationship(SET &S)
{
	Date = S * S;
}

inline SET Binary_elationship::E(SET S)
{
	return S * S;
}

inline SET Binary_elationship::I(const SET& S)
{
	Date.CHS.begin();
	//for (int i : S.IS)
	//	Date.push(ordinal_pair(i, i));
}

inline Binary_elationship::Binary_elationship(SET S1, SET S2)
{
	Date = S1 * S2;
}

inline Binary_elationship::~Binary_elationship()
{
}
