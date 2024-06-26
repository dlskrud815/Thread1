// Thread1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

using namespace std;

void printMessage(int count, string name)
{
    for (int i = 0; i < count; i++)
    {
        cout << name << ": hello from thread!" << endl;
    }
}

int main()
{
    thread t1(printMessage, 5, "t1"); //새로운 스레드 생성 및 입력 값 전달
    thread t2(printMessage, 10, "t2");
    
    t1.join();
    t2.join(); //메인 스레드가 t1, t2 스레드 종료 시까지 대기

    return 0;
}
