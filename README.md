cpp-class-SET
=============
### A class named SET can storage of data mixed<br>
* 包含两个类：'SET'（集合）、'ordinal_pair'（序偶）<br>
* 支持的数据类型：`int`,`char`,`string`,`SET`,ordinal_pair`<br>
* 支持不同类型数据混合储存<br>
* 支持的运算：交（`&&`）、并（`+`）、差（`-`）、对称差（`Symmetrical_difference(SET 1,SET2)`）、幂集（`SET.power()`）、笛卡尔积（`*` ）<br>
* 支持输出流`<<`操作，可直接将结果用`cout`输出<br>

>Contains two categories: SET (set), ordinal_pair (order couple)<br>
>Supported data types: int, char, string, SET, ordinal_pair<br>
>Support mixed storage of different types of data<br>
>Supported operations: intersection (&&), union (+), difference (-), symmetric difference (Symmetrical_difference (SET 1, SET2)), power set (SET.power ()), Cartesian product (* )<br>
>Support output stream << operation, you can directly output the result with cout<br>

下面列出示例代码
```C++
    SET SET0 = {};//定义一个空集集合
    //{Empty_set}

    SET SET1({ 1,2,3,4});//定义一个集合，里面有几个常数
    //{1,2,3,4}

    SET SET2 = { 'H','e','l','l','o',',','w','o','r','l','d' };//定义一个集合，里面有几个字符
    //{',','H','d','e','l','o','r','w'}                        //不会储存重复的字符

    ordinal_pair op1 = { 25, "Hello,world!" };//定义一个序偶
    //<25,"Hello,world!">

    SET SET3 = { 1,3,5,7 };//定义一个集合，里面有几个常数
	SET3.push({ 'H', 'l' });//添加两个字符
    SET3.push(op1);//定义一个序偶
	SET3.push(SET1);//定义一个集合（重点：作为元素，而非拷贝或者重合什么的）
    //{1,3,5,7,'H','l',{1,2,3,4},<25,"Hello,world!">}          //可以各种数据混合存储

    SET SET4 = SET1 - SET3;//定义一个集合，储存了SET1 - SET3的结果
    //{2,4}

    SET SET5 = SET1 + SET3;//定义一个集合，储存了SET1 + SET3的结果
    //{1,2,3,4,5,7,'H','l',{1,2,3,4},<25,"Hello,world!">}

    SET SET6 = SET1 && SET3;//定义一个集合，储存了SET1 && SET3的结果
    //{1,3}

    SET SET7 = Symmetrical_difference(SET1, SET3);//定义一个集合，储存了Symmetrical_difference(SET1, SET3)的结果
    //{2,4,5,7,'H','l',{1,2,3,4},<25,"Hello,world!">}

    SET SET8 = SET4.power();//定义一个集合，储存了SET4.power()的结果
    //{{Empty_set},{2},{4},{2,4}}

    SET SET9 = SET5 * SET6;//定义一个集合，储存了SET5 * SET6的结果
    //{<1,1>,<1,3>,<2,3>,<3,3>,<4,3>,<5,3>,<7,1>,<7,3>,<{1,2,3,4},1>,<{1,2,3,4},3>,<'H',1>,<'H',3>,<'l',1>,<'l',3>,<<25,"Hello,world!">,1>,<<25,"Hello,world!">,3>}

    cout << SET0 << endl << SET1 << endl << SET2 << endl << op1 << endl << SET3 << endl << SET4 << endl << SET5 << endl << SET6 << endl << SET7 << endl << SET8 << endl << SET9 << endl;//直接将各集合数据输出到流
    // {Empty_set}
    // {1,2,3,4}
    // {',','H','d','e','l','o','r','w'}
    // {1,3,5,7,'H','l',{1,2,3,4},<25,"Hello,world!">}
    // {2,4}
    // {1,2,3,4,5,7,'H','l',{1,2,3,4},<25,"Hello,world!">}
    // {1,3}
    // {2,4,5,7,'H','l',{1,2,3,4},<25,"Hello,world!">}
    // {{Empty_set},{2},{4},{2,4}}
    // {<1,1>,<1,3>,<2,3>,<3,3>,<4,3>,<5,3>,<7,1>,<7,3>,<{1,2,3,4},1>,<{1,2,3,4},3>,<'H',1>,<'H',3>,<'l',1>,<'l',3>,<<25,"Hello,world!">,1>,<<25,"Hello,world!">,3>}
```


>项目源自离散作业<br>

## 5月10日更新
### ordinal_pair（序偶）类更新
* 开始用模板代替重载。
* 全部数据用指针代替常量。

## 5月11日更新
### SET（集合）类补BUG、更新示例文件
* 修复有参构造函数Empty依然为true
* 示例文件重命名
* 示例文件更新

## 5月16日更新
### SET（集合）添加迭代器
* 对迭代器取址返回一个SET集合，集合包含迭代器当前所指向的元素，
* 可用`for(SET T:(SET)S)`进行单个元素遍历

使用示例代码：
```c++
SET::iterator its = SET5.begin();//定义迭代器
++its;
cout << *its << endl;
for (SET T : SET5)//使用迭代器遍历
cout << T << " ";
```

## 5月19日更新
### SET（集合）添加>>重载，可以使用cin向SET添加数据、simple更新
* 先读入一个整数，表示输入类型：`int:0 char:1 string:3 Empty:5`，然后读取接下来的数据直到遇到`EOF`
* 应老师要求，sample更新从文件读入数据。

使用实列代码
```c++
SET SET1;
cin>>SET1;

ifstream input("input.txt");
SET SET1;
if (input)
{
input >> SET1;
cout << "SET1:" << SET1 << endl;
}
else
cout << "input open failed" << endl;
input.close()

```

## 5月31日
### 新建二元关系`Binary_relationship`分支，实现二元关系的各州概念
* 项目进展请查看[二元关系.md](二元关系.md)


# 6月5日到6月10日
## 新建分支Refactoring用于代码重构
### 重构内容：数据储存方式、使用真·hash对数据进行量化
* 新建类`Date`，封装`int`,`char`,`string`,`class SET`,`class ordinal_pair`五种数据类型。
* 减少指针的使用，防止出错。
* 数据的构造、析构转移给`Date`，减少其他类的代码量。
* 使用纯真hash运算，数据识别更精确


[My blog](https://hwzen.myds.me:17001 "变态文春の又一个博客")
