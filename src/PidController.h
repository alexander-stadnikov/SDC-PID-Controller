#pragma once

namespace sdc
{
    class PidController final
    {
    public:
        struct Tau
        {
            double p;
            double i;
            double d;
        };

    public:
        void Init(const Tau &) noexcept;
        void UpdateError(double cte) noexcept;
        double GetSteering() const noexcept;
        double GetTotalError() const noexcept;
        Tau GetTau() const noexcept;
        void SetTotalErrorNormalizer(int) noexcept;

    private:
        struct Error
        {
            double p;
            double i;
            double d;
            double prevCte;
            double total;
            double n;
            int normalizer;

            void Update(double) noexcept;
            double TotalError() const noexcept;
        };

        Error m_error;
        Tau m_tau;
    };
}
