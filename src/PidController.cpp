#include "PidController.h"

namespace sdc
{
    void PidController::Init(double p, double i, double d) noexcept
    {
        m_error = Error{0, 0, 0};
        m_p = p;
        m_i = i;
        m_d = d;
        m_prevCte = 0;
    }

    void PidController::UpdateError(double cte) noexcept
    {
        m_error.p = cte;
        m_error.i += cte;
        m_error.d = cte - m_prevCte;
        m_prevCte = cte;
    }

    double PidController::TotalError() noexcept
    {
        return -m_p * m_error.p - m_i * m_error.i * m_i - m_d * m_error.d;
    }
}
