#pragma once
#include <set>
#include"discrete_SET.h"


class Graphs: public ordinal_pair
{
public:
	Graphs();
	Graphs(const SET &S1, MSET S2);
	static bool Is_Graphs(SET S1, MSET S2);
	~Graphs();

	static Graphs G(const SET &S1, MSET S2);
	static Graphs E(const SET &S1, MSET S2);
	unsigned int V_size() { return date[0].SETT().size(); };
	unsigned int E_size() { return date[1].SETT().size(); };
	bool EG_empty() { return date[1].SETT().size() == 0; };
	bool Figure_empty() { return date[0].SETT().size() == 0; };
	static unsigned int Associations(Date d,MSET S);
	bool V_Adjacent(Date d1, Date d2);
	static bool E_Adjacent(MSET S1,MSET S2);
	static bool E_Adjacent(ordinal_pair op1, ordinal_pair op2);
	unsigned int link_branch();

private:
	void link_branch(Date d,set<Date> &traversaled,unsigned int &sum);
	bool Is_Directed;
};

Graphs::Graphs()
{
}

inline bool Graphs::Is_Graphs(SET S1, MSET  S2)
{
	types T = (*S2.begin()).ty();
	if (T != Ordinal_pair && T != MSet)
		return false;

	for (Date d : S2)
	{
		if (d.ty() != T)
			return false;
	}
	for (Date d : S2)
	{
		switch (d.ty())
		{
		case Ordinal_pair:
			if (S1.find(d.OP().date1()) == S1.end() && S1.find(d.OP().date2()) == S1.end())
				return false;
			break;
		case MSet:
		{
			if (S1.find(*d.MSETT().begin()) == S1.end() && S1.find(*(++d.MSETT().begin())) == S1.end())
				return false;
		}
		default:
			break;
		}
	}
	return true;
}

inline Graphs::Graphs(const SET & S1, MSET S2)
{
	if (!Is_Graphs(S1, S2))
	{
		std::cout << "This is not a Graphs!" << std::endl;
		return;
	}
	if ((*S2.begin()).ty() == Ordinal_pair)
		Is_Directed = true;
	else
		Is_Directed = false;
	date[0] = S1;
	date[1] = S2;
}

Graphs::~Graphs()
{
}

inline Graphs Graphs::G(const SET & S1, MSET S2)
{
	if ((*S2.begin()).ty() != MSet)
	{
		std::cout << "this is not a Undirected graph!" << std::endl;
		return Graphs();
	}
	return Graphs(S1, S2);
}

inline Graphs Graphs::E(const SET & S1, MSET S2)
{
	if ((*S2.begin()).ty() != Ordinal_pair)
	{
		std::cout << "this is not a Undirected graph!" << std::endl;
		return Graphs();
	}
	return Graphs(S1, S2);
}

inline unsigned int Graphs::Associations(Date d,MSET S)
{
	unsigned int t = 0;
	MSET::iterator it = S.begin();
	if (*it == d)
		t++;
	++it;
	if (*it == d)
		t++;
	return t;
}

inline bool Graphs::V_Adjacent(Date d1, Date d2)
{
	if (Is_Directed)
	{
		std::cout << "not a Undirected graph!" << std::endl;
		return false;
	}
	if (date[0].SETT().find(d1) == date[0].SETT().end() || date[0].SETT().find(d2) == date[0].SETT().end())
	{
		std::cout << "can't find the vertex!" << std::endl;
		return false;
	}
	
	if (Is_Directed)
	{
		if (date[1].MSETT().find(Date(MSET({ d1,d2 }))) != date[1].MSETT().end())
			return true;
		else
			return false;
	}
	else
	{
		if ((date[1].MSETT().find(Date(ordinal_pair(d1, d2))) != date[1].MSETT().end()) || (date[1].MSETT().find(Date(ordinal_pair(d2, d1))) != date[1].MSETT().end()))
			return true;
		else
			return false;
	}
	
}

inline bool Graphs::E_Adjacent(MSET S1, MSET S2)
{
	MSET::iterator it = S1.begin();
	if (S2.find(*it) != S2.end())
		return true;
	++it;
	if (S2.find(*it) != S2.end())
		return true;

	return false;
}

inline bool Graphs::E_Adjacent(ordinal_pair op1, ordinal_pair op2)
{
	return op1.date2() == op2.date1();
}

inline unsigned int Graphs::link_branch()
{
	set<Date> traversaled;
	unsigned int sum = 0;
	for(Date d:date[0].SETT())
		link_branch(d , traversaled, sum);
	return sum;
}

inline void Graphs::link_branch(Date d, set<Date> &traversaled, unsigned int &sum)
{
	if (traversaled.find(d) != traversaled.end())
		return;
	traversaled.insert(d);
	if (Is_Directed)
	{

	}
	else
	{
		MSET::iterator it;
		for (it=date[1].MSETT().begin();it!= date[1].MSETT().end();++it)
		{
			if (*(*it).MSETT().begin() == d)
			{
				if (traversaled.find(*(++(*it).MSETT().begin())) != traversaled.end())
				{
					link_branch(*(++(*it).MSETT().begin()), traversaled, sum);
					break;
				}
			}
		}
		if (it == date[1].MSETT().end())
		{
			sum++;
		}
		
	}
}