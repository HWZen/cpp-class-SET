#pragma once
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
/***********类声明**************************************************************************************************************************/
class SET;											//SET类声明
class ordinal_pair;									//序偶类声明
class Date;
class MSET;

/***********hash结构体声明******************************************************************************************************************/
template<>
struct hash<Date>;

template<>
struct hash<SET>;

template<>
struct hash<MSET>;

template<>
struct hash<ordinal_pair>;

/***********输出流重载声明******************************************************************************************************************/
ostream &operator<<(ostream &os, SET &S);			//SET类重载<<声明
ostream &operator<<(ostream &os, MSET &S);			//MSET类重载<<声明
ostream &operator<<(ostream &os, ordinal_pair &op); //序偶类重载<<声明
ostream &operator<<(ostream &os, Date &date);		//Date类重载<<声明



enum types											//枚举类型定义声明
{
	Int,
	Char,
	Str,
	Set,
	MSet,
	Ordinal_pair,
	null
};


/************Date完整声明*******************************************************************************************************************/
class Date
{
public:
	Date()
	{
		_ty = null;
		_SETT = NULL;
		_MSETT = NULL;
		_OP = NULL;
	}
	Date(const Date &date);

	~Date();

	Date(const char *chs);
	Date(const int &t);
	Date(const char &t);
	Date(const string &t);
	Date(const SET &t);
	Date(const MSET &t);
	Date(const ordinal_pair &t);
	types ty() { return _ty; };
	int I() { return _I; };
	char CH() { return _CH; };
	string STR() { return _STR; };
	SET SETT();
	MSET MSETT();
	ordinal_pair OP();


	bool operator<(const Date &date) const;
	bool operator==(const Date &date);
	int operator%(const Date &date);

	void operator=(const char *t);
	void operator=(const int &t);
	void operator=(const char &t);
	void operator=(const string &t);
	void operator=(const SET &t);
	void operator=(const MSET &t);
	void operator=(const ordinal_pair &t);

	
	friend ostream &operator<<(ostream &os, Date &date);
	friend istream &operator>>(istream &is, Date &date);

	friend struct hash<Date>;
	friend struct hash<SET>;
	friend struct hash<ordinal_pair>;
	friend class Binary_relationship;

private:
	types _ty;
	int _I;
	char _CH;
	string _STR;
	SET *_SETT;
	MSET *_MSETT;
	ordinal_pair *_OP;

};

/************序偶完整声明*******************************************************************************************************************/
class ordinal_pair
{
public:
	/*************构造函数（5重载）****************/
	/**********5月10日，开始用模板代替重载*********/

	ordinal_pair() {};
	ordinal_pair(const ordinal_pair &op)
	{
		date[0] = op.date[0];
		date[1] = op.date[1];
	}
	~ordinal_pair() 															      //析构函数
	{
		date[0].~Date();
		date[1].~Date(); 
	}

	ordinal_pair(Date t1, Date t2)
	{
		date[0] = t1;
		date[1] = t2;
	}

	Date date1() { return date[0]; };
	Date date2() { return date[1]; };

	template <typename T1, typename T2>
	ordinal_pair(T1 t1, T2 t2);

	void operator=(const ordinal_pair &op);											   //重载赋值运算
	bool operator==(const ordinal_pair &O);											   //重载符号==
	bool operator<(const ordinal_pair &op) const; //重载符号<
	friend ostream &operator<<(ostream &os, ordinal_pair &op);						   //声明重载符号<<(友元)
	friend istream &operator>>(istream &in, ordinal_pair &op);						   //声明重载符号>>(友元)
	ordinal_pair anti();

	/**********第一、第二分量设置函数（5*2重载）************/
	//void component1(int t);
	//void component1(char t);
	//void component1(string t);
	//void component1(SET t);
	//void component1(ordinal_pair t);
	//void component2(int t);
	//void component2(char t);
	//void component2(string t);
	//void component2(SET t);
	//void component2(ordinal_pair t);

	//size_t OPHash() const; //序偶变量量化函数，用于不同序偶变量的比较

protected:

	/********储存分量数据，允许int,char,string,SET和序偶类型作为分量*******/
	/*******************5月10日，全部数据用指针代替常量********************/
	/*******************6月6日，全部数据用一结构体封装*********************/
	Date date[2];

	friend class Binary_relationship;

	friend struct hash<Date>;

	friend struct hash<SET>;

	friend struct hash<ordinal_pair>;
	
};

/**************SET完整声明******************************************************************************************************************/
class SET
{
public:
	/******************构造函数（7重载）*******************/
	SET() { Empty = true; };
	SET(const SET &S);
	SET(initializer_list<Date>date)
	{
		DATES.insert(date);
	};
	SET(initializer_list<int> I)
	{
		for (int i : I)
			DATES.insert(Date(i));
		Empty = false;
	};
	SET(initializer_list<char> ch)
	{
		for (char CH : ch)
			DATES.insert(Date(CH));
		Empty = false;
	};
	SET(initializer_list<string> str)
	{
		for (string STR : str)
			DATES.insert(Date(STR));
		Empty = false;
	};
	SET(initializer_list<ordinal_pair> op)
	{
		for (ordinal_pair OP : op)
			DATES.insert(Date(OP));
		Empty = false;
	};
	SET(initializer_list<SET> SETS)
	{
		for (SET sets : SETS)
			DATES.insert(Date(sets));
		Empty = false;
	};

	class iterator //迭代器
	{
	public:
		iterator(){};
		iterator(SET *i, int p) : THIS(i), pos(p) {}

		~iterator(){};

		bool operator!=(iterator it) //重载!=
		{
			return (this->pos != it.pos) || (!(*this->THIS == *it.THIS));
		}

		bool operator==(iterator it) //重载==
		{
			return (this->pos == it.pos) && (*this->THIS == *it.THIS);
		}

		iterator operator++() //重载++
		{
			pos++;
			return *this;
		}

		Date &operator*() //重载*
		{
			int Pos = pos;
			set<Date>::iterator it = THIS->DATES.begin();
			while (Pos--)
			{
				++it;
			}

			Date *temp = new Date;
			*temp = *it;
			return *temp;
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

	iterator find(const Date &S)
	{
		for (iterator it=begin();it!=end();++it)
			if (*it == S)
				return it;
		return end();
	}

	~SET(){}; //析构函数

	bool operator==(const SET &S);												   //重载==
	void operator=(const SET &S);												   //重载赋值运算
	inline bool operator<(const SET &S) const;									   //重载<
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
	//size_t SETHash() const;														   //SET变量量化函数，用于不同序偶变量的比较

	/*****************添加元素函数（5重载）*******************/
	inline void push(int I)
	{
		DATES.insert(Date(I));
		Empty = false;
	};
	inline void push(char ch)
	{
		DATES.insert(Date(ch));
		Empty = false;
	};
	inline void push(string str)
	{
		DATES.insert(Date(str));
		Empty = false;
	};
	inline void push(SET Set)
	{
		DATES.insert(Date(Set));
		Empty = false;
	};
	inline void push(MSET Set);
	inline void push(ordinal_pair op)
	{
		Date *temp = new Date(op);
		DATES.insert(*temp);
		Empty = false;
	};
	inline void push(const Date &date) 
	{
		DATES.insert(date);
		Empty = false; 
	};
	inline void push(initializer_list<int> I)
	{
		for (int i : I)
			DATES.insert(Date(i));
		Empty = false;
	};
	inline void push(initializer_list<char> ch)
	{
		for (char CH : ch)
			DATES.insert(Date(CH));
		Empty = false;
	};
	inline void push(initializer_list<string> str)
	{
		for (string STR : str)
			DATES.insert(Date(STR));
		Empty = false;
	};
	inline void push(initializer_list<SET> SETT)
	{
		for (SET T : SETT)
			DATES.insert(Date(T));
		Empty = false;
	};
	inline void push(initializer_list<MSET> SETT);
	inline void push(initializer_list<ordinal_pair> op)
	{
		for (ordinal_pair OP : op)
			DATES.insert(Date(OP));
		Empty = false;
	};

private:
	bool Empty; //是否包含空集

	/*储存元素数据，允许int,char,string,SET和序偶类型作为元素*/

	set<Date> DATES;

	friend class Binary_relationship;

	friend struct hash<Date>;
	friend struct hash<SET>;
	friend struct hash<MSET>;
	friend struct hash<ordinal_pair>;
};

/**************MSET完整声明*****************************************************************************************************************/
class MSET
{
public:
	MSET() { Empty = true; };
	MSET(const MSET &MS) { Empty = MS.Empty; DATES = MS.DATES; };
	MSET(initializer_list<Date>date)
	{
		DATES.insert(date);
	};
	MSET(initializer_list<int> I)
	{
		for (int i : I)
			DATES.insert(Date(i));
		Empty = false;
	};
	MSET(initializer_list<char> ch)
	{
		for (char CH : ch)
			DATES.insert(Date(CH));
		Empty = false;
	};
	MSET(initializer_list<string> str)
	{
		for (string STR : str)
			DATES.insert(Date(STR));
		Empty = false;
	};
	MSET(initializer_list<ordinal_pair> op)
	{
		for (ordinal_pair OP : op)
			DATES.insert(Date(OP));
		Empty = false;
	};
	MSET(initializer_list<SET> SETS)
	{
		for (SET sets : SETS)
			DATES.insert(Date(sets));
		Empty = false;
	};

	~MSET() {};

	/*****************添加元素函数（5重载）*******************/
	inline void push(int I)
	{
		DATES.insert(Date(I));
		Empty = false;
	};
	inline void push(char ch)
	{
		DATES.insert(Date(ch));
		Empty = false;
	};
	inline void push(string str)
	{
		DATES.insert(Date(str));
		Empty = false;
	};
	inline void push(SET Set)
	{
		DATES.insert(Date(Set));
		Empty = false;
	};
	inline void push(MSET Set)
	{
		DATES.insert(Date(Set));
		Empty = false;
	};
	inline void push(ordinal_pair op)
	{
		Date *temp = new Date(op);
		DATES.insert(*temp);
		Empty = false;
	};
	inline void push(const Date &date)
	{
		DATES.insert(date);
		Empty = false;
	};
	inline void push(initializer_list<int> I)
	{
		for (int i : I)
			DATES.insert(Date(i));
		Empty = false;
	};
	inline void push(initializer_list<char> ch)
	{
		for (char CH : ch)
			DATES.insert(Date(CH));
		Empty = false;
	};
	inline void push(initializer_list<string> str)
	{
		for (string STR : str)
			DATES.insert(Date(STR));
		Empty = false;
	};
	inline void push(initializer_list<SET> SETT)
	{
		for (SET T : SETT)
			DATES.insert(Date(T));
		Empty = false;
	};
	inline void push(initializer_list<MSET> SETT)
	{
		for (MSET T : SETT)
			DATES.insert(Date(T));
		Empty = false;
	};
	inline void push(initializer_list<ordinal_pair> op)
	{
		for (ordinal_pair OP : op)
			DATES.insert(Date(OP));
		Empty = false;
	};


	class iterator //迭代器
	{
	public:
		iterator() {};
		iterator(MSET *i, int p) : THIS(i), pos(p) {}

		~iterator() {};

		bool operator!=(iterator it) //重载!=
		{
			return (this->pos != it.pos) || !((*this->THIS == *it.THIS));
		}

		bool operator==(iterator it) //重载==
		{
			return (this->pos == it.pos) && (*this->THIS == *it.THIS);
		}

		iterator operator++() //重载++
		{
			pos++;
			return *this;
		}

		Date &operator*() //重载*
		{
			int Pos = pos;
			multiset<Date>::iterator it = THIS->DATES.begin();
			while (Pos--)
			{
				++it;
			}

			Date *temp = new Date;
			*temp = *it;
			return *temp;
		}

	private:
		MSET *THIS = nullptr;
		int pos = 0;
		int *I = nullptr;
		char *CH = nullptr;
		string *STR = nullptr;
		SET *SETT = nullptr;
		MSET *MSETT = nullptr;
		ordinal_pair *OP = nullptr;
	};
	iterator begin() { return iterator(this, 0); }		   //返回头部迭代器
	iterator end() { return iterator(this, (int)size()); } //返回尾部迭代器
	iterator find(const Date &S)
	{
		for (iterator it=begin();it!=end();++it)
			if (*it == S)
				return it;
		return end();
	}

	size_t size() { return DATES.size(); };

	bool operator==(const MSET &S);						   //重载==
	void operator=(const MSET &S);						   //重载赋值运算
	bool operator<(const MSET &S) const;				   //重载<

	friend ostream &operator<<(ostream &os, MSET &S);

	friend struct hash<Date>;
	friend struct hash<SET>;
	friend struct hash<MSET>;
	friend struct hash<ordinal_pair>;
private:
	multiset<Date> DATES;
	bool Empty;
};

/****************hash完整声明***************************************************************************************************************/
template<>
struct hash<Date>
{
public:
	size_t operator()(const Date &date) const;
};

template<>
struct hash<ordinal_pair>
{
public:
	size_t operator()(const ordinal_pair &op)const;
};

template<>
struct hash<SET>
{
public:
	size_t operator()(const SET &SETT)const;
};

template<>
struct hash<MSET>
{
public:
	size_t operator()(const MSET &SETT)const;
};

/************************序偶函数定义*******************************************************************************************************/

void ordinal_pair::operator=(const ordinal_pair &op)
{
	date[0] = op.date[0];
	date[1] = op.date[1];
}

template <typename T1, typename T2>
ordinal_pair::ordinal_pair(T1 t1, T2 t2)
{
	date[0] = t1;
	date[1] = t2;
}

//inline void ordinal_pair::component1(int t)
//{
//	date[0].ty = Int;
//	delete date[0].I;
//	date[0].I = new int;
//	*date[0].I = t;
//}
//inline void ordinal_pair::component1(char t)
//{
//	date[0].ty = Char;
//	delete date[0].CH;
//	date[0].CH = new char;
//	*date[0].CH = t;
//}
//inline void ordinal_pair::component1(string t)
//{
//	date[0].ty = Str;
//	delete date[0].STR;
//	date[0].STR = new string;
//	*date[0].STR = t;
//}
//inline void ordinal_pair::component1(SET t)
//{
//	date[0].ty = Set;
//	delete date[0].SETT;
//	date[0].SETT = new SET;
//	*date[0].SETT = t;
//}
//inline void ordinal_pair::component1(ordinal_pair t)
//{
//	date[0].ty = Ordinal_pair;
//	delete date[0].OP;
//	date[0].OP = new ordinal_pair;
//	*date[0].OP = t;
//}
//
//inline void ordinal_pair::component2(int t)
//{
//	date[1].ty = Int;
//	delete date[1].I;
//	date[1].I = new int;
//	*date[1].I = t;
//}
//inline void ordinal_pair::component2(char t)
//{
//	date[1].ty = Char;
//	delete date[1].CH;
//	date[1].CH = new char;
//	*date[1].CH = t;
//}
//inline void ordinal_pair::component2(string t)
//{
//	date[1].ty = Str;
//	delete date[1].STR;
//	date[1].STR = new string;
//	*date[1].STR = t;
//}
//inline void ordinal_pair::component2(SET t)
//{
//	date[1].ty = Set;
//	delete date[1].SETT;
//	date[1].SETT = new SET;
//	*date[1].SETT = t;
//}
//inline void ordinal_pair::component2(ordinal_pair t)
//{
//	date[1].ty = Ordinal_pair;
//	delete date[1].OP;
//	date[1].OP = new ordinal_pair;
//	*date[1].OP = t;
//}

bool ordinal_pair::operator==(const ordinal_pair &op)
{
	return date[0] == op.date[0] && date[1] == op.date[1];
}

bool ordinal_pair::operator<(const ordinal_pair &op) const
{
	return hash<ordinal_pair>()(*this) < hash<ordinal_pair>()(op);
}

ostream &operator<<(ostream &os, ordinal_pair &op)
{
	os << '<';
	os << op.date[0];
	os << ",";
	os << op.date[1];
	os << '>';
	return os;
	// TODO: 在此处插入 return 语句
}

inline istream &operator>>(istream &in, ordinal_pair &op)
{
	in >> op.date[0] >> op.date[1];
	return in;
	// TODO: 在此处插入 return 语句
}

ordinal_pair ordinal_pair::anti()
{
	ordinal_pair t;
	t.date[0] = date[1];
	t.date[1] = date[0];
	return t;
}


/********************SET函数定义**********************************************************************************************************/
SET::SET(const SET &S)
{
	Empty = S.Empty;
	DATES = S.DATES;
}

inline void SET::operator=(const SET &S)
{
	Empty = S.Empty;
	DATES = S.DATES;
}

bool SET::operator==(const SET &S)
{
	if (Empty == S.Empty && DATES.size()==S.DATES.size())
	{
		for (Date date : DATES)
			if (S.DATES.find(date) == S.DATES.end())
				return false;
		for (Date date : S.DATES)
			if (DATES.find(date) == DATES.end())
				return false;
		return true;
	}
	else
		return false;
}

SET SET::operator+(const SET &S)
{
	SET Temp = S;
	for (Date t : DATES)
		Temp.DATES.insert(t);
	return Temp;
	// TODO: 在此处插入 return 语句
}

SET SET::operator&&(const SET &S)
{
	SET Temp;
	for (Date date : DATES)
		if (S.DATES.find(date) != S.DATES.end())
			Temp.push(date);
	return Temp;
	// TODO: 在此处插入 return 语句
}

SET SET::operator-(const SET &S)
{
	SET Temp;
	for (Date date : DATES)
		if (S.DATES.find(date) == S.DATES.end())
			Temp.push(date);
	return Temp;

	// TODO: 在此处插入 return 语句
}

void SET::push(MSET Set)
{
	Date *temp = new Date(Set);
	DATES.insert(*temp);
	Empty = false;
};
inline void SET::push(initializer_list<MSET> SETT)
{
	for (MSET T : SETT)
		DATES.insert(Date(T));
	Empty = false;
};

SET Symmetrical_difference(const SET &S1, const SET &S2)
{
	SET Temp;
	for (Date date : S1.DATES)
		if (S2.DATES.find(date) == S2.DATES.end())
			Temp.push(date);

	for (Date date : S2.DATES)
		if (S1.DATES.find(date) == S1.DATES.end())
			Temp.push(date);

	return Temp;
	// TODO: 在此处插入 return 语句
}

SET SET::operator*(const SET &S)
{
	SET Stemp;
	for (Date date1 : DATES)
	{
		for (Date date2 : S.DATES)
		{
			ordinal_pair OPTemp(date1, date2);
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
		set<Date>::iterator it = DATES.begin();
		for (int I = 0; I < i; I++)
			++it;
		T.push(*it);
		int ii = i;
		//if (ii < IS.size())
		//{
		//	set<int>::iterator isi = IS.begin();
		//	for (int I = 0; I < ii; I++)
		//		isi++;
		//	T.push(*isi);
		//}
		//else
		//{
		//	ii -= IS.size();
		//	if (ii < CHS.size())
		//	{
		//		set<char>::iterator chsi = CHS.begin();
		//		for (int I = 0; I < ii; I++)
		//			chsi++;
		//		T.push(*chsi);
		//	}
		//	else
		//	{
		//		ii -= CHS.size();
		//		if (ii < STRS.size())
		//		{
		//			set<string>::iterator strsi = STRS.begin();
		//			for (int I = 0; I < ii; I++)
		//				strsi++;
		//			T.push(*strsi);
		//		}
		//		else
		//		{
		//			i -= STRS.size();
		//			if (ii < SETS.size())
		//			{
		//				set<SET>::iterator setsi = SETS.begin();
		//				for (int I = 0; I < ii; I++)
		//					setsi++;
		//				T.push(*setsi);
		//			}
		//			else
		//			{
		//				ii -= SETS.size();
		//				if (ii < OPS.size())
		//				{
		//					set<ordinal_pair>::iterator opsi = OPS.begin();
		//					for (int I = 0; I < ii; I++)
		//						opsi++;
		//					T.push(*opsi);
		//				}
		//			}
		//		}
		//	}
		//}
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
	for (Date date : S.DATES)
		os << date << ',';

	if (S.Empty)
		os << "Empty_set";
	else
		os << "\b";
	os << '}';

	return os;

	// TODO: 在此处插入 return 语句
}

inline istream &operator>>(istream &in, SET &S)
{
	
	S.Empty = false;
	Date temp;
	while (in >> temp)
		S.DATES.insert(temp);
	return in;
	// TODO: 在此处插入 return 语句
}

inline size_t SET::size() const
{
	return DATES.size();
}

inline bool SET::operator<(const SET &S) const
{ 
	return hash<SET>()(*this) < hash<SET>()(S); 
}

/*****************MSET函数定义***************************************************************************************************************/

bool MSET::operator==(const MSET & S)
{
	if (Empty == S.Empty && DATES.size() == S.DATES.size())
	{
		for (Date date : DATES)
			if (S.DATES.find(date) == S.DATES.end())
				return false;
		for (Date date : S.DATES)
			if (DATES.find(date) == DATES.end())
				return false;
		return true;
	}
	else
		return false;
}

inline void MSET::operator=(const MSET &S)
{
	Empty = S.Empty;
	DATES = S.DATES;
}

inline bool MSET::operator<(const MSET & S) const
{
	return hash<MSET>()(*this) < hash<MSET>()(S);
}

inline ostream & operator<<(ostream & os, MSET & S)
{
	os << '{';
	for (Date d : S.DATES)
		os << d << ',';
	if(S.Empty)
		os << "Empty_set";
	os << "\b" << '}';
	return os;
	// TODO: 在此处插入 return 语句
}

/*****************Date函数定义****************************************************************************************************************/


Date::Date(const char *chs)
{
	_ty = Str;
	_SETT = NULL;
	_MSETT = NULL;
	_OP = NULL;
	_STR = chs;
}
Date::Date(const int &t)
{
	_ty = Int;
	_I = t;
	_SETT = NULL;
	_MSETT = NULL;
	_OP = NULL;
}
Date::Date(const char &t)
{
	_ty = Char;
	_CH = t;
	_SETT = NULL;
	_MSETT = NULL;
	_OP = NULL;
}
Date::Date(const string &t)
{
	_ty = Str;
	_STR = t;
	_SETT = NULL;
	_MSETT = NULL;
	_OP = NULL;
}
Date::Date(const SET &t)
{
	_ty = Set;
	_SETT = new SET;
	*_SETT = t;
	_MSETT = NULL;
	_OP = NULL;
}
Date::Date(const MSET &t)
{
	_ty = MSet;
	_SETT = NULL;
	_MSETT = new MSET;
	*_MSETT = t;
	_OP = NULL;
}
Date::Date(const ordinal_pair &t)
{
	_ty = Ordinal_pair;
	_SETT = NULL;
	_MSETT = NULL;
	_OP = new ordinal_pair;
	*_OP = t;
}

inline SET Date::SETT()
{
	return *_SETT;
}
inline ordinal_pair Date::OP()
{
	return *_OP;
}
inline MSET Date::MSETT()
{
	return *_MSETT;
}

int Date::operator%(const Date &date)
{
	if (_ty != Int || date._ty != Int)
		return -1;
	else
		return _I % date._I;
}

void Date::operator=(const char *t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = Str;
	_STR = t;
}
void Date::operator=(const int &t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = Int;
	_I = t;
}
void Date::operator=(const char &t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = Char;
	_CH = t;
}
void Date::operator=(const string &t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = Str;
	_STR = t;
}
void Date::operator=(const SET &t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = Set;
	_SETT = new SET;
	*_SETT = t;
}
void Date::operator=(const MSET & t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = MSet;
	_MSETT = new MSET;
	*_MSETT = t;
}
void Date::operator=(const ordinal_pair &t)
{
	switch (_ty)
	{
	case Set:
		if (_SETT != NULL)
			delete _SETT;
		_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			delete _MSETT;
		_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			delete _OP;
		_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	_ty = Int;
	_OP = new ordinal_pair;
	*_OP = t;
}

ostream & operator<<(ostream & os, Date & date)
{
	switch (date._ty)
	{
	case Int:
		os << date._I;
		break;
	case Char:
		os << date._CH;
		break;
	case Str:
		os << date._STR;
		break;
	case Set:
		os << *date._SETT;
		break;
	case MSet:
		os << *date._MSETT;
		break;
	case Ordinal_pair:
		os << *date._OP;
		break;
	case null:
		os << "null";
	default:
		break;
	}
	return os;
	// TODO: 在此处插入 return 语句
}

inline istream & operator>>(istream & is, Date & date)
{
	switch (date._ty)
	{
	case Set:
		if (date._SETT != NULL)
			delete date._SETT;
		date._SETT = NULL;
		break;
	case MSet:
		if (date._MSETT != NULL)
			delete date._MSETT;
		date._MSETT = NULL;
		break;
	case Ordinal_pair:
		if (date._OP != NULL)
			delete date._OP;
		date._OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	int i;
	is >> i;
	switch (types(i))
	{
	case Int:
		date._ty = Int;
		is >> date._I;
		break;
	case Char:
		date._ty = Char;
		is >> date._CH;
		break;
	case Str:
		date._ty = Str;
		is >> date._STR;
		break;
	case null:
		date._ty = null;
		break;
	default:
		/*std::cout << "暂不支持的格式： " << _types(i);*/
		date._ty = null;
		break;
	}
	return is;
	// TODO: 在此处插入 return 语句
}

Date::Date(const Date &date)
{
	_ty = date._ty;
	_SETT = NULL;
	_MSETT = NULL;
	_OP = NULL;
	switch (_ty)
	{
	case Int:
		_I = date._I;
		break;
	case Char:
		_CH = date._CH;
		break;
	case Str:
		_STR = date._STR;
		break;
	case Set:
		_SETT = new SET;
		*_SETT = *date._SETT;
		break;
	case MSet:
		_MSETT = new MSET;
		*_MSETT = *date._MSETT;
		break;
	case Ordinal_pair:
		_OP = date._OP;
		break;
	case null:
		break;
	default:
		break;
	}
}

Date::~Date()
{

	switch (_ty)
	{
	case Set:
		if(_SETT!=NULL)
			_SETT = NULL;
		break;
	case MSet:
		if (_MSETT != NULL)
			_MSETT = NULL;
		break;
	case Ordinal_pair:
		if (_OP != NULL)
			_OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
}

bool Date::operator==(const Date &date)
{
	if (_ty == date._ty)
	{
		switch (_ty)
		{
		case Int:
			return _I == date._I;
			break;
		case Char:
			return _CH == date._CH;
			break;
		case Str:
			return _STR == date._STR;
			break;
		case Set:
			return *_SETT == *date._SETT;
			break;
		case MSet:
			return *_MSETT == *date._MSETT;
			break;
		case Ordinal_pair:
			return *_OP == *date._OP;
			break;
		case null:
			return true;
			break;
		default:
			break;
		}
	}
	else
		return false;
}

bool Date::operator<(const Date &date) const
{
	return hash<Date>()(*this) < hash<Date>()(date);
}


/***************hash函数定义*******************************************************************************************************************/

size_t hash<Date>::operator()(const Date &date) const
{
	if (&date == NULL)
		return 0;
	size_t h1 = hash<types>()(date._ty);
	size_t h2;
	switch (date._ty)
	{
	case Int:
		h2 = date._I;
		break;
	case Char:
		h2 = date._CH;
		break;
	case Str:
		h2 = hash<string>()(date._STR);
		break;
	case Set:
		h2 = hash<SET>()(*date._SETT);
		break;
	case Ordinal_pair:
		h2 = hash<ordinal_pair>()(*date._OP);
		break;
	case null:
		h2 = 100;
	default:
		break;
	}
	return h2 ^ (h1 << 2);
}

size_t hash<ordinal_pair>::operator()(const ordinal_pair &op)const
{
	if (&op == NULL)
		return 0;
	size_t h1 = hash<Date>()(op.date[0]);
	size_t h2 = hash<Date>()(op.date[1]);
	return h1 ^ (h2 << 2);
}

size_t hash<SET>::operator()(const SET &SETT)const
{
	if (SETT.DATES.size() == 0)
		return 1;
	size_t h = hash<Date>()(*SETT.DATES.begin());
	for (Date t : SETT.DATES)
		h = hash<size_t>()(h ^ (hash<Date>()(t) << 2));
	h += SETT.Empty;
	return h;
}

inline size_t hash<MSET>::operator()(const MSET & SETT) const
{
	if (SETT.DATES.size() == 0)
		return 1;
	size_t h = hash<Date>()(*SETT.DATES.begin());
	for (Date t : SETT.DATES)
		h = hash<size_t>()(h ^ (hash<Date>()(t) << 2));
	h += SETT.Empty;
	return h;
	return size_t();
}
