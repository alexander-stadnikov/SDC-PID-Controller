#include "PID.h"

namespace sdc
{
    void PidController::Init(double, double, double) noexcept
    {
    }

    void PidController::UpdateError(double) noexcept
    {
    }

    double PidController::TotalError() noexcept
    {
        return 0.0;
    }
}
