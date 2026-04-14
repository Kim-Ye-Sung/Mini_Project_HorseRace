#pragma once
class Loan
{
private :
	int LoanMoney = 6000;

	int DDay = 3;


public:
	inline int GetLoanMoney() const { return LoanMoney; }
	inline int GetDDay() const { return DDay; }

	void SetNewLoanMoney();
	void SetNewDDay();

	void DecreaseDDay();

};

