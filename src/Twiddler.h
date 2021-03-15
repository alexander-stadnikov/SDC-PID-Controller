#pragma once

namespace sdc
{
    class Twiddler
    {
    public:
        void Update() noexcept;
        bool IsEpochDone() const noexcept;

    private:
        int test{500};
    };
}