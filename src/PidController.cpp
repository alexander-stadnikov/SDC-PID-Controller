#include "PidController.h"

#include <cmath>

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

    double PidController::TotalError() const noexcept
    {
        return -m_p * m_error.p - m_i * m_error.i * m_i - m_d * m_error.d;
    }

    double Throttle::Value() const noexcept
    {

        return m_throttle;
    }

    void Throttle::Update(double cte, double speed) noexcept
    {
        m_throttle = 1.0;
        if (std::fabs(cte) > .8)
        {
            m_slowDown = true;
        }

        if (m_slowDown)
        {
            if (speed > 50)
            {
                m_throttle = -1.0;
            }
            else if (std::fabs(cte) <= 0.3)
            {
                m_slowDown = false;
            }
        }
    }
}
