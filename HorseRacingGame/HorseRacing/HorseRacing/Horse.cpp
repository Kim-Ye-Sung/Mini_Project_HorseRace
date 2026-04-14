#include "pch.h"
#include "Horse.h"

Horse::Horse()
{
	ConditionComponent = std::make_unique<HorseCondition>();
	RecordComponent_ = std::make_unique<RecordComponent>();
}
