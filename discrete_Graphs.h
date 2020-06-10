#pragma once
#include"discrete_SET.h"


class Graphs: public ordinal_pair
{
public:
	Graphs();
	Graphs(const SET &S1, const SET &S2);
	~Graphs();

private:
	bool Is_Directed;
};

Graphs::Graphs()
{
}

Graphs::~Graphs()
{
}
