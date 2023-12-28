/*
* An object oriented implementation of the hierarchial design
* of various bank accounts.
*/

#include "account.h"
#include <iostream>
#include <string>

// Account class
int Account::AccNoGenerator = 10000;

Account::Account(const std::string &name, float balance):
Name(name), Balance(balance) {
	AccNo = ++AccNoGenerator;
}

Account::~Account() {
	std::cout << "~Account()\n";
}

const std::string Account::GetName() const {
	return Name;
}

float Account::GetBalance() const {
	return Balance;
}

int Account::GetAccNo() const {
	return AccNo;
}

float Account::GetInterestRate() const {
	return 0.0f; //Gets implemented by child classes.
}

void Account::AccumulateInterest() {
	Balance = 0.0f;	//Gets implemented by child classes.
}

void Account::Withdraw(float amount) {
	if (amount <= Balance)
		Balance -= amount;
	else {
		std::cout << "Insufficient Balance\n";
	}
}

void Account::Deposit(float amount) {
	Balance += amount;
}

// Savings class
Savings::Savings(const std::string &name, float balance, float rate) :
Account(name, balance), InterestRate(rate) {
}

Savings::~Savings() {
	std::cout << "~Savings()\n";
}

float Savings::GetInterestRate() const {
	return InterestRate;
}

void Savings::AccumulateInterest() {
	Balance += Balance * InterestRate;
}

// Checking class
//Checking::Checking(const std::string &name, float balance) :
//Account(name, balance) {
//}

Checking::~Checking() {
	std::cout << "~Checking()\n";
}

void Checking::Withdraw(float amount) {
	if (GetBalance() - amount > 500.0f)	// Make sure the balance does not fall below 500.
		// Balance -= amount;
		Account::Withdraw(amount);
	else {
		std::cout << "Insufficient Balance\n";
	}
}

void Transaction (Account *pTransAcc, float dAmount, float wAmount) {
	std::cout << "Transaction requested." << std::endl;
	std::cout << "Account #: " << pTransAcc->GetAccNo() << std::endl;
	std::cout << "Initial balance: " << pTransAcc->GetBalance() << std::endl;
	pTransAcc->Deposit(dAmount);
	pTransAcc->AccumulateInterest();
	pTransAcc->Withdraw(wAmount);
	std::cout << "Final balance: " << pTransAcc->GetBalance() << std::endl;
}
