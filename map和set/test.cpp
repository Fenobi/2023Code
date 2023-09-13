#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

void test_set1()
{
	set<int> s;
	s.insert(2);
	s.insert(4);
	s.insert(1);
	s.insert(7);
	s.insert(1);
	s.insert(5);

	set<int>::iterator it = s.begin();

	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
}

void test_map1()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("ÅÅĞò", "sort"));
	dict.insert(pair<string, string>("×ó±ß", "left"));
	dict.insert(pair<string, string>("ÓÒ±ß", "right"));
	dict.insert(make_pair("×Ö·û´®", "string"));

	//map<string, string>::iterator it = dict.begin();
	auto it = dict.begin();
	while (it != dict.end())
	{
		//cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
	for (const auto& kv : dict)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}

void test_map2() 
{
	string arr[] = { "Æ»¹û","Î÷¹Ï","Ïã½¶","²İİ®","Æ»¹û","Î÷¹Ï","Æ»¹û","Æ»¹û","Î÷¹Ï","Æ»¹û","Ïã½¶","Æ»¹û","Ïã½¶" };
	map<string, int> countMap;

	//for (auto& e:arr)
	//{
	//	map<string, int>::iterator it = countMap.find(e);
	//	if (it == countMap.end())
	//	{
	//		countMap.insert(make_pair(e, 1));
	//	}
	//	else
	//	{
	//		it->second++;
	//	}
	//}


	for (auto& e : arr)
	{
		countMap[e]++;
	} 

	for (const auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}

void test_map3()
{
	//map<string, map<string,map<string,string>>> dict;
	//dict["1"]["2"]["3"] = "123";
	map<string, string> dict;
	dict["×Ö·û´®"] = "string";
	dict["²åÈë"] = "insert";
	dict["µü´úÆ÷"];
	dict["µü´úÆ÷"] = "iterator";

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	for (auto& e : dict)
	{
		cout << e.first << ":" << e.second << endl;
	}

}


int main()
{
	// test_set1();
	//test_map1();
	//test_map2();
	test_map3();
	return 0;
}