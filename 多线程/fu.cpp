#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

void thread_run()
{
	while (true)
	{
		cout << "�������߳�" << endl;
		Sleep(1000);
	}
}

int main()
{
	thread tr(thread_run);
	
	while (true)
	{
		cout << "�������߳�" << endl;
		Sleep(1000);
	}
	tr.join();

	return 0;
}