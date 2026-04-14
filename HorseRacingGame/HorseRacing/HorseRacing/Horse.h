#pragma once

#include <memory>
#include <atlimage.h>
#include "HorseCondition.h"
#include "RecordComponent.h"

class Horse
{
private:
	std::unique_ptr<HorseCondition> ConditionComponent;
	std::unique_ptr<RecordComponent> RecordComponent_;

	CImage HorseImage;

public:
	Horse();

	virtual void AddPosition() = 0;

	CImage& GetHorseImage()  { return HorseImage; }
};