// Thread2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void printMessage(int thread_num)
{
    for (int i = 0; i < 10; i++)
    {
        cout << endl << thread_num << ": " << i + 1 << endl;
    }
}

int main()
{
    vector <thread> threads;
    
    //for (int i = 0; i < 5; i++)
    //{
    //    threads.emplace_back(printMessage, i);
    //}

    //for (int i = 0; i < threads.size(); i++)
    //{
    //    threads[i].join();
    //}


    threads.resize(5);
    int i = 0;

    for (thread &th : threads)
    {
        th = thread(printMessage, i++);
    }

    for (thread& th : threads)
    {
        th.join();
    }

    return 0;
}
