#pragma once

#include "Horse.h"

class NormalHorse : public Horse
{
private:
	void AddPosition() override;

public:
	NormalHorse();

};

