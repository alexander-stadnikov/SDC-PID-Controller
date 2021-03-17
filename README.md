# PID Controller

This repository contains the implementation of the ["PID Controller"](https://en.wikipedia.org/wiki/PID_controller) Project for Udacity Course Self-Driving Car Engineer.

[**Full video**](https://www.youtube.com/watch?v=e9iFyyR1AEc)

![alt](./video_shortcut.gif)

## Goals

* A Self-Driving Car must be able to follow the planned route. The car uses a proportional–integral–derivative (PID) Controller.
* Code must compile without errors with ```cmake``` and ```make```
* No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or rollover any surfaces that would otherwise be considered unsafe (if humans were in the vehicle)


---
## Project Overview

The project contains two main components – the planning service and Udacity Simulator.
The service is a C++ application. It uses [uWebSockets](https://github.com/uWebSockets/uWebSockets) for network communications.
The simulator sends the telemetry data as a JSON object to the planning service and gets the trajectory back.
Data formats presented below are pseudo-JSON, comments, and values only for explanation.

### Simulator
You can download the Term3 Simulator which contains the Path Planning Project from the [releases tab](https://github.com/udacity/self-driving-car-sim/releases).

To run the simulator on Mac/Linux, first make the binary file executable with the following command:
```shell
sudo chmod u+x {simulator_file_name}
```

**Simulator data format**:

```
{
	"cte": 0.0, // The cross-track error
	"speed": 0.0, // The car's speed
	"steering_angle": 0.0, // The car's steering angle
}
```

**PID Controller data format**:

```
{
  "steering_angle": 0.0, // The steering angle
  "throttle": 0.0 // The throttle
}
```

## Parameters Tuning

The crucial part of the Controller is hyperparameters. In this project, these values were calculated with the Twiddle algorithm. The basic idea is similar to the Gradient Descent method. Values from the course used as starting values.

Results:

Parameter | Initial Value | Tuned Value
--- | --- | ---
**P** - Proportional | 0.15 | 0.16
**I** - Integral | 0.0004 | 0.0003
**D** - Differential | 3.0 | 3.0

The algorithm implemented in [Twiddler.cpp](./src/Twiddler.cpp)

## Throttle Control

The drive as fast as possible, the car uses very primitive throttle control:

```python
throttle = max_throttle
cte = abs(cte)

if cte > max_cte_threshold:
    slow_Down = true

if slowDown:
    if speed > stabilization_speed:
        throttle = brake
    elif cte <= min_cte_threshold:
        slow_down = False
```

The algorithm implemented in [Twiddler.cpp](./src/Throttle.cpp)

---

## Dependencies

* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`