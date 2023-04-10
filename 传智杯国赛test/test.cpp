#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> v;
	int my = 0;
	int temp;
	while (n--)
	{
		cin >> temp;
		v.push_back(temp);
	}
	int w;
	cin >> w;
	if (n == 0)
	{
		cout << 0;
		return 0;
	}
	sort(v.begin(), v.end());
	int i;
	int a;
	n = v.size();
	for (i = n - 1; i >= 0; --i)
	{
		if (w >= v[i])
		{
			my = v[i];
			break;
		}
	}
	a = i;
	int count = 0;
	for (i = 0; i < n; ++i)
	{
		if (v[i] <= my && i <= a)
		{
			my -= v[i];
			++count;
		}
	}
	cout << count;
	return 0;
}

//typedef long long ll;
//
//int main()
//{
//	int n, k;
//	cin >> n >> k;
//	vector<int> v;
//	int i;
//	int max = (1 << (k-1));
//	while (n--)
//	{
//		cin >> i;
//		v.push_back(i);
//	}
//	sort(v.begin(), v.end());
//	int a, b;
//	n = v.size();
//	for (i = 0; i < n; ++i)
//	{
//		if (v[i] > 0)
//		{
//			break;
//		}
//	}
//	b = i;
//	for (i = 0; i < n; ++i)
//	{
//		if (v[i] <= 0)
//		{
//			break;
//		}
//	}
//	a = i;
//	int sum = 0;
//	int count = 0;
//	for (i = 0; i < n; ++i)
//	{
//		if ((sum + v[i]) < max && (sum + v[i]) >= -max &&v[i]<0)
//		{
//			sum += v[i];
//			++count;
//		}
//		else
//			if (sum < 0)
//			{
//				if ((sum + v[b]) < max && (sum + v[b]) >= -max && n > 0 && v[b] >= 0)
//				{
//					sum += v[b];
//					++count;
//					++b;
//				}
//				else
//				{
//					break;
//				}
//			}
//			else
//			{
//				if ((sum + v[i]) < max && (sum + v[i]) >= -max && n > 0 && v[i] < 0)
//				{
//					sum += v[i];
//					++count;
//				}
//			}
//
//	}
//	printf("%d", count);
//	return 0;
//}


//int main() 
//{
//	ll ans = 0;
//	ll n, l, r;
//	ll cur = 0;
//	ll a, b;
//
//	cin >> n >> l >> r;
//	vector<pair<ll, ll>> v;
//	for (int i = 0; i < n; i++) 
//	{
//		cin >> a >> b;
//		v.push_back({ a,b });
//	}
//	cur += abs(l - v[0].first) + abs(r - v[0].second);
//	for (int i = 1; i < n; ++i) 
//	{
//		int x = v[i].first;
//		int y = v[i].second;
//
//		int l1 = x, r1 = y;
//		if (l < x) 
//		{
//			cur += x - l;
//			l1 = l;
//		}
//		else if (l > (x + 1)) 
//		{
//			cur += l - x - 1;
//			l1 = l - 1;
//		}
//
//		if (r < y - 1)
//		{
//			r1 = r + 1;
//			cur += y - r - 1;
//		}
//		else if (r > y) 
//		{
//			r1 = r;
//			cur += r - y;
//		}
//
//		r = r1;
//		l = l1;
//	}
//
//	cout << cur << endl;
//	return 0;
//}

//int main()
//{
//	string str1;
//	string str2;
//	cin >> str1 >> str2;
//	int n1 = str1.size();
//	int n2 = str2.size();
//	int i1 = -1, i2 = -1;
//	int i = 0;
//	while (i < n1) {
//		if (str1[i] == '.') {
//			i1 = i;
//			break;
//		}
//		++i;
//	}
//	i = 0;
//	while (i < n2) {
//		if (str2[i] == '.') {
//			i2 = i;
//			break;
//		}
//		++i;
//	}
//	if (i1 != -1 && i2 != -1)
//	{
//
//		while ((str1[n1] != '.') && (str1[n1] != '.'))
//		{
//			if (str1[n1--] != str2[n2--])
//			{
//				printf("NO");
//				return 0;
//			}
//		}
//	}
//	else if (i1 == -1 && i2 == -1)
//	{
//		printf("YES");
//	}
//	else
//	{
//		printf("NO");
//	}
//	printf("YES");
//	return 0;
//}


//#include<bits/stdc++.h>
//using namespace std;
//int main() 
//{
//	string a;
//	cin >> a;
//	string b;
//	cin >> b;
//	int n = a.size();
//	int m = b.size();
//	int index1 = -1, index2 = -1;
//	int i = 0;
//	while (i < n) {
//		if (a[i] == '.') {
//			index1 = i;
//			break;
//		}
//		i++;
//	}
//	i = 0;
//	while (i < m) {
//		if (b[i] == '.') {
//			index2 = i;
//			break;
//		}
//		i++;
//	}
//	if (index1 != -1 && index2 != -1) {
//
//
//		int i1 = n - 1;
//		int i2 = m - 1;
//		while (a[i1] == '0' && i1 > index1) {
//			i1--;
//		}
//		while (b[i2] == '0' && i2 > index2) {
//			i2--;
//		}
//		string s1 = " ", s2 = " ";
//		for (int j = index1 + 1; j <= i1; j++) {
//			s1 += a[j];
//		}
//		for (int j = index2 + 1; j <= i2; j++) {
//			s2 += b[j];
//		}
//		if (s1 == s2) {
//			cout << "YES" << endl;
//		}
//		else {
//			cout << "NO" << endl;
//		}
//
//	}
//	else if (index1 == -1 && index2 == -1) {
//		cout << "YES" << endl;
//
//	}
//	else {
//		cout << "NO" << endl;
//	}
//
//
//	return 0;
//}

//typedef unsigned long long ll;
//
//int main()
//{
//    int s;
//    ll sum = 0;
//    scanf("%d", &s);
//    int i = 1;
//    ll jie = 1;
//    while (s--)
//    {
//        jie *= i;
//        sum += jie;
//        ++i;
//    } 
//    printf("%lld", sum);
//    return 0;
//}

//int main()
//{
//	int n, count = 0;
//	int i = 0;
//	scanf("%d", &n);
//
//	while (i!=31)
//	{
//		if (((n & (0x1 >> i)) << i) == 1)
//		{
//			cout << 1;
//		}
//		else
//		{
//			cout << 0;
//		}
//		++i;
//	}
//
//	//printf("%d", i);
//	return 0;
//}

//int main()
//{
//	priority_queue<int, vector<int>, less<int>> pri;
//
//	pri.push(3);
//	pri.push(4);
//	pri.push(1);
//	pri.push(2);
//	pri.push(7);
//	pri.push(9);
//
//	while (!pri.empty())
//	{
//		cout << pri.top() << ' ';
//		pri.pop();
//	}
//
//	set<int> s;
//	s.insert(1);
//	s.insert(1);
//	s.insert(1);
//	s.insert(1);
//	s.insert(1);
//
//	s.insert(2);
//	for (auto e : s)
//	{
//		cout << e << ' ';
//	}
//
//	map<int, int> m;
//	m.insert(1, 2);
//	m.insert(1, 3);
//	m.insert(1, 4);
//	m.insert(2, 4);
//	m.insert(3, 4);
//	m.insert(4, 5);
//	/*for (auto e : s)
//	{
//		cout << e << ' ';
//	}*/
//	return 0;
//}
