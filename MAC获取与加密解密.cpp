// MAC获取与加密解密.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<string>
#include <WinSock2.h>
#include <Iphlpapi.h>
using namespace std;
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库

/*构造两个参数，一个是BYTE数组，一个是BYTE数组对应的长度，目的是方便后续的for循环进行遍历而不用再此判断。*/
/*Thanks for https://blog.csdn.net/superna666/article/details/52809007/ */
string * byteToHexStr(unsigned char byte_arr[], int arr_len)

{

	string* hexstr = new string();

	for (int i = 0; i < arr_len; i++)
	{

		char hex1;

		char hex2;

		/*借助C++支持的unsigned和int的强制转换，把unsigned char赋值给int的值，那么系统就会自动完成强制转换*/

		int value = byte_arr[i];

		int S = value / 16;

		int Y = value % 16;

		//将C++中unsigned char和int的强制转换得到的商转成字母

		if (S >= 0 && S <= 9)

			hex1 = (char)(48 + S);

		else

			hex1 = (char)(55 + S);

		//将C++中unsigned char和int的强制转换得到的余数转成字母

		if (Y >= 0 && Y <= 9)

			hex2 = (char)(48 + Y);

		else

			hex2 = (char)(55 + Y);

		//最后一步的代码实现，将所得到的两个字母连接成字符串达到目的

		*hexstr = *hexstr + hex1 + hex2;

	}

	return hexstr;

}

string * getMAC()
{
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();

	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);

	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);

	//记录网卡数量
	int netCardNum = 0;
	//记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;

	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}

	return byteToHexStr(pIpAdapterInfo->Address, pIpAdapterInfo->AddressLength);
}

string encrypt(string str)	/*加密*/
{
	string out;
	string temp;
	int i;
	for (i = 0; i < str.size(); i++)
	{
		temp = str[i] + i + 5;
		out += temp;

	}

	return out;
}

string Decrypt(string str)
{
	string out;
	string temp;
	int i;
	for (i = 0; i < str.size(); i++)
	{
		temp = str[i] - i - 5;
		out += temp;
	}
	return out;

}

int main()
{
	string MAC;
	cout << "本机MAC地址：" << *getMAC() << endl;
	cout << "MAC地址加密：" << encrypt(*getMAC()) << endl;
	cout << "MAC地址加密后解密：" << Decrypt(encrypt(*getMAC())) << endl;
	cout << "输入其它MAC地址：" << endl;
	cin >> MAC;
	cout << "其它MAC地址加密：" << encrypt(MAC) << endl;
	cout << "输入加密后的地址：" << endl;
	cin >> MAC;
	cout << "解密地址：" << Decrypt(MAC) << endl;



	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
