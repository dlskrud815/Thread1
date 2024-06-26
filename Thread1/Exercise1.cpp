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
		cout << "����: " << this->balacne << endl;
	}

	void WithDraw(int amount)
	{
		this->balacne -= amount;
		cout << "����: " << this->balacne << endl;
	}

private:
	int balacne;
};


//�Ա� �Լ�
//count Ƚ����ŭ amount�� �Ա�
void Iterative_Deposit(BankAccount& ba, int amount, int count)
{
	for (int i = 0; i < count; i++)
	{
		mtx.lock();
		ba.Deposit(amount);
		mtx.unlock();
	}
}

//��� �Լ�
//count Ƚ����ŭ amount�� ���
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