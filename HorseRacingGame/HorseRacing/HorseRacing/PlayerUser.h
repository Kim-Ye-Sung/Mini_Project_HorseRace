#pragma once

#include "Loan.h"

class PlayerUser
{
private:
	int Money = 5000;

	Loan LoanObj;

	class Horse* SelectHorse = nullptr;

public:
	inline int GetMoney() const { return Money; }

	inline int GetLoanMoney() const { return LoanObj.GetLoanMoney(); }

	inline int GetDDay() const { return LoanObj.GetDDay(); }

	inline void SetSelectHorse(Horse* SelectHorse) { this->SelectHorse = SelectHorse; }
};

