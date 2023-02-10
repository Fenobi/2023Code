#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include "stack.h"
#include "queue.h"

using namespace std;

int main()
{
	/*fu::stack<int> st;
	fu::queue<int> q;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	while (!st.empty()||!q.empty())
	{
		cout << st.top() << '\n';
		cout << q.front() << '\n';
		st.pop();
		q.pop();
	}*/
	priority_queue<int> pq;
	pq.push(4);
	pq.push(2);
	pq.push(3);
	pq.push(1);

	return 0;
}