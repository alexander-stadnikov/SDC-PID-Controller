#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"

#include "PidController.h"
#include "Throttle.h"
#include "Twiddler.h"
#include "Helpers.h"

int main()
{
    uWS::Hub h;

    sdc::PidController pid;
    pid.Init(0.0, 0.0, 0.0);

    sdc::Throttle throttle;
    throttle.SetMaxThrottle(1.0);
    throttle.SetMaxBrake(-1.0);
    throttle.SetMaxCteThreshold(0.8);
    throttle.SetMinCteThreshold(0.3);
    throttle.SetStabilizationSpeed(30.0);

    sdc::Twiddler twiddler;

    h.onMessage([&pid, &throttle, &twiddler](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                                             uWS::OpCode opCode) {
        // "42" at the start of the message means there's a websocket message event.
        // The 4 signifies a websocket message
        // The 2 signifies a websocket event
        if (length && length > 2 && data[0] == '4' && data[1] == '2')
        {
            auto s = sdc::hasData(std::string(data).substr(0, length));

            if (s != "")
            {
                auto j = nlohmann::json::parse(s);

                std::string event = j[0].get<std::string>();

                if (event == "telemetry")
                {
                    // j[1] is the data JSON object
                    double cte = std::stod(j[1]["cte"].get<std::string>());
                    double speed = std::stod(j[1]["speed"].get<std::string>());
                    // double angle = std::stod(j[1]["steering_angle"].get<std::string>());

                    pid.UpdateError(cte);
                    throttle.Update(cte, speed);
                    double steer_value = pid.GetSteering();
                    twiddler.Update();

                    if (twiddler.IsEpochDone())
                    {
                        std::string reset_msg = "42[\"reset\",{}]";
                        ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
                        return;
                    }

                    // DEBUG
                    std::cout << "CTE: " << cte << " Steering Value: " << steer_value
                              << std::endl;

                    nlohmann::json msgJson;
                    msgJson["steering_angle"] = steer_value;
                    msgJson["throttle"] = throttle.GetValue();
                    auto msg = "42[\"steer\"," + msgJson.dump() + "]";
                    std::cout << msg << std::endl;
                    ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                } // end "telemetry" if
            }
            else
            {
                // Manual driving
                std::string msg = "42[\"manual\",{}]";
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
        } // end websocket message if
    });   // end h.onMessage

    h.onConnection([&](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        std::cout << "Connected!!!" << std::endl;
    });

    h.onDisconnection([&](uWS::WebSocket<uWS::SERVER> ws, int code,
                          char *message, size_t length) {
        ws.close();
        std::cout << "Disconnected" << std::endl;
    });

    int port = 4567;
    if (h.listen(port))
    {
        std::cout << "Listening to port " << port << std::endl;
    }
    else
    {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }

    h.run();
}