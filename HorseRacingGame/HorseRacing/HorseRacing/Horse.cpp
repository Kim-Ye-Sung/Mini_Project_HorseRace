#include "pch.h"
#include "Horse.h"

Horse::Horse()
{
	ConditionComponent = std::make_unique<HorseCondition>();
}
