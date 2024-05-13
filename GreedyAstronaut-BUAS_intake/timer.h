#pragma once

#include <chrono>

class Timer {
public:
    Timer();

    void Start(); // Timer start
    void Update(); // Timer update
    bool IsFinished() const; // Is timer finished?
    int GetDuration() const; // Remaining durantion of timer

private:
    const int startingDuration;
    std::chrono::steady_clock::time_point startTime;
    int duration;
};