//
// Created by Максим Фалалеев on 29/06/16.
//

#ifndef FASTCRAFT_TIMER_H
#define FASTCRAFT_TIMER_H

#include <chrono>

using namespace std::chrono;

namespace fastcraft {

    class Timer {
    public:
        Timer() : _prev_time(high_resolution_clock::now()) {
        }

        double getDeltaTime() {
            // Gett current time as a std::chrono::time_point
            // which basically contains info about the current point in time
            auto current = high_resolution_clock::now();
            // Compare the two to create time_point containing delta time in nanosecnds
            auto timeDiff = duration_cast<nanoseconds>(current - _prev_time);
            // Get the tics as a variable
            float delta = timeDiff.count();
            // Turn nanoseconds into seconds
            delta /= 1000000000;
            _prev_time = current;
            return delta;
        }

        // Returns time since last time this function was called
        // in seconds with nanosecond precision
        double getDeltaTicks() {
            // 1. Get current time as a std::chrono::time_point
            auto current = high_resolution_clock::now();

            // 2. Get the time difference as seconds
            // ...represented as a double
            duration<double> delta(current - _prev_time);

            // 3. Reset the timePrev to the current point in time
            _prev_time = current;

            // 4. Returns the number of ticks in delta
            return delta.count();
        }

    private:
        // For delta time calculation, updated every frame
        // We use high_resolution_clock
        // ...because we want the highest possible accuracy
        time_point<high_resolution_clock> _prev_time;
    };

}

#endif //FASTCRAFT_TIMER_H
