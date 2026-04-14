#pragma once

enum Condition
{
	Worst,
	Bad,
	Common,
	Good,
	Best
};

class HorseCondition
{
private:
	Condition CurrentCondition;

public:

	HorseCondition();

	inline void SetCurrentCondition(Condition CurrentCondition) { this->CurrentCondition = CurrentCondition; }
	void SetCurrentCondition(int itemValue);
};

