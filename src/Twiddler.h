#pragma once

#include "PidController.h"

#include <vector>

namespace sdc
{
    class Twiddler
    {
    public:
        explicit Twiddler(const PidController::Tau &tau, double tolerance) noexcept;

        void Update(double err) noexcept;
        PidController::Tau GetTau() const noexcept;
        double GetBestError() const noexcept;
        double GetSumOfIncrements() const noexcept;

    private:
        enum class State
        {
            Increment,
            Check,
            Decrement,
            Done
        };

        State m_state;
        std::vector<double> m_tau;
        std::vector<double> m_dTau;
        const double m_tolerance;
        std::vector<double>::size_type m_param;
        double m_bestErr;
    };
}