#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
bool alarm_set = false;

void alarm(chrono::seconds sec)
{
	this_thread::sleep_for(chrono::seconds(sec));
	{
		unique_lock<mutex> lock(mtx);
		alarm_set = true;
		cv.notify_one();
	}
}

void wait_for_alarm()
{
	unique_lock<mutex> lock(mtx);
	cv.wait(lock, [] { return alarm_set; }); // �� ���� true�� �� ������ wait
	cout << "�˶��� �︳�ϴ�!!" << endl;
}

int main()
{
	cout << "�˶��� ��ٸ��� ��.. " << endl;
	
	thread timer1(alarm, chrono::seconds(3));
	thread timer2(wait_for_alarm);

	timer1.join();
	timer2.join();

	return 0;
}