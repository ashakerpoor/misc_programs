#include "account.h"
#include <iostream>
#include <string>


int main() {

	Account acc_1("Lisa", 3521.44);
	std::cout << acc_1.GetInterestRate() << std::endl;
	std::cout << acc_1.GetName() << std::endl;
	std::cout << acc_1.GetAccNo() << std::endl;
	std::cout << acc_1.GetBalance() << std::endl;

	Savings svg_1("Mark", 4072.1, .03);
	std::cout << svg_1.GetName() << std::endl;
	std::cout << svg_1.GetAccNo() << std::endl;
	std::cout << "Before interest rate applied: " << svg_1.GetBalance() << std::endl;
	svg_1.AccumulateInterest();
	std::cout << "After interest rate applied: " << svg_1.GetBalance() << std::endl;

	Checking ckg_1("Frank", 780.0);
	std::cout << ckg_1.GetName() << std::endl;
	std::cout << ckg_1.GetAccNo() << std::endl;
	ckg_1.Withdraw(500);
	std::cout << "After Withdrawal: " << ckg_1.GetBalance() << std::endl;


	Savings svg_2("Homer", 1700., .04);
	Transaction (&svg_2, 300, 500);

	return 0;
}
