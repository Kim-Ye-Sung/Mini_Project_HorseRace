#include "pch.h"
#include "HorseCondition.h"
#include <random>

HorseCondition::HorseCondition()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(Worst, Best);

    CurrentCondition = static_cast<Condition>(dist(gen));
}

void HorseCondition::SetCurrentCondition(int itemValue)
{
    int NewValue = static_cast<int>(CurrentCondition) + itemValue;

    if (NewValue < Worst)
    {
        NewValue = Worst;
    }
    else if (NewValue > Best)
    {
        NewValue = Best;
    }

    CurrentCondition = static_cast<Condition>(NewValue);
}
