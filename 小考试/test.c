#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>

//int main()
//{
	//int i;
	////答题区域
	//for (i = 20; i <= 50; ++i)
	//{
	//	if (i % 2 == 0 && i % 7 == 0)
	//	{
	//		printf("%d ", i);
	//	}
	//}
	//int a[10], i, sum;
	//sum = 0;
	//for (i = 1; i <= 10; ++i)
	//{
	//	a[i - 1] = i * 2;
	//	sum += a[i - 1];
	//}
	//printf("%d", sum);
	//int a, g, s, b;
	//scanf("%d", &a);
	//g = a % 10;
	//s = a / 10 % 10;
	//b = a / 100;
	//if (g*g*g==s*s*s==b*b*b)
	//{
	//	//后面看不到了，这个反正是 判断是水仙花数的条件
	//	
	//}
	/*int i ,j;
	for (i = 1; i <= 9; ++i)
	{
		for (j = i; j <= 9; ++j)
		{
			printf("%d*%d=%02d ", i, j, i * j);
		}
		printf("\n");
	}
	return 0;
}*/

//#include <stdio.h>
//#include <math.h>
//
//int main()
//{
//	int p = 1;
//	int j;
//	int out;
//	for (int i = 0; i < 6; ++i)
//	{
//		for (j = 2; j < i; ++j)
//		{
//			if (i % j == 0)
//			{
//				break;
//			}
//			if (pow(2, j) - 1 % j == 0)
//			{
//				break;
//			}
//		}
//		if (i == j)
//		{
//			p = i;
//			out = (pow(2, p) - 1) * pow(2, p - 1);
//			printf("%d ", out);
//			
//		}
//	}
//	return 0;
//}

#include <stdio.h>

void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void SelectSort(int* a, int n)
{
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int maxi = end;
		int mini = begin;
		for (int i = begin; i <= end; i++)
		{
			if (a[maxi] < a[i])
			{
				maxi = i;
			}
			if (a[mini] > a[i])
			{
				mini = i;
			}
		}
		Swap(&a[begin], &a[mini]);
		if (maxi == begin)
		{
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);
		begin++;
		end--;
	}
}


int main()
{
	int arr1[] = { 7,6,5,4,3,2,1 };
	int arr2[] = {0,1,2,3,4,5,6};
	char ch[4] = "off";
	ch[0] = "on";
	int n = sizeof(arr1) / sizeof(arr1[0]);
	for (int i = 0; i < n; ++i)
	{
		int mini = i;
		int j = i;
		for (; j < n ; ++j)
		{
			if (arr1[mini] > arr1[j])
			{
				mini = j;
			}
		}
		Swap(&arr2[mini], &arr2[i]);
		Swap(&arr1[mini], &arr1[i]);

	}
	
	return 0;
}