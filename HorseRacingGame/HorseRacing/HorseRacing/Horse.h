#pragma once

#include <memory>
#include <atlimage.h>
#include "HorseCondition.h"

class Horse
{
private:
	std::unique_ptr<HorseCondition> ConditionComponent;

	CImage HorseImage;

public:
	Horse();

	virtual void AddPosition() = 0;

	CImage& GetHorseImage()  { return HorseImage; }
};