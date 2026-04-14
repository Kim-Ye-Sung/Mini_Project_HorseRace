#pragma once

#include "Loan.h"

class PlayerUser
{
private:
	int Money = 5000;

	Loan LoanObj;

public:
	inline int GetMoney() const { return Money; }

	inline int GetLoanMoney() const { return LoanObj.GetLoanMoney(); }

	inline int GetDDay() const { return LoanObj.GetDDay(); }
};

