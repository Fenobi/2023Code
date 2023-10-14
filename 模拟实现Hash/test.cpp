#include "HashTable.hpp"
#include "UnorderedMap.hpp"
#include "UnorderedSet.hpp"

void test1()
{
	std::string arr[] = { "Æ»¹û","Ïã½¶","Àæ×Ó","Ïã½¶","Àæ×Ó","Æ»¹û","Ïã½¶","Ïã½¶","Àæ×Ó","Ïã½¶" };
	std::unordered_map<std::string, int> um;
	for (auto& e : arr)
	{
		um[e]++;
	}
	std::unordered_map<std::string, int>::iterator it = um.begin();
	while (it != um.end())
	{
		std::cout << it->first << ":" << it->second << std::endl;
		++it;
	}
}

void test2()
{
	const long long N = 100000;
	std::unordered_set<int> us;
	std::set<int> s;

	std::vector<int> v;
	v.reserve(N);
	srand((unsigned int)time(0));
	for (int i = 0; i < N; ++i)
	{
		v.push_back(i);
	}

	size_t begin1 = clock();
	for (auto e : v)
	{
		us.insert(e);
	}
	size_t end1 = clock();
	std::cout << "unordered_set insert : " << end1 - begin1 << std::endl;


	size_t begin2 = clock();
	for (auto e : v)
	{
		s.insert(e);

	}
	size_t end2 = clock();
	std::cout << "set insert : " << end2 - begin2 << std::endl;

	std::cout << us.size() << std::endl;
	std::unordered_map<int, int> um;
	std::unordered_map<int, int>::iterator it = um.begin();
}

void Func(const std::unordered_set<int>& us)
{
	std::unordered_set<int>::const_iterator it = us.begin();

	while (it != us.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

void Test_unordered_set()
{
	std::unordered_set<int> us;
	us.insert(3);
	us.insert(13);
	us.insert(23);
	us.insert(5);
	us.insert(15);
	us.insert(6);

	std::unordered_set<int>::iterator it = us.begin();
	while (it != us.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	for (auto e : us)
	{
		std::cout << e << " ";
	}
	Func(us);
}

int main()
{
	//test1();
	//test2();
	//closeHash::TestHT1();
	//closeHash::TestHT2();
	//bucketHash::TestHT1();
	//bucketHash::TestHT2();
	//fu::Test_unordered_set();
	fu::Test_unordered_map();
	//Test_unordered_set();

	return 0;
}

