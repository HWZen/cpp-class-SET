#pragma once
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class SET;											//SET类声明
class ordinal_pair;									//序偶类声明
ostream &operator<<(ostream &os, SET &S);			//SET类重载<<声明
ostream &operator<<(ostream &os, ordinal_pair &op); //序偶类重载<<声明
enum types											//枚举类型定义声明
{
	Int,
	Char,
	Str,
	Set,
	Ordinal_pair,
	null
};

/************序偶完整声明**************/
class ordinal_pair
{
public:
	/*************构造函数（5重载）****************/
	/**********5月10日，开始用模板代替重载*********/
	ordinal_pair();

	//折中解决const char** 无法强制转换成string*的bug
#if 1
	template <typename T2>
	ordinal_pair(const char *chs, T2 t2);

	template <typename T1>
	ordinal_pair(T1 t1, const char *chs);
#endif

	template <typename T1, typename T2>
	ordinal_pair(T1 t1, T2 t2);

	ordinal_pair(const ordinal_pair &op);

	void operator=(const ordinal_pair &op);											   //重载赋值运算
	~ordinal_pair();																   //析构函数
	bool operator==(const ordinal_pair &O);											   //重载符号==
	bool operator<(const ordinal_pair &op) const { return (OPHash() < op.OPHash()); }; //重载符号<
	friend ostream &operator<<(ostream &os, ordinal_pair &op);						   //声明重载符号<<(友元)

	/**********第一、第二分量设置函数（5*2重载）************/
	void component1(int t);
	void component1(char t);
	void component1(string t);
	void component1(SET t);
	void component1(ordinal_pair t);
	void component2(int t);
	void component2(char t);
	void component2(string t);
	void component2(SET t);
	void component2(ordinal_pair t);

	size_t OPHash() const; //序偶变量量化函数，用于不同序偶变量的比较

private:
	enum types type1, type2; //第一、第二变量类型

	/********储存分量数据，允许int,char,string,SET和序偶类型作为分量*******/
	/*******************5月10日，全部数据用指针代替常量********************/
	int *I[2];
	char *CH[2];
	string *STR[2];
	SET *SETT[2];
	ordinal_pair *OP[2];
};

/**************SET完整声明****************/
class SET
{
public:
	/******************构造函数（7重载）*******************/
	SET() { Empty = true; };
	SET(const SET &S);
	SET(initializer_list<int> I)
	{
		IS.insert(I);
		Empty = false;
	};
	SET(initializer_list<char> ch)
	{
		CHS.insert(ch);
		Empty = false;
	};
	SET(initializer_list<string> str)
	{
		STRS.insert(str);
		Empty = false;
	};
	SET(initializer_list<ordinal_pair> op)
	{
		OPS.insert(op);
		Empty = false;
	};
	SET(initializer_list<SET> Set)
	{
		SETS.insert(Set);
		Empty = false;
	};

	class iterator //迭代器
	{
	public:
		iterator() {};
		iterator(SET *i, int p) : THIS(i), pos(p) {}

		~iterator() {};

		bool operator!=(iterator it) //重载!=
		{
			return (this->pos != it.pos) || (this->THIS != it.THIS);
		}

		bool operator==(iterator it) //重载==
		{
			return (this->pos == it.pos) && (this->THIS == it.THIS);
		}

		iterator operator++() //重载++
		{
			pos++;
			return *this;
		}

		SET &operator*() //重载*
		{
			int Pos = pos;
			if (Pos < THIS->IS.size())
			{
				set<int>::iterator iti = THIS->IS.begin();
				for (int i = 0; i < Pos; i++)
					iti++;
				SET *Temp = new SET;
				*Temp = { *iti };
				return *Temp;
			}
			Pos -= THIS->IS.size();
			if (Pos < THIS->CHS.size())
			{
				set<char>::iterator itch = THIS->CHS.begin();
				for (int i = 0; i < Pos; i++)
					itch++;
				SET *Temp = new SET;
				*Temp = { *itch };
				return *Temp;
			}
			Pos -= THIS->CHS.size();
			if (Pos < THIS->STRS.size())
			{
				set<string>::iterator itstr = THIS->STRS.begin();
				for (int i = 0; i < Pos; i++)
					itstr++;
				SET *Temp = new SET;
				*Temp = { *itstr };
				return *Temp;
			}
			Pos -= THIS->STRS.size();
			if (Pos < THIS->SETS.size())
			{
				set<SET>::iterator itset = THIS->SETS.begin();
				for (int i = 0; i < Pos; i++)
					itset++;
				SET *Temp = new SET;
				*Temp = { *itset };
				return *Temp;
			}
			Pos -= THIS->SETS.size();
			if (Pos < THIS->OPS.size())
			{
				set<ordinal_pair>::iterator itop = THIS->OPS.begin();
				for (int i = 0; i < Pos; i++)
					itop++;
				SET *Temp = new SET;
				*Temp = { *itop };
				return *Temp;
			}
			SET *Temp = new SET;
			return *Temp;
		}

	private:
		SET *THIS = nullptr;
		int pos = 0;
		int *I = nullptr;
		char *CH = nullptr;
		string *STR = nullptr;
		SET *SETT = nullptr;
		ordinal_pair *OP = nullptr;
	};
	iterator begin() { return iterator(this, 0); }		   //返回头部迭代器
	iterator end() { return iterator(this, (int)size()); } //返回尾部迭代器

	~SET() {}; //析构函数

	bool operator==(const SET &S);												   //重载==
	void operator=(const SET &S);												   //重载赋值运算
	inline bool operator<(const SET &S) const { return SETHash() < S.SETHash(); }; //重载<
	SET operator+(const SET &S);												   //重载+（并集）
	SET operator&&(const SET &S);												   //重载&（交集）
	SET operator-(const SET &S);												   //重载-（差集）
	SET operator*(const SET &S);												   //重载*（笛卡尔积）
	SET power();																   //幂集
	void power(int i, SET T, SET *Res);											   //幂集执行函数
	friend SET Symmetrical_difference(const SET &S1, const SET &S2);			   //对称差（友元）
	friend ostream &operator<<(ostream &os, SET &S);							   //声明重载符号<<(友元)
	friend istream &operator>>(istream &in, SET &S);							   //声明重载符号>>(友元)
	size_t size() const;														   //返回元素个数
	size_t SETHash() const;														   //SET变量量化函数，用于不同序偶变量的比较

	/*****************添加元素函数（5重载）*******************/
	inline void push(int I)
	{
		IS.insert(I);
		Empty = false;
	};
	inline void push(char ch)
	{
		CHS.insert(ch);
		Empty = false;
	};
	inline void push(string str)
	{
		STRS.insert(str);
		Empty = false;
	};
	inline void push(SET Set)
	{
		SETS.insert(Set);
		Empty = false;
	};
	inline void push(ordinal_pair op)
	{
		OPS.insert(op);
		Empty = false;
	};
	inline void push(initializer_list<int> I)
	{
		IS.insert(I);
		Empty = false;
	};
	inline void push(initializer_list<char> ch)
	{
		CHS.insert(ch);
		Empty = false;
	};
	inline void push(initializer_list<string> str)
	{
		STRS.insert(str);
		Empty = false;
	};
	inline void push(initializer_list<SET> Set)
	{
		SETS.insert(Set);
		Empty = false;
	};
	inline void push(initializer_list<ordinal_pair> op)
	{
		OPS.insert(op);
		Empty = false;
	};

private:
	bool Empty; //是否包含空集

	/*储存元素数据，允许int,char,string,SET和序偶类型作为元素*/
	set<int> IS;
	set<char> CHS;
	set<string> STRS;
	set<SET> SETS;
	set<ordinal_pair> OPS;
};

/************************序偶函数定义****************************/

void ordinal_pair::operator=(const ordinal_pair &op)
{
	type1 = op.type1;
	type2 = op.type2;
	switch (type1)
	{
	case Int:
		delete I[0];
		I[0] = new int;
		*I[0] = *op.I[0];
		break;
	case Char:
		delete CH[0];
		CH[0] = new char;
		*CH[0] = *op.CH[0];
		break;
	case Str:
		delete STR[0];
		STR[0] = new string;
		*STR[0] = *op.STR[0];
		break;
	case Set:
		delete SETT[0];
		SETT[0] = new SET;
		*SETT[0] = *op.SETT[0];
		break;
	case Ordinal_pair:
		delete OP[0];
		OP[0] = new ordinal_pair;
		*OP[0] = *op.OP[0];
		break;
	case null:
		break;
	default:
		break;
	}
	switch (type2)
	{
	case Int:
		delete I[1];
		I[1] = new int;
		*I[1] = *op.I[1];
		break;
	case Char:
		delete CH[1];
		CH[1] = new char;
		*CH[1] = *op.CH[1];
		break;
	case Str:
		delete STR[1];
		STR[1] = new string;
		*STR[1] = *op.STR[1];
		break;
	case Set:
		delete SETT[1];
		SETT[1] = new SET;
		*SETT[1] = *op.SETT[1];
		break;
	case Ordinal_pair:
		delete OP[1];
		OP[1] = new ordinal_pair;
		*OP[1] = *op.OP[1];
		break;
	case null:
		break;
	default:
		break;
	}
}

ordinal_pair::ordinal_pair()
{
	type1 = null;
	type2 = null;
	I[0] = NULL;
	I[1] = NULL;
	CH[0] = NULL;
	CH[1] = NULL;
	STR[0] = NULL;
	STR[1] = NULL;
	SETT[0] = NULL;
	SETT[1] = NULL;
	OP[0] = NULL;
	OP[1] = NULL;
}

inline ordinal_pair::~ordinal_pair()
{
	if (SETT[0] != NULL)
		delete SETT[0];
	SETT[0] = NULL;
	if (SETT[1] != NULL)
		delete SETT[1];
	SETT[1] = NULL;
	if (OP[0] != NULL)
		delete OP[0];
	OP[0] = NULL;
	if (OP[1] != NULL)
		delete OP[1];
	OP[1] = NULL;
	delete I[0];
	delete I[1];
	delete CH[0];
	delete CH[1];
	delete STR[0];
	delete STR[1];
	I[0] = NULL;
	I[1] = NULL;
	CH[0] = NULL;
	CH[1] = NULL;
	STR[0] = NULL;
	STR[1] = NULL;
}

ordinal_pair::ordinal_pair(const ordinal_pair &op)
{
	type1 = op.type1;
	type2 = op.type2;
	I[0] = NULL;
	I[1] = NULL;
	CH[0] = NULL;
	CH[1] = NULL;
	STR[0] = NULL;
	STR[1] = NULL;
	SETT[0] = NULL;
	SETT[1] = NULL;
	OP[0] = NULL;
	OP[1] = NULL;

	switch (type1)
	{
	case Int:
		I[0] = new int;
		*I[0] = *op.I[0];
		break;
	case Char:
		CH[0] = new char;
		*CH[0] = *op.CH[0];
		break;
	case Str:
		STR[0] = new string;
		*STR[0] = *op.STR[0];
		break;
	case Set:
		SETT[0] = new SET;
		*SETT[0] = *op.SETT[0];
		break;
	case Ordinal_pair:
		OP[0] = new ordinal_pair;
		*OP[0] = *op.OP[0];
		break;
	case null:
		break;
	default:
		break;
	}
	switch (type2)
	{
	case Int:
		I[1] = new int;
		*I[1] = *op.I[1];
		break;
	case Char:
		CH[1] = new char;
		*CH[1] = *op.CH[1];
		break;
	case Str:
		STR[1] = new string;
		*STR[1] = *op.STR[1];
		break;
	case Set:
		SETT[1] = new SET;
		*SETT[1] = *op.SETT[1];
		break;
	case Ordinal_pair:
		OP[1] = new ordinal_pair;
		*OP[1] = *op.OP[1];
		break;
	case null:
		break;
	default:
		break;
	}
}

template <typename T1>
ordinal_pair::ordinal_pair(T1 t1, const char *chs)
{
	const type_info &SInfo = typeid(SET);
	const type_info &IInfo = typeid(int);
	const type_info &CInfo = typeid(char);
	const type_info &StrInfo = typeid(string);
	const type_info &OPInfo = typeid(ordinal_pair);
	const type_info &t1info = typeid(t1);
	T1 *tt1 = new T1;
	*tt1 = t1;
	SETT[0] = NULL;
	OP[0] = NULL;
	I[0] = NULL;
	CH[0] = NULL;
	STR[0] = NULL;
	SETT[1] = NULL;
	OP[1] = NULL;
	I[1] = NULL;
	CH[1] = NULL;

	if (t1info == IInfo)
	{
		type1 = Int;
		I[0] = (int *)tt1;
	}
	else if (t1info == CInfo)
	{
		type1 = Char;
		CH[0] = (char *)tt1;
	}
	else if (t1info == StrInfo)
	{
		type1 = Str;
		STR[0] = (string *)tt1;
	}
	else if (t1info == SInfo)
	{
		type1 = Set;
		SETT[0] = (SET *)tt1;
	}
	else if (t1info == OPInfo)
	{
		type1 = Ordinal_pair;
		OP[0] = (ordinal_pair *)tt1;
	}
	else
	{
		cout << "不支持的数据类型：" << t1info.name() << endl;
		type1 = null;
	}

	type2 = Str;
	STR[1] = new string;
	*STR[1] = chs;
}

template <typename T1, typename T2>
ordinal_pair::ordinal_pair(T1 t1, T2 t2)
{
	const type_info &SInfo = typeid(SET);
	const type_info &IInfo = typeid(int);
	const type_info &CInfo = typeid(char);
	const type_info &StrInfo = typeid(string);
	const type_info &OPInfo = typeid(ordinal_pair);
	const type_info &t1info = typeid(t1);
	const type_info &t2info = typeid(t2);
	T1 *tt1 = new T1;
	T2 *tt2 = new T2;

	*tt1 = t1;
	*tt2 = t2;
	SETT[0] = NULL;
	OP[0] = NULL;
	I[0] = NULL;
	CH[0] = NULL;
	STR[0] = NULL;
	SETT[1] = NULL;
	OP[1] = NULL;
	I[1] = NULL;
	CH[1] = NULL;
	STR[1] = NULL;

	if (t1info == IInfo)
	{
		type1 = Int;
		I[0] = (int *)tt1;
	}
	else if (t1info == CInfo)
	{
		type1 = Char;
		CH[0] = (char *)tt1;
	}
	else if (t1info == StrInfo)
	{
		type1 = Str;
		STR[0] = (string *)tt1;
	}
	else if (t1info == SInfo)
	{
		type1 = Set;
		SETT[0] = (SET *)tt1;
	}
	else if (t1info == OPInfo)
	{
		type1 = Ordinal_pair;
		OP[0] = (ordinal_pair *)tt1;
	}
	else
	{
		cout << "不支持的数据类型：" << t1info.name() << endl;
		type1 = null;
	}

	if (t2info == IInfo)
	{
		type2 = Int;
		I[1] = (int *)tt2;
	}
	else if (t2info == CInfo)
	{
		type2 = Char;
		CH[1] = (char *)tt2;
	}
	else if (t2info == StrInfo)
	{
		type2 = Str;
		STR[1] = (string *)tt2;
	}
	else if (t2info == SInfo)
	{
		type2 = Set;
		SETT[1] = (SET *)tt2;
	}
	else if (t2info == OPInfo)
	{
		type2 = Ordinal_pair;
		OP[1] = (ordinal_pair *)tt2;
	}
	else
	{
		cout << "不支持的数据类型：" << t2info.name() << endl;
		type2 = null;
	}
}

template <typename T2>
ordinal_pair::ordinal_pair(const char *chs, T2 t2)
{
	const type_info &SInfo = typeid(SET);
	const type_info &IInfo = typeid(int);
	const type_info &CInfo = typeid(char);
	const type_info &StrInfo = typeid(string);
	const type_info &OPInfo = typeid(ordinal_pair);
	const type_info &t2info = typeid(t2);
	T2 *tt2 = new T2;
	*tt2 = t2;
	SETT[0] = NULL;
	OP[0] = NULL;
	I[0] = NULL;
	CH[0] = NULL;
	SETT[1] = NULL;
	OP[1] = NULL;
	I[1] = NULL;
	CH[1] = NULL;
	STR[1] = NULL;

	type1 = Str;
	STR[0] = new string;
	*STR[0] = chs;

	if (t2info == IInfo)
	{
		type2 = Int;
		I[1] = (int *)tt2;
	}
	else if (t2info == CInfo)
	{
		type2 = Char;
		CH[1] = (char *)tt2;
	}
	else if (t2info == StrInfo)
	{
		type2 = Str;
		STR[1] = (string *)tt2;
		cout << STR[1] << endl;
		cout << *STR[1] << endl;
	}
	else if (t2info == SInfo)
	{
		type2 = Set;
		SETT[1] = (SET *)tt2;
	}
	else if (t2info == OPInfo)
	{
		type2 = Ordinal_pair;
		OP[1] = (ordinal_pair *)tt2;
	}
	else
	{
		cout << "不支持的数据类型：" << t2info.name() << endl;
		type2 = null;
	}
}

inline void ordinal_pair::component1(int t)
{
	type1 = Int;
	delete I[0];
	I[0] = new int;
	*I[0] = t;
}
inline void ordinal_pair::component1(char t)
{
	type1 = Char;
	delete CH[0];
	CH[0] = new char;
	*CH[0] = t;
}
inline void ordinal_pair::component1(string t)
{
	type1 = Str;
	delete STR[0];
	STR[0] = new string;
	*STR[0] = t;
}
inline void ordinal_pair::component1(SET t)
{
	type1 = Set;
	delete SETT[0];
	SETT[0] = new SET;
	*SETT[0] = t;
}
inline void ordinal_pair::component1(ordinal_pair t)
{
	type1 = Ordinal_pair;
	delete OP[0];
	OP[0] = new ordinal_pair;
	*OP[0] = t;
}

inline void ordinal_pair::component2(int t)
{
	type2 = Int;
	delete I[1];
	I[1] = new int;
	*I[1] = t;
}
inline void ordinal_pair::component2(char t)
{
	type2 = Char;
	delete CH[1];
	CH[1] = new char;
	*CH[1] = t;
}
inline void ordinal_pair::component2(string t)
{
	type2 = Str;
	delete STR[1];
	STR[1] = new string;
	*STR[1] = t;
}
inline void ordinal_pair::component2(SET t)
{
	type2 = Set;
	delete SETT[1];
	SETT[1] = new SET;
	*SETT[1] = t;
}
inline void ordinal_pair::component2(ordinal_pair t)
{
	type2 = Ordinal_pair;
	delete OP[1];
	OP[1] = new ordinal_pair;
	*OP[1] = t;
}

inline size_t ordinal_pair::OPHash() const
{
	size_t s = type1 * 10000 + type2 * 100000;
	switch (type1)
	{
	case Int:
		s += *I[0] * 200;
		break;
	case Char:
		s += *CH[0] * 400;
		break;
	case Str:
		s = (s + STR[0]->length() + STR[0]->at(0)) * 1000;
		break;
	case Set:
		s += SETT[0]->SETHash() / 1000;
		break;
	case Ordinal_pair:
		s += OP[0]->OPHash() / 200;
		break;
	case null:
		break;
	default:
		break;
	}
	switch (type2)
	{
	case Int:
		s += *I[1] * 100;
		break;
	case Char:
		s += *CH[1] * 300;
		break;
	case Str:
		s = (s + STR[1]->length() + STR[1]->at(0)) * 900;
		break;
	case Set:
		s += SETT[1]->SETHash() / 900;
		break;
	case Ordinal_pair:
		s += OP[1]->OPHash() / 100;
		break;
	case null:
		break;
	default:
		break;
	}
	return s;
}

bool ordinal_pair::operator==(const ordinal_pair &op)
{
	if (type1 == op.type1 && type2 == op.type2)
	{
		switch (type1)
		{
		case Int:
			if (*I[0] != *op.I[0])
				return false;
			break;
		case Char:
			if (*CH[0] != *op.CH[0])
				return false;
			break;
		case Str:
			if (*STR[0] != *op.STR[0])
				return false;
			break;
		case Set:
			if (!(*SETT[0] == *op.SETT[0]))
				return false;
			break;
		case Ordinal_pair:
			if (!(*OP[0] == *op.OP[0]))
				return false;
			break;
		case null:
			break;
		default:
			break;
		}
		switch (type2)
		{
		case Int:
			if (*I[1] != *op.I[1])
				return false;
			break;
		case Char:
			if (*CH[1] != *op.CH[1])
				return false;
			break;
		case Str:
			if (*STR[1] != *op.STR[1])
				return false;
			break;
		case Set:
			if (!(*SETT[1] == *op.SETT[1]))
				return false;
			break;
		case Ordinal_pair:
			if (!(*OP[1] == *op.OP[1]))
				return false;
			break;
		case null:
			break;
		default:
			break;
		}
		return true;
	}
	else
		return false;
}

ostream &operator<<(ostream &os, ordinal_pair &op)
{
	os << '<';
	switch (op.type1)
	{
	case Int:
		os << *op.I[0];
		break;
	case Char:
		os << '\'' << *op.CH[0] << '\'';
		break;
	case Str:
		os << '"' << *op.STR[0] << '"';
		break;
	case Set:
		os << *op.SETT[0];
		break;
	case Ordinal_pair:
		os << *op.OP[0];
		break;
	case null:
		os << "NULL";
		break;
	default:
		break;
	}
	os << ",";
	switch (op.type2)
	{
	case Int:
		os << *op.I[1];
		break;
	case Char:
		os << '\'' << *op.CH[1] << '\'';
		break;
	case Str:
		os << '"' << *op.STR[1] << '"';
		break;
	case Set:
		os << *op.SETT[1];
		break;
	case Ordinal_pair:
		os << *op.OP[1];
		break;
	case null:
		os << "NULL";
		break;
	default:
		break;
	}
	os << '>';
	return os;
	// TODO: 在此处插入 return 语句
}

/********************SET函数定义***********************/
SET::SET(const SET &S)
{
	Empty = S.Empty;
	IS = S.IS;
	CHS = S.CHS;
	STRS = S.STRS;
	SETS = S.SETS;
	OPS = S.OPS;
}

inline void SET::operator=(const SET &S)
{
	Empty = S.Empty;
	IS = S.IS;
	CHS = S.CHS;
	STRS = S.STRS;
	SETS = S.SETS;
	OPS = S.OPS;
}

bool SET::operator==(const SET &S)
{
	if (Empty == S.Empty && IS == S.IS && CHS == S.CHS && STRS == S.STRS)
		;
	{
		for (SET TSET : SETS)
			if (S.SETS.find(TSET) == S.SETS.end())
				return false;
		for (SET TSET : S.SETS)
			if (SETS.find(TSET) == SETS.end())
				return false;
		return true;
	}
}

SET SET::operator+(const SET &S)
{
	SET Temp = S;
	Temp.IS.insert(IS.begin(), IS.end());
	Temp.CHS.insert(CHS.begin(), CHS.end());
	Temp.STRS.insert(STRS.begin(), STRS.end());
	Temp.SETS.insert(SETS.begin(), SETS.end());
	Temp.OPS.insert(OPS.begin(), OPS.end());
	return Temp;
	// TODO: 在此处插入 return 语句
}

SET SET::operator&&(const SET &S)
{
	SET Temp;
	for (int i : IS)
		if (S.IS.find(i) != S.IS.end())
			Temp.push(i);

	for (char ch : CHS)
		if (S.CHS.find(ch) != S.CHS.end())
			Temp.push(ch);

	for (string str : STRS)
		if (S.STRS.find(str) != S.STRS.end())
			Temp.push(str);

	for (SET Set : SETS)
		if (S.SETS.find(Set) != S.SETS.end())
			Temp.push(Set);
	for (ordinal_pair op : OPS)
		if (S.OPS.find(op) != S.OPS.end())
			Temp.push(op);
	return Temp;
	// TODO: 在此处插入 return 语句
}

SET SET::operator-(const SET &S)
{
	SET Temp;
	for (int i : IS)
		if (S.IS.find(i) == S.IS.end())
			Temp.push(i);

	for (char ch : CHS)
		if (S.CHS.find(ch) == S.CHS.end())
			Temp.push(ch);

	for (string str : STRS)
		if (S.STRS.find(str) == S.STRS.end())
			Temp.push(str);

	for (SET Set : SETS)
		if (S.SETS.find(Set) == S.SETS.end())
			Temp.push(Set);
	for (ordinal_pair op : OPS)
		if (S.OPS.find(op) == S.OPS.end())
			Temp.push(op);
	return Temp;

	// TODO: 在此处插入 return 语句
}

SET Symmetrical_difference(const SET &S1, const SET &S2)
{
	SET Temp;
	for (int i : S1.IS)
		if (S2.IS.find(i) == S2.IS.end())
			Temp.push(i);

	for (char ch : S1.CHS)
		if (S2.CHS.find(ch) == S2.CHS.end())
			Temp.push(ch);

	for (string str : S1.STRS)
		if (S2.STRS.find(str) == S2.STRS.end())
			Temp.push(str);

	for (SET Set : S1.SETS)
		if (S2.SETS.find(Set) == S2.SETS.end())
			Temp.push(Set);
	for (ordinal_pair op : S1.OPS)
		if (S2.OPS.find(op) == S2.OPS.end())
			Temp.push(op);

	for (int i : S2.IS)
		if (S1.IS.find(i) == S1.IS.end())
			Temp.push(i);

	for (char ch : S2.CHS)
		if (S1.CHS.find(ch) == S1.CHS.end())
			Temp.push(ch);

	for (string str : S2.STRS)
		if (S1.STRS.find(str) == S1.STRS.end())
			Temp.push(str);

	for (SET Set : S2.SETS)
		if (S1.SETS.find(Set) == S1.SETS.end())
			Temp.push(Set);
	for (ordinal_pair op : S2.OPS)
		if (S1.OPS.find(op) == S1.OPS.end())
			Temp.push(op);
	return Temp;
	// TODO: 在此处插入 return 语句
}

SET SET::operator*(const SET &S)
{
	SET Stemp;
	for (int i1 : IS)
	{
		for (int i2 : S.IS)
		{
			ordinal_pair OPTemp(i1, i2);
			Stemp.push(OPTemp);
		}
		for (char ch2 : S.CHS)
		{
			ordinal_pair OPTemp(i1, ch2);
			;
			Stemp.push(OPTemp);
		}
		for (string str2 : S.STRS)
		{
			ordinal_pair OPTemp(i1, str2);
			Stemp.push(OPTemp);
		}
		for (SET SET2 : S.SETS)
		{
			ordinal_pair OPTemp(i1, SET2);
			Stemp.push(OPTemp);
		}
		for (ordinal_pair OP2 : S.OPS)
		{
			ordinal_pair OPTemp(i1, OP2);
			Stemp.push(OPTemp);
		}
	}
	for (char ch1 : CHS)
	{
		for (int i2 : S.IS)
		{
			ordinal_pair OPTemp(ch1, i2);
			Stemp.push(OPTemp);
		}
		for (char ch2 : S.CHS)
		{
			ordinal_pair OPTemp(ch1, ch2);
			Stemp.push(OPTemp);
		}
		for (string str2 : S.STRS)
		{
			ordinal_pair OPTemp(ch1, str2);
			Stemp.push(OPTemp);
		}
		for (SET SET2 : S.SETS)
		{
			ordinal_pair OPTemp(ch1, SET2);
			Stemp.push(OPTemp);
		}
		for (ordinal_pair OP2 : S.OPS)
		{
			ordinal_pair OPTemp(ch1, OP2);
			Stemp.push(OPTemp);
		}
	}
	for (string str1 : STRS)
	{
		for (int i2 : S.IS)
		{
			ordinal_pair OPTemp(str1, i2);
			Stemp.push(OPTemp);
		}
		for (char ch2 : S.CHS)
		{
			ordinal_pair OPTemp(str1, ch2);
			Stemp.push(OPTemp);
		}
		for (string str2 : S.STRS)
		{
			ordinal_pair OPTemp(str1, str2);
			Stemp.push(OPTemp);
		}
		for (SET SET2 : S.SETS)
		{
			ordinal_pair OPTemp(str1, SET2);
			Stemp.push(OPTemp);
		}
		for (ordinal_pair OP2 : S.OPS)
		{
			ordinal_pair OPTemp(str1, OP2);
			Stemp.push(OPTemp);
		}
	}
	for (SET SET1 : SETS)
	{
		for (int i2 : S.IS)
		{
			ordinal_pair OPTemp(SET1, i2);
			Stemp.push(OPTemp);
		}
		for (char ch2 : S.CHS)
		{
			ordinal_pair OPTemp(SET1, ch2);
			Stemp.push(OPTemp);
		}
		for (string str2 : S.STRS)
		{
			ordinal_pair OPTemp(SET1, str2);
			Stemp.push(OPTemp);
		}
		for (SET SET2 : S.SETS)
		{
			ordinal_pair OPTemp(SET1, SET2);
			Stemp.push(OPTemp);
		}
		for (ordinal_pair OP2 : S.OPS)
		{
			ordinal_pair OPTemp(SET1, OP2);
			Stemp.push(OPTemp);
		}
	}
	for (ordinal_pair op1 : OPS)
	{
		for (int i2 : S.IS)
		{
			ordinal_pair OPTemp(op1, i2);
			Stemp.push(OPTemp);
		}
		for (char ch2 : S.CHS)
		{
			ordinal_pair OPTemp(op1, ch2);
			Stemp.push(OPTemp);
		}
		for (string str2 : S.STRS)
		{
			ordinal_pair OPTemp(op1, str2);
			Stemp.push(OPTemp);
		}
		for (SET SET2 : S.SETS)
		{
			ordinal_pair OPTemp(op1, SET2);
			Stemp.push(OPTemp);
		}
		for (ordinal_pair OP2 : S.OPS)
		{
			ordinal_pair OPTemp(op1, OP2);
			Stemp.push(OPTemp);
		}
	}

	return Stemp;
	// TODO: 在此处插入 return 语句
}

void SET::power(int i, SET T, SET *Res)
{
	if (i == size())
	{
		Res->push(T);
		return;
	}
	else
	{
		power(i + 1, T, Res);
		int ii = i;
		if (ii < IS.size())
		{
			set<int>::iterator isi = IS.begin();
			for (int I = 0; I < ii; I++)
				isi++;
			T.push(*isi);
		}
		else
		{
			ii -= IS.size();
			if (ii < CHS.size())
			{
				set<char>::iterator chsi = CHS.begin();
				for (int I = 0; I < ii; I++)
					chsi++;
				T.push(*chsi);
			}
			else
			{
				ii -= CHS.size();
				if (ii < STRS.size())
				{
					set<string>::iterator strsi = STRS.begin();
					for (int I = 0; I < ii; I++)
						strsi++;
					T.push(*strsi);
				}
				else
				{
					i -= STRS.size();
					if (ii < SETS.size())
					{
						set<SET>::iterator setsi = SETS.begin();
						for (int I = 0; I < ii; I++)
							setsi++;
						T.push(*setsi);
					}
					else
					{
						ii -= SETS.size();
						if (ii < OPS.size())
						{
							set<ordinal_pair>::iterator opsi = OPS.begin();
							for (int I = 0; I < ii; I++)
								opsi++;
							T.push(*opsi);
						}
					}
				}
			}
		}
		power(i + 1, T, Res);
	}
}

inline SET SET::power()
{
	SET RES;
	power(0, SET(), &RES);
	return RES;
}

ostream &operator<<(ostream &os, SET &S)
{
	os << '{';
	for (int i : S.IS)
		os << i << ',';

	for (char ch : S.CHS)
		os << '\'' << ch << '\'' << ',';

	for (string str : S.STRS)
		os << '"' << str << '"' << ',';

	for (SET SET1 : S.SETS)
		os << SET1 << ',';

	for (ordinal_pair op : S.OPS)
		os << op << ',';

	if (S.Empty)
		cout << "Empty_set";
	else
		cout << "\b";
	cout << '}';

	return os;

	// TODO: 在此处插入 return 语句
}

inline istream &operator>>(istream &in, SET &S)
{
	int i;
	in >> i;
	types Ty = types(i);
	S.Empty = false;
	switch (Ty)
	{
	case Int:
		int i;
		while (in >> i)
			S.IS.insert(i);
		break;
	case Char:
		char ch;
		while (in >> ch)
			S.CHS.insert(ch);
		break;
	case Str:
	{
		string str;
		while (in >> str)
			S.STRS.insert(str);
		break;
	}
	case Set:
		break;
	case Ordinal_pair:
		break;
	case null:
		S.Empty = true;
		break;
	default:
		break;
	}
	return in;
	// TODO: 在此处插入 return 语句
}

inline size_t SET::size() const
{
	return IS.size() + CHS.size() + STRS.size() + SETS.size() + OPS.size();
}

size_t SET::SETHash() const
{
	size_t s = size() * 100000;
	set<int>::iterator isi = IS.begin();
	set<char>::iterator chsi = CHS.begin();
	set<string>::iterator strsi = STRS.begin();
	set<SET>::iterator setsi = SETS.begin();
	set<ordinal_pair>::iterator opsi = OPS.begin();
	for (int i = 1; i <= IS.size(); i++)
	{
		s += *isi * i * 100;
		isi++;
	}
	for (int i = 1; i <= CHS.size(); i++)
	{
		s += *chsi * i * 1000;
		chsi++;
	}
	for (int i = 1; i <= STRS.size(); i++)
	{
		s += (strsi->length() + strsi->at(0)) * i * 10000;
		isi++;
	}
	for (int i = 1; i <= SETS.size(); i++)
	{
		s += setsi->SETHash() / 5000 * i;
		setsi++;
	}
	for (int i = 1; i <= OPS.size(); i++)
	{
		s += opsi->OPHash() / 10000 * i;
		opsi++;
	}
	return s;
}