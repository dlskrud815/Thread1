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
	cv.wait(lock, [] { return alarm_set; }); // 이 값이 true가 될 때까지 wait
	cout << "알람이 울립니다!!" << endl;
}

int main()
{
	cout << "알람을 기다리는 중.. " << endl;
	
	thread timer1(alarm, chrono::seconds(3));
	thread timer2(wait_for_alarm);

	timer1.join();
	timer2.join();

	return 0;
}