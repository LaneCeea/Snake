#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

#include <Core/Log.h>

#include <chrono>

class Timer {
public:
    using ClockType     = std::chrono::high_resolution_clock;
    using TimePointType = ClockType::time_point;
    using DurationType  = std::chrono::duration<double>;

public:
    Timer() :
        m_Start(), m_PauseStart(), m_PauseDur(DurationType::zero()),
        m_IsStarted(false), m_IsRunning(false) {
    }

    ~Timer() = default;

    double Time() const {
        if (!m_IsStarted) {
            return DurationType::zero().count();
        }

        const TimePointType _Now                = ClockType::now();
        const DurationType _RealTimeDur         = _Now - m_Start;

        if (m_IsRunning) {
            const DurationType _TimerDur        = _RealTimeDur - m_PauseDur;
            return _TimerDur.count();
        } else {
            const DurationType _CurrentPuaseDur = _Now - m_PauseStart;
            const DurationType _TimerDur        = _RealTimeDur - m_PauseDur - _CurrentPuaseDur;
            return _TimerDur.count();
        }
    }

    void Start() {
        if (m_IsStarted) {
            CORE_WARN("Invalid Timer operation: Attempt to start an started Timer.\n");
            return;
        }
        m_Start = ClockType::now();
        m_IsStarted = true;
        m_IsRunning = true;
    }

    void Reset() {
        if (!m_IsStarted) {
            CORE_WARN("Invalid Timer operation: Attempt to reset an un-started Timer.\n");
            return;
        }
        m_IsStarted = false;
        m_IsRunning = false;
    }

    void Pause() {
        if (!m_IsStarted || !m_IsRunning) {
            CORE_WARN("Invalid Timer operation: Attempt to pause an paused Timer.\n");
            return;
        }
        m_PauseStart = ClockType::now();
        m_IsRunning  = false;
    }

    void Resume() {
        if (!m_IsStarted) {
            CORE_WARN("Invalid Timer operation: Attempt to resume an un-started Timer.\n");
            return;
        }
        if (m_IsRunning) {
            CORE_WARN("Invalid Timer operation: Attempt to resume an running Timer.\n");
            return;
        }
        const TimePointType _Now = ClockType::now();
        m_PauseDur              += _Now - m_PauseStart;
        m_IsRunning              = true;
    }

    static double GlobalTime() {
        static const TimePointType _Zero;
        const TimePointType _Now = ClockType::now();
        const DurationType _Dur = _Now - _Zero;
        return _Dur.count();
    }

private:
    TimePointType m_Start;
    TimePointType m_PauseStart;
    DurationType m_PauseDur;

    bool m_IsStarted; // ? started : un-started
    bool m_IsRunning; // ? running : paused
};

#endif // !CORE_TIMER_H_