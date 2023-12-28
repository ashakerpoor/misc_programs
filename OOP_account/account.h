/* The header file:
* An object oriented implementation of the hierarchial design
* of various bank accounts.
*/

#pragma once
#include <string>

class Account {
	int AccNo;
	std::string Name;
	static int AccNoGenerator;

protected:
	float Balance;

public:
	Account(const std::string &name, float balance);
	virtual ~Account();
	const std::string GetName() const;
	float GetBalance() const;
	int GetAccNo() const;

	virtual float GetInterestRate() const;
	virtual	void AccumulateInterest();
	virtual	void Withdraw(float amount);

	void Deposit(float amount);
};

class Savings :
	public Account {
		float InterestRate;

	public:
		Savings(const std::string &name, float balance, float rate);
		~Savings();
		float GetInterestRate() const override;
		void AccumulateInterest() override;
};

class Checking :
	public Account {
	public:
	//	Checking(const std::string &name, float balance);
		using Account::Account;
		~Checking();
		void Withdraw(float amount) override;
};

void Transaction (Account *pTransAcc, float dAmount, float wAmount);
