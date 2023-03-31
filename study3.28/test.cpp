#include<iostream>
using namespace std;
const int fx[]={0,-2,-1,1,2,2,1,-1,-2};
const int fy[]={0,1,2,2,1,-1,-2,-2,-1};
long long f[40][40];bool s[40][40];
int b1,b2,d1,d2;
int main()
{ 
	cin >> b1 >> b2 >> d1 >> d2;
	b1 += 2, b2 += 2, d1 += 2, d2 += 2;
	f[2][1] = 1; s[d1][d2] = 1;
	for (int i = 1; i <= 8; ++i)
	{
		s[fx[i] + d1][fy[i] + d2] = 1;
	}
	for (int i = 2; i <= b1; ++i)
	{
		for (int j = 2; j <= b2; ++j) 
		{
			if (s[i][j])continue;
			f[i][j] = f[i - 1][j] + f[i][j - 1]; 
		} 
	}
	cout << f[b1][b2] << endl;
	return 0;
}