#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;


class BankAccount
{
public:
	BankAccount()
	{
		this->balacne = 1000;
	}

	void Deposit(int amount) 
	{
		this->balacne += amount;
		cout << "예금: " << this->balacne << endl;
	}

	void WithDraw(int amount)
	{
		this->balacne -= amount;
		cout << "예금: " << this->balacne << endl;
	}

private:
	int balacne;
};


//입금 함수
//count 횟수만큼 amount를 입금
void Iterative_Deposit(BankAccount& ba, int amount, int count)
{
	for (int i = 0; i < count; i++)
	{
		mtx.lock();
		ba.Deposit(amount);
		mtx.unlock();
	}
}

//출금 함수
//count 횟수만큼 amount를 출금
void Iterative_WithDraw(BankAccount& ba, int amount, int count)
{
	for (int i = 0; i < count; i++)
	{
		mtx.lock();
		ba.WithDraw(amount);
		mtx.unlock();
	}
}


int main()
{
	int amount = 100, count = 100;
	BankAccount bankAccount;

	thread t_deposit(Iterative_Deposit, ref(bankAccount), amount, count);
	thread t_withdraw(Iterative_WithDraw, ref(bankAccount), amount, count);

	t_deposit.join();
	t_withdraw.join();

	return 0;
}