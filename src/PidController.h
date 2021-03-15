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
        double Value() const noexcept;

    private:
        bool m_slowDown = false;
        double m_throttle;
        double m_maxThrottle;
        double m_maxBrake;
        double m_maxCteThreshold;
        double m_minCteThreshold;
        double m_stabilizationSpeed;
    };

    class PidController final
    {
    public:
        void Init(double p, double i, double d) noexcept;
        void UpdateError(double cte) noexcept;
        double Steering() const noexcept;
        double TotalError() const noexcept;

    private:
        struct Error
        {
            double p;
            double i;
            double d;
            double prevCte;
            double total;
            double n;

            void Update(double) noexcept;
            double TotalError() const noexcept;
        };

        struct Tau
        {
            double p;
            double i;
            double d;
        };

        Error m_error;
        Tau m_tau;
    };
}
