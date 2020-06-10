#pragma once
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class SET;											//SET类声明
class ordinal_pair;									//序偶类声明
class Date;

template<>
struct hash<Date>;

template<>
struct hash<SET>;

template<>
struct hash<ordinal_pair>;

ostream &operator<<(ostream &os, SET &S);			//SET类重载<<声明
ostream &operator<<(ostream &os, ordinal_pair &op); //序偶类重载<<声明
ostream &operator<<(ostream &os, Date &date);



enum types											//枚举类型定义声明
{
	Int,
	Char,
	Str,
	Set,
	Ordinal_pair,
	null
};

class Date
{
public:
	Date()
	{
		ty = null;
		SETT = NULL;
		OP = NULL;
	}
	Date(const Date &date);

	~Date();

	Date(const char *chs);
	Date(const int &t);
	Date(const char &t);
	Date(const string &t);
	Date(const SET &t);
	Date(const ordinal_pair &t);

	bool operator<(const Date &date) const;
	bool operator==(const Date &date);
	int operator%(const Date &date);

	void operator=(const char *t);
	void operator=(const int &t);
	void operator=(const char &t);
	void operator=(const string &t);
	void operator=(const SET &t);
	void operator=(const ordinal_pair &t);

	
	friend ostream &operator<<(ostream &os, Date &date);
	friend istream &operator>>(istream &is, Date &date);

	friend struct hash<Date>;
	friend struct hash<SET>;
	friend struct hash<ordinal_pair>;
	friend class Binary_relationship;

private:
	types ty;
	int I;
	char CH;
	string STR;
	SET *SETT;
	ordinal_pair *OP;

};

/************序偶完整声明**************/
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
	~ordinal_pair() 
	{
		date[0].~Date();
		date[1].~Date(); 
	};

	//折中解决const char** 无法强制转换成string*的bug
#if 0
	template <typename T2>
	ordinal_pair(const char *chs, T2 t2);

	template <typename T1>
	ordinal_pair(T1 t1, const char *chs);
#endif

	ordinal_pair(Date t1, Date t2)
	{
		date[0] = t1;
		date[1] = t2;
	}

	template <typename T1, typename T2>
	ordinal_pair(T1 t1, T2 t2);

	void operator=(const ordinal_pair &op);											   //重载赋值运算															   //析构函数
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

private:

	/********储存分量数据，允许int,char,string,SET和序偶类型作为分量*******/
	/*******************5月10日，全部数据用指针代替常量********************/
	/*******************6月6日，全部数据用一结构体封装*********************/
	Date date[2];

	friend class Binary_relationship;

	friend struct hash<Date>;

	friend struct hash<SET>;

	friend struct hash<ordinal_pair>;
	
};

/**************SET完整声明****************/
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

		Date &operator*() //重载*
		{
			int Pos = pos;
			set<Date>::iterator it = THIS->DATES.begin();
			while (Pos--)
			{
				++it;
			}

			/*if (Pos < THIS->IS.size())
			{
				set<int>::iterator iti = THIS->IS.begin();
				for (int i = 0; i < Pos; i++)
					iti++;
				SET *Temp = new SET;
				*Temp = {*iti};
				return *Temp;
			}
			Pos -= THIS->IS.size();
			if (Pos < THIS->CHS.size())
			{
				set<char>::iterator itch = THIS->CHS.begin();
				for (int i = 0; i < Pos; i++)
					itch++;
				SET *Temp = new SET;
				*Temp = {*itch};
				return *Temp;
			}
			Pos -= THIS->CHS.size();
			if (Pos < THIS->STRS.size())
			{
				set<string>::iterator itstr = THIS->STRS.begin();
				for (int i = 0; i < Pos; i++)
					itstr++;
				SET *Temp = new SET;
				*Temp = {*itstr};
				return *Temp;
			}
			Pos -= THIS->STRS.size();
			if (Pos < THIS->SETS.size())
			{
				set<SET>::iterator itset = THIS->SETS.begin();
				for (int i = 0; i < Pos; i++)
					itset++;
				SET *Temp = new SET;
				*Temp = {*itset};
				return *Temp;
			}
			Pos -= THIS->SETS.size();
			if (Pos < THIS->OPS.size())
			{
				set<ordinal_pair>::iterator itop = THIS->OPS.begin();
				for (int i = 0; i < Pos; i++)
					itop++;
				SET *Temp = new SET;
				*Temp = {*itop};
				return *Temp;
			}
			SET *Temp = new SET;*/

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
	inline void push(initializer_list<ordinal_pair> op)
	{
		for (ordinal_pair OP : op)
			DATES.insert(Date(OP));
		Empty = false;
	};

private:
	bool Empty; //是否包含空集

	/*储存元素数据，允许int,char,string,SET和序偶类型作为元素*/
	//set<int> IS;
	//set<char> CHS;
	//set<string> STRS;
	//set<SET> SETS;
	//set<ordinal_pair> OPS;

	set<Date> DATES;

	friend class Binary_relationship;

	friend struct hash<Date>;

	friend struct hash<SET>;

	friend struct hash<ordinal_pair>;
};

/****************hash完整声明****************/
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

/************************序偶函数定义****************************/

void ordinal_pair::operator=(const ordinal_pair &op)
{
	date[0] = op.date[0];
	date[1] = op.date[1];
}



//template <typename T1>
//ordinal_pair::ordinal_pair(T1 t1, const char *chs)
//{
//	const type_info &SInfo = typeid(SET);
//	const type_info &IInfo = typeid(int);
//	const type_info &CInfo = typeid(char);
//	const type_info &StrInfo = typeid(string);
//	const type_info &OPInfo = typeid(ordinal_pair);
//	const type_info &t1info = typeid(t1);
//	T1 *tt1 = new T1;
//	*tt1 = t1;
//
//	if (t1info == IInfo)
//	{
//		date[0].ty = Int;
//		date[0].I = (int *)tt1;
//	}
//	else if (t1info == CInfo)
//	{
//		date[0].ty = Char;
//		date[0].CH = (char *)tt1;
//	}
//	else if (t1info == StrInfo)
//	{
//		date[0].ty = Str;
//		date[0].STR = (string *)tt1;
//	}
//	else if (t1info == SInfo)
//	{
//		date[0].ty = Set;
//		date[0].SETT = (SET *)tt1;
//	}
//	else if (t1info == OPInfo)
//	{
//		date[0].ty = Ordinal_pair;
//		date[0].OP = (ordinal_pair *)tt1;
//	}
//	else
//	{
//		cout << "不支持的数据类型：" << t1info.name() << endl;
//		date[0].ty = null;
//	}
//
//	date[1].ty = Str;
//	date[1].STR = new string;
//	*date[1].STR = chs;
//}

template <typename T1, typename T2>
ordinal_pair::ordinal_pair(T1 t1, T2 t2)
{
	date[0] = t1;
	date[1] = t2;
}

//template <typename T2>
//ordinal_pair::ordinal_pair(const char *chs, T2 t2)
//{
//	const type_info &SInfo = typeid(SET);
//	const type_info &IInfo = typeid(int);
//	const type_info &CInfo = typeid(char);
//	const type_info &StrInfo = typeid(string);
//	const type_info &OPInfo = typeid(ordinal_pair);
//	const type_info &t2info = typeid(t2);
//	T2 *tt2 = new T2;
//	*tt2 = t2;
//	date[0].SETT = NULL;
//	date[0].OP = NULL;
//	date[0].I = NULL;
//	date[0].CH = NULL;
//	date[1].SETT = NULL;
//	date[1].OP = NULL;
//	date[1].I = NULL;
//	date[1].CH = NULL;
//	date[1].STR = NULL;
//
//	date[0].ty = Str;
//	date[0].STR = new string;
//	*date[0].STR = chs;
//
//	if (t2info == IInfo)
//	{
//		date[1].ty = Int;
//		date[1].I = (int *)tt2;
//	}
//	else if (t2info == CInfo)
//	{
//		date[1].ty = Char;
//		date[1].CH = (char *)tt2;
//	}
//	else if (t2info == StrInfo)
//	{
//		date[1].ty = Str;
//		date[1].STR = (string *)tt2;
//	}
//	else if (t2info == SInfo)
//	{
//		date[1].ty = Set;
//		date[1].SETT = (SET *)tt2;
//	}
//	else if (t2info == OPInfo)
//	{
//		date[1].ty = Ordinal_pair;
//		date[1].OP = (ordinal_pair *)tt2;
//	}
//	else
//	{
//		cout << "不支持的数据类型：" << t2info.name() << endl;
//		date[1].ty = null;
//	}
//}

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

//inline size_t ordinal_pair::OPHash() const
//{
//	size_t s = date[0].ty * 10000 + date[1].ty * 100000;
//	switch (date[0].ty)
//	{
//	case Int:
//		s += *date[0].I * 212;
//		break;
//	case Char:
//		s += *date[0].CH * 412;
//		break;
//	case Str:
//		s = (s + date[0].STR->length() + date[0].STR->at(0)) * 1000;
//		break;
//	case Set:
//		s += date[0].SETT->SETHash() / 1000;
//		break;
//	case Ordinal_pair:
//		s += date[0].OP->OPHash() / 200;
//		break;
//	case null:
//		break;
//	default:
//		break;
//	}
//	switch (date[1].ty)
//	{
//	case Int:
//		s += *date[1].I * 101;
//		break;
//	case Char:
//		s += *date[1].CH * 311;
//		break;
//	case Str:
//		s = (s + date[1].STR->length() + date[1].STR->at(0)) * 900;
//		break;
//	case Set:
//		s += date[1].SETT->SETHash() / 900;
//		break;
//	case Ordinal_pair:
//		s += date[1].OP->OPHash() / 100;
//		break;
//	case null:
//		break;
//	default:
//		break;
//	}
//	return s;
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


/********************SET函数定义***********************/
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

//size_t SET::SETHash() const
//{
//	size_t s = size() * 100000;
//	set<int>::iterator isi = IS.begin();
//	set<char>::iterator chsi = CHS.begin();
//	set<string>::iterator strsi = STRS.begin();
//	set<SET>::iterator setsi = SETS.begin();
//	set<ordinal_pair>::iterator opsi = OPS.begin();
//	for (int i = 1; i <= IS.size(); i++)
//	{
//		s += *isi * i * 100;
//		isi++;
//	}
//	for (int i = 1; i <= CHS.size(); i++)
//	{
//		s += *chsi * i * 1000;
//		chsi++;
//	}
//	for (int i = 1; i <= STRS.size(); i++)
//	{
//		s += (strsi->length() + strsi->at(0)) * i * 10000;
//		isi++;
//	}
//	for (int i = 1; i <= SETS.size(); i++)
//	{
//		s += setsi->SETHash() / 5000 * i;
//		setsi++;
//	}
//	for (int i = 1; i <= OPS.size(); i++)
//	{
//		s += opsi->OPHash() / 10000 * i;
//		opsi++;
//	}
//	return s;
//}



/*****************Date函数定义******************/


Date::Date(const char *chs)
{
	ty = Str;
	SETT = NULL;
	OP = NULL;
	STR = chs;
}
Date::Date(const int &t)
{
	ty = Int;
	I = t;
	SETT = NULL;
	OP = NULL;
}
Date::Date(const char &t)
{
	ty = Char;
	CH = t;
	SETT = NULL;
	OP = NULL;
}
Date::Date(const string &t)
{
	ty = Str;
	STR = t;
	SETT = NULL;
	OP = NULL;
}
Date::Date(const SET &t)
{
	ty = Set;
	SETT = new SET;
	*SETT = t;
	OP = NULL;
}
Date::Date(const ordinal_pair &t)
{
	ty = Ordinal_pair;
	SETT = NULL;
	OP = new ordinal_pair;
	*OP = t;
}

int Date::operator%(const Date &date)
{
	if (ty != Int || date.ty != Int)
		return -1;
	else
		return I % date.I;
}

void Date::operator=(const char *t)
{
	switch (ty)
	{
	case Set:
		if (SETT != NULL)
			delete SETT;
		SETT = NULL;
		break;
	case Ordinal_pair:
		if (OP != NULL)
			delete OP;
		OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	ty = Str;
	STR = t;
}
void Date::operator=(const int &t)
{
	switch (ty)
	{
	case Set:
		delete SETT;
		SETT = NULL;
		break;
	case Ordinal_pair:
		delete OP;
		OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	ty = Int;
	I = t;
}
void Date::operator=(const char &t)
{
	switch (ty)
	{
	case Set:
		delete SETT;
		SETT = NULL;
		break;
	case Ordinal_pair:
		delete OP;
		OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	ty = Char;
	CH = t;
}
void Date::operator=(const string &t)
{
	switch (ty)
	{
	case Set:
		delete SETT;
		SETT = NULL;
		break;
	case Ordinal_pair:
		delete OP;
		OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	ty = Str;
	STR = t;
}
void Date::operator=(const SET &t)
{
	switch (ty)
	{
	case Set:
		delete SETT;
		SETT = NULL;
		break;
	case Ordinal_pair:
		delete OP;
		OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	ty = Set;
	SETT = new SET;
	*SETT = t;
}
void Date::operator=(const ordinal_pair &t)
{
	switch (ty)
	{
	case Set:
		delete SETT;
		SETT = NULL;
		break;
	case Ordinal_pair:
		delete OP;
		OP = NULL;
		break;
	case null:
		break;
	default:
		break;
	}
	ty = Int;
	OP = new ordinal_pair;
	*OP = t;
}

ostream & operator<<(ostream & os, Date & date)
{
	switch (date.ty)
	{
	case Int:
		os << date.I;
		break;
	case Char:
		os << date.CH;
		break;
	case Str:
		os << date.STR;
		break;
	case Set:
		os << *date.SETT;
		break;
	case Ordinal_pair:
		os << *date.OP;
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
	int i;
	is >> i;
	switch (types(i))
	{
	case Int:
		date.ty = Int;
		is >> date.I;
		break;
	case Char:
		date.ty = Char;
		is >> date.CH;
		break;
	case Str:
		date.ty = Str;
		is >> date.STR;
		break;
	case null:
		date.ty = null;
		break;
	default:
		/*std::cout << "暂不支持的格式： " << types(i);*/
		date.ty = null;
		break;
	}
	return is;
	// TODO: 在此处插入 return 语句
}

Date::Date(const Date &date)
{
	ty = date.ty;
	SETT = NULL;
	OP = NULL;
	switch (ty)
	{
	case Int:
		I = date.I;
		break;
	case Char:
		CH = date.CH;
		break;
	case Str:
		STR = date.STR;
		break;
	case Set:
		SETT = new SET;
		*SETT = *date.SETT;
		break;
	case Ordinal_pair:
		OP = date.OP;
		break;
	case null:
		break;
	default:
		break;
	}
}

Date::~Date()
{

	switch (ty)
	{
	case Set:
		if(SETT!=NULL)
		{
			SETT = NULL;
		}
		break;
	case Ordinal_pair:
		if (OP != NULL)
		{
			OP = NULL;
		}
		break;
	case null:
		break;
	default:
		break;
	}
}

bool Date::operator==(const Date &date)
{
	if (ty == date.ty)
	{
		switch (ty)
		{
		case Int:
			return I == date.I;
			break;
		case Char:
			return CH == date.CH;
			break;
		case Str:
			return STR == date.STR;
			break;
		case Set:
			return *SETT == *date.SETT;
			break;
		case Ordinal_pair:
			return *OP == *date.OP;
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




size_t hash<Date>::operator()(const Date &date) const
{
	if (&date == NULL)
		return 0;
	size_t h1 = hash<types>()(date.ty);
	size_t h2;
	switch (date.ty)
	{
	case Int:
		h2 = date.I;
		break;
	case Char:
		h2 = date.CH;
		break;
	case Str:
		h2 = hash<string>()(date.STR);
		break;
	case Set:
		h2 = hash<SET>()(*date.SETT);
		break;
	case Ordinal_pair:
		h2 = hash<ordinal_pair>()(*date.OP);
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