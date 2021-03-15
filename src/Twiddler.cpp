#include "Twiddler.h"

namespace sdc
{
    void Twiddler::Update() noexcept
    {
        test--;
        if (test < 0)
        {
            test = 500;
        }
    }

    bool Twiddler::IsEpochDone() const noexcept
    {
        return test <= 0;
    }
}