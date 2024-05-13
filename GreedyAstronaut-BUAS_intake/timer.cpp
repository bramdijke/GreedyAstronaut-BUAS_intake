#include "timer.h"

Timer::Timer() : startingDuration(60), duration(startingDuration) {} // Initialize starting duration to 60

void Timer::Start() {
    startTime = std::chrono::steady_clock::now(); // Current time is starting time of timer
}

void Timer::Update() { // Function to update the time
    auto endTime = std::chrono::steady_clock::now(); // Current time
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime); // Calculates time elapsed in seconds
    duration = startingDuration - elapsedSeconds.count(); // Calculates remaing duration
    if (duration < 0) { // Makes sure duration isn't negative
        duration = 0;
    }
}

bool Timer::IsFinished() const { // Checks if the timer is finished
    return duration <= 0;
}

int Timer::GetDuration() const { // Gets the remaining duration 
    return duration;
}

void Timer::Reset() { // Function to reset timer
    duration = startingDuration; //  Resets duration equal to startingDuration (60 seconds)
    startTime = std::chrono::steady_clock::now();
}