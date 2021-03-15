#pragma once

namespace sdc
{
    class Throttle
    {
    public:
        void Update(double cte, double speed) noexcept;
        double Value() const noexcept;

    private:
        bool m_slowDown = false;
        double m_throttle;
    };

    class PidController final
    {
    public:
        void Init(double p, double i, double d) noexcept;
        void UpdateError(double cte) noexcept;
        double TotalError() const noexcept;

    private:
        struct Error
        {
            double p;
            double i;
            double d;
        };

        Error m_error;
        double m_p;
        double m_i;
        double m_d;
        double m_prevCte;
    };
}
