#include "Twiddler.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>

namespace sdc
{
    Twiddler::Twiddler(const PidController::Tau &tau,
                       double tolerance) noexcept
        : m_state{State::Increment},
          m_tau{tau.p, tau.i, tau.d},
          m_dTau{m_tau[0] / 10, m_tau[1] / 10, m_tau[2] / 10},
          m_tolerance(tolerance),
          m_param(0),
          m_bestErr(-1.0)
    {
    }

    void Twiddler::Update(double err) noexcept
    {
        if (std::isless(m_bestErr, 0.0))
        {
            m_bestErr = err;
        }

        if (std::isless(GetSumOfIncrements(), m_tolerance))
        {
            m_state = State::Done;
        }

        std::cout << "e=" << err << " be=" << m_bestErr << std::endl;
        std::cout << m_dTau[0] << " " << m_dTau[1] << " " << m_dTau[2] << std::endl;

        switch (m_state)
        {
        case State::Done:
            std::cout << "Tau:"
                      << " p= " << m_tau[0]
                      << " i= " << m_tau[1]
                      << " d= " << m_tau[2]
                      << std::endl;
            break;

        case State::Increment:
            std::cout << "Increment " << m_param << std::endl;
            m_tau[m_param] += m_dTau[m_param];
            m_state = State::Check;
            break;

        case State::Check:
            std::cout << "Check " << m_param << std::endl;
            if (std::isless(err, m_bestErr))
            {
                m_bestErr = err;
                m_dTau[m_param] *= 1.1;
                m_param++;
                if (m_param >= m_tau.size())
                {
                    m_param = 0;
                }
                m_state = State::Increment;
                Update(err);
            }
            else
            {
                m_tau[m_param] -= 2.0 * m_dTau[m_param];
                m_state = State::Decrement;
            }
            break;

        case State::Decrement:
            std::cout << "Decrement " << m_param << std::endl;
            if (std::isless(err, m_bestErr))
            {
                m_bestErr = err;
                m_dTau[m_param] *= 1.1;
            }
            else
            {
                m_tau[m_param] += m_dTau[m_param];
                m_dTau[m_param] *= 0.9;
            }
            m_state = State::Increment;
            m_param++;
            if (m_param >= m_tau.size())
            {
                m_param = 0;
            }
            Update(err);
            break;
        }
    }

    PidController::Tau Twiddler::GetTau() const noexcept
    {
        return {m_tau[0], m_tau[1], m_tau[2]};
    }

    double Twiddler::GetBestError() const noexcept
    {
        return m_bestErr;
    }

    double Twiddler::GetSumOfIncrements() const noexcept
    {
        return std::accumulate(m_dTau.cbegin(), m_dTau.cend(), 0.0);
    }
}