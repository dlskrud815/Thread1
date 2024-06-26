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
		cout << "����: " << this->balance << endl;
	}

	void WithDraw(int amount)
	{
		int temp = this->balance.load();
		this->balance.store(temp - amount);
		cout << "����: " << this->balance << endl;
	}

private:
	atomic<int> balance;
};


//�Ա� �Լ�
//count Ƚ����ŭ amount�� �Ա�
void Iterative_Deposit(BankAccount& ba, int amount, int count)
{
	for (int i = 0; i < count; i++)
	{
		ba.Deposit(amount);
	}
}

//��� �Լ�
//count Ƚ����ŭ amount�� ���
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