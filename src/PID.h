#pragma once

namespace sdc
{
    class PidController final
    {
    public:
        void Init(double p, double i, double d) noexcept;
        void UpdateError(double cte) noexcept;
        double TotalError() noexcept;

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
    };
}
