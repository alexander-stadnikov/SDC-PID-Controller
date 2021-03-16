#include "PidController.h"

namespace sdc
{
    void PidController::Init(const Tau &tau) noexcept
    {
        m_error = Error{0, 0, 0, 0, 0, 0};
        m_tau = tau;
    }

    void PidController::UpdateError(double cte) noexcept
    {
        m_error.Update(cte);
    }

    double PidController::GetSteering() const noexcept
    {
        return -m_tau.p * m_error.p -
               m_tau.i * m_error.i -
               m_tau.d * m_error.d;
    }

    double PidController::GetTotalError() const noexcept
    {
        return m_error.TotalError();
    }

    PidController::Tau PidController::GetTau() const noexcept
    {
        return m_tau;
    }

    void PidController::Error::Update(double cte) noexcept
    {
        p = cte;
        i += cte;
        d = cte - prevCte;
        prevCte = cte;
        total += cte * cte;
        n++;
    }

    double PidController::Error::TotalError() const noexcept
    {
        return total / n;
    }
}
