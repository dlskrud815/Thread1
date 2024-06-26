#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// global ����
mutex mtx; // ���ؽ� ��ü ����
int counter = 0;

void increment()
{
	for (int i = 0; i < 100000; i++)
	{
		mtx.lock(); // �Ӱ� ������ ���� ���� ���
		++counter; // ���� �ڿ��� ����
		mtx.unlock(); // �Ӱ� ������ ����� ��� ����
	} //mtx ������� ������ Context Switching �Ͼ

	//for (int i = 0; i < 1000; i++)
	//{
	//	lock_guard<mutex> lock(mtx);
	//	++counter;
	//}
}

int main()
{
	thread t1(increment);
	thread t2(increment);
	thread t3(increment);

	t1.join();
	t2.join();
	t3.join();

	cout << "Final counter value: " << counter << endl;

	return 0;
}