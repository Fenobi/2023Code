#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int main()
{

    int a = 2, b = 1, c = 2;
    if (a < b)
        if (b < 0)
            c = 0;
        else
            c++;
    printf("%d\n", c);
    //int n,m;
    //cin >> n >> m;
    //int arr[100][100];
    ////vector<vector<int>> vv;
    //for (int i = 0; i < n; i++)
    //{
    //    for (int j = 0; j < m; j++)
    //    {
    //        arr[i][j] = 0;
    //    }
    //}

    //int t;
    //cin >> t;
    //int x, y;
    //cin >> x >> y;
    //
    //    

    //
    //return 0;
}

//
//int main()
//{
//	int n;
//	cin >> n;
//	while (n--)
//	{
//		int ax, ay, bx, by, cx, cy, dx, dy;
//		cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
//		if()
//	}
//	return 0;
//}

//int main()
//{
//	vector<int> st;
//	vector<int> q;
//	int n;
//	cin >> n;
//	int a = 0;
//	int sum = 0;
//	for (int i = 0; i < n; ++i)
//	{
//		int ch;
//		cin >> ch;
//		st.push_back(ch);
//	}
//	for (int i = 1; i < n; ++i)
//	{
//		
//		if (st[i] == 0)
//		{
//			if (st[i-1] == 0)
//			{
//				++a;
//			}
//			else if(st[i-1]==1)
//			sum += 1;
//		}
//		else if (st[i] == 1)
//		{
//			if (st[i - 1] == 0)
//			{
//				--a;
//				sum += 1;
//			}
//			else if(st[i-1]==1)
//			{
//				sum *= 2;
//			}
//		}
//		
//	}
//	cout << sum;
//	return 0;
//}

//int main()
//{
//	int n;
//	cin >> n;
//	long double a, b;
//	while (n--)
//	{
//		cin >> a >> b;
//		int count = 0;
//		int i = 1;
//		int t = 5000;
//		while (t--)
//		{
//			long double c = i * a, d = i * b;
//			if (((long long)d - (long long)c) >= 1)
//			{
//				++count;
//				break;
//			}
//			else
//			{
//				++count;
//			}
//			++i;
//		}
//		cout << count << endl;
//	}
//	return 0;
//}

    //unsigned long long tang(unsigned long long x, unsigned long long y, unsigned long long z)
    //{
    //   
    //}


//int main()
//{
//    //int n, m;
//    //cin >> n;
//    //while (n--)
//    //{ 
//    //    int i = 0;
//    //    cin >> m;
//    //    vector<int> v;
//    //    
//    //    while (m--)
//    //    {
//    //        cin >> i;
//    //        v.push_back(i);
//    //    }
//    //    sort(v.begin(), v.end());
//    //    cout << v[0] + v[1] << '\n';
//    //}
//    int m;
//    cin >> m;
//    int count = 1;
//    while (m--)
//    {
//        unsigned long long n, a, b, c;
//        cin >> n >> a >> b >> c;
//        unsigned long long x = a, y = b, z = c;
//        unsigned long long num;
//        vector<unsigned long long> v;
//        unsigned long long g = 1;
//        int p = n;
//        while (n--)
//        {
//            unsigned long long t;
//            x ^= x << 16;
//            x ^= x >> 5;
//            x ^= x << 1;
//            t = x;
//            x = y;
//            y = z;
//            z = t ^ x ^ y;
//            v.push_back(z);
//        }
//        for (int i = p - 1; i >= 0; --i)
//            g *= v[i];
//        g *= 2;
//        
//        cout << "Case #" << count++ << ":" << g << endl;
//     //   printf("Case #%d:%lld\n", count++, g);
//
//    }
//
//
//
//
//
//    return 0;
//}


//int main()
//{
//	int p1, p2, p3, i = 0;
//	char s[101] = { 0 };
//	cin >> p1 >> p2 >> p3 >> s;
//	char p = 0,j;
//	char prve, next, now;
//	while (s[i])
//	{
//		prve = s[i - 1];
//		next = s[i + 1];
//		now = s[i];
//		if (now == '-' && prve < next && ((prve >= '0' && next <= '9') || (prve >= 'a' && next <= 'z')))
//		{
//			for (p3 == 1 ? j = prve + 1 : j = next - 1; p3 == 1 ? j < next : j > prve; p3 == 1 ? ++j : --j)
//			{
//				p = j;
//				if (p1 == 2)
//					p = (j >= 'a') ? j - 32 : j;
//				else if (p1 == 3)
//					p = '*';
//				for (int k = 0; k < p2; ++k)
//					cout << p;
//			}
//		}
//		else
//		{
//			cout << now;
//		}
//		++i;
//	}
//
//	return 0;
//}
//



//int main()
//{
//	int p1, p2, p3,i;
//	cin >> p1 >> p2 >> p3;
//	string s;
//	string add;
//	char temp = getchar();
//	getline(cin, s);
//	int n = s.size();
//	string::iterator it = s.begin();
//	
//	for (i = 0; i < n - 1; ++i)
//	{
//		if (s[i] == '-')
//		{ 
//			if (s[i - 1] < s[i + 1])
//			{
//				int a = 1;
//				while ((s[i - 1] + a) != s[i + 1] - 1)
//				{
//					int t1 = p2;
//					while (t1--)
//					{
//						if (p1 == 3)
//							add.push_back('*');
//						else if (p1 == 2 && s[i - 1] < '0' && s[i - 1]>'9')
//							add.push_back(s[i - 1] + a + 32);
//						else
//							add.push_back(s[i - 1] + a);
//					}
//					++a;
//				}
//			}
//			else 
//			{
//				add.push_back(s[i++]);
//			}
//		}
//		if (s[i] == '-')
//			++i;
//		add.push_back(s[i]);
//	}
//	cout << add;
//	
//	return 0;
//}
//int main()
//{
//	int i, j, long float a, b, x, y;
//	scanf("%d %lf %lf", &j, &a, &b);
//
//	for (i = 1; x - y < 1; i++)
//	{
//		x = i * a, y = i * b;
//		printf("")
//	}
//
//	return 0;
//}
//
