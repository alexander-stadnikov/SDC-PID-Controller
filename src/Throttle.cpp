#include "Throttle.h"

#include <cmath>

namespace sdc
{
    Throttle::Throttle() noexcept
        : m_throttle(0.0),
          m_maxThrottle(0.0),
          m_maxBrake(0.0),
          m_maxCteThreshold(0.0),
          m_minCteThreshold(0.0),
          m_stabilizationSpeed(0.0)
    {
    }

    void Throttle::SetMaxThrottle(double v) noexcept
    {
        m_maxThrottle = v;
    }

    void Throttle::SetMaxBrake(double v) noexcept
    {
        m_maxBrake = v;
    }

    void Throttle::SetMaxCteThreshold(double v) noexcept
    {
        m_maxCteThreshold = v;
    }

    void Throttle::SetMinCteThreshold(double v) noexcept
    {
        m_minCteThreshold = v;
    }

    void Throttle::SetStabilizationSpeed(double v) noexcept
    {
        m_stabilizationSpeed = v;
    }

    double Throttle::GetValue() const noexcept
    {
        return m_throttle;
    }

    void Throttle::Update(double cte, double speed) noexcept
    {
        m_throttle = m_maxThrottle;
        cte = std::fabs(cte);

        if (cte > m_maxCteThreshold)
        {
            m_slowDown = true;
        }

        if (m_slowDown)
        {
            if (speed > m_stabilizationSpeed)
            {
                m_throttle = m_maxBrake;
            }
            else if (cte <= m_minCteThreshold)
            {
                m_slowDown = false;
            }
        }
    }
}