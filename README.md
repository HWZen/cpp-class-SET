cpp-class-SET
=============
### A class named SET can storage of data mixed<br>
#### Now this project is going to expand to the entire discrete
* 包含四个个类：'SET'（集合）、'ordinal_pair'（序偶）、`Date`（储存数据）、`MSET`（多重集）<br>
* 项目已有的扩展：二元关系、图<br>
* 支持的数据类型：`int`,`char`,`string`,`SET`,`MSET`,`ordinal_pair`<br>
* `Date`支持不同类型数据混合储存<br>
* `SET`支持的运算：交（`&&`）、并（`+`）、差（`-`）、对称差（`Symmetrical_difference(SET 1,SET2)`）、幂集（`SET.power()`）、笛卡尔积（`*` ）<br>
* 支持输出流`<<`操作，可直接将结果用`cout`输出<br>

>Contains two categories: SET (set), ordinal_pair (order couple)<br>
>Supported data types: int, char, string, SET, MSET,ordinal_pair<br>
>Date Support mixed storage of different types of data<br>
>SET Supported operations: intersection (&&), union (+), difference (-), symmetric difference (Symmetrical_difference (SET 1, SET2)), power set (SET.power ()), Cartesian product (* )<br>
>Support output stream << operation, you can directly output the result with cout<br>

下面列出SET示例代码
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
* 使用纯正hash运算，数据识别更精确

## 6月13日
### 图类基础功能完成
> 在B站朋友：第0奇异点【[他的github](https://github.com/Binary-Song)】的建议下，我决定用邻接矩阵来作为图的数据结构，确实是简洁明了了很多。
> 甚至他还帮我写了一份Matrix矩阵类和Graph图类。真的是万分感谢！

### 截至6月13日图类完成的功能有：
* `static Graphs G(size_t v, MSET S2);`							//构建并返回无向图
* `static Graphs E(size_t v, MSET S2);`							//构建并返回有向图
* `size_t V_size() { return V_num; };`							//顶点数量(n阶图)
* `size_t E_size();`											//边数量
* `bool EG_empty();`											//判断零图
* `bool Figure_empty() { return V_num == 0; };`					//判断空图
* `static unsigned int Associations(Date d, MSET S);`			//关联次数
* `bool V_Adjacent(size_t d1, size_t d2);`						//判断顶点是否相邻
* `static bool E_Adjacent(MSET S1, MSET S2);`					//判断无向边是否相邻
* `static bool E_Adjacent(ordinal_pair op1, ordinal_pair op2);` //判断有向图是否相邻
* `unsigned int link_branch();`									//连通分量
* `void print();`												//打印邻接矩阵

> 更新后记
这次更新其实工程量比想象的大。
一开始我是边看PPT边写图的，以至于我以为图和二元关系一样，是在集合基础上的扩展。
于是在数据上我继承了集合SET的多样性，还在SET.h里添加了一个MSET多重集类。
结果遇到了很多麻烦，尤其为了添加了MSET，基本整个SET.h都改了，还是疯狂StackOverFlow。
当然，这些麻烦并非不可解决，但这真的非常麻烦。
后来在B站网友的点提下，我意识到在图的概念里，对数据的多样性并没有什么需求。没有需求说要为顶点起个优雅的名字，储存边也没有必要给SET套娃套好几层（两层足矣）
于是我决定重构快完成的代码，顶点全部用int，边用MSET传进来后马上转换成邻接矩阵。（以后肯定会支持直接用邻接矩阵构造）
在决定这样做以后，我只用一个晚上就实现了图的基本概念。实属便捷
我从中获得的教训：
>> 代码要追求简洁而不是功能强大，越简洁的代码约稳定，越复杂的代码越难维护，尤其是项目只有你一个人在写的时候
如果写出了复杂而功能强大的代码，不要留恋。将它放在头文件里，需要的时候调用就好，不要想着再为它添砖加瓦，工程量巨大。

> 最后，再次感谢第0奇异点，感谢他提点我用邻接矩阵，感谢他为我写了一份矩阵类和图类，感谢他教会我用void类型的指针！

[My blog](https://hwzen.myds.me:17001 "变态文春の又一个博客")
