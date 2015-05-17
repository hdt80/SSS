#include <core/Timer.h>

namespace sss {
    
    Timer::Timer(long duration) : _start(std::clock()), _duration(duration / 1000.0) {
    
    }

    Timer::~Timer() {
    
    }

    double Timer::elapsed() {
        return (double)((std::clock() - _start) / (double)CLOCKS_PER_SEC);
    }

    bool Timer::finished() {
        return elapsed() >= _duration;
    }

    void Timer::restart() {
        _start = std::clock();
    }
}
