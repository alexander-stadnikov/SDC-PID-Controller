#pragma once

#include <string>
#include <cmath>

namespace sdc
{
    double deg2rad(double x)
    {
        return x * M_PI / 180;
    }

    double rad2deg(double x)
    {
        return x * 180 / M_PI;
    }

    // Checks if the SocketIO event has JSON data.
    // If there is data the JSON object in string format will be returned,
    // else the empty string "" will be returned.
    std::string hasData(std::string s)
    {
        auto found_null = s.find("null");
        auto b1 = s.find_first_of("[");
        auto b2 = s.find_last_of("]");
        if (found_null != std::string::npos)
        {
            return "";
        }
        else if (b1 != std::string::npos && b2 != std::string::npos)
        {
            return s.substr(b1, b2 - b1 + 1);
        }
        return "";
    }
}