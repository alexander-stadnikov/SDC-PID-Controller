#pragma once

namespace sdc
{
    class Throttle
    {
    public:
        Throttle() noexcept;

        void SetMaxThrottle(double) noexcept;
        void SetMaxBrake(double) noexcept;
        void SetMaxCteThreshold(double) noexcept;
        void SetMinCteThreshold(double) noexcept;
        void SetStabilizationSpeed(double) noexcept;

        void Update(double cte, double speed) noexcept;
        double GetValue() const noexcept;

    private:
        bool m_slowDown = false;
        double m_throttle;
        double m_maxThrottle;
        double m_maxBrake;
        double m_maxCteThreshold;
        double m_minCteThreshold;
        double m_stabilizationSpeed;
    };
}