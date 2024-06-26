#include <iostream>
#include <thread>

using namespace std;

class BankAccount
{
public:
	BankAccount()
	{
		this->balance.store(1000);
	}

	void Deposit(int amount)
	{
		int temp = this->balance.load();
		this->balance.store(temp + amount);
		cout << "예금: " << this->balance << endl;
	}

	void WithDraw(int amount)
	{
		int temp = this->balance.load();
		this->balance.store(temp - amount);
		cout << "예금: " << this->balance << endl;
	}

private:
	atomic<int> balance;
};


//입금 함수
//count 횟수만큼 amount를 입금
void Iterative_Deposit(BankAccount& ba, int amount, int count)
{
	for (int i = 0; i < count; i++)
	{
		ba.Deposit(amount);
	}
}

//출금 함수
//count 횟수만큼 amount를 출금
void Iterative_WithDraw(BankAccount& ba, int amount, int count)
{
	for (int i = 0; i < count; i++)
	{
		ba.WithDraw(amount);
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