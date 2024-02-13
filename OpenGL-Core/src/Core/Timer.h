#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

#include <Core/Log.h>

#include <chrono>

class Timer {
public:
    using RepType       = double;
    using ClockType     = std::chrono::high_resolution_clock;
    using TimePointType = ClockType::time_point;
    using DurationType  = std::chrono::duration<RepType>;

public:
    Timer() :
        m_Start(), m_PauseStart(), m_PauseDur(DurationType::zero()),
        m_LastCallTime(0.0),
        m_IsStarted(false), m_IsRunning(false) {
    }

    ~Timer() = default;

    RepType Now() const {
        if (!m_IsStarted) {
            return DurationType::zero().count();
        }

        const TimePointType _Now                = ClockType::now();
        const DurationType _RealTimeDur         = _Now - m_Start;
        DurationType _TimerDur;

        if (m_IsRunning) {
            _TimerDur                           = _RealTimeDur - m_PauseDur;
        } else {
            const DurationType _CurrentPuaseDur = _Now - m_PauseStart;
            _TimerDur                           = _RealTimeDur - m_PauseDur - _CurrentPuaseDur;
        }
        m_LastCallTime = _TimerDur.count();
        return m_LastCallTime;
    }

    RepType Last() const {
        return m_LastCallTime;
    }

    void Start() {
        if (m_IsStarted) {
            CORE_WARN("Invalid Timer operation: Attempt to start an started Timer.\n");
            return;
        }
        m_Start     = ClockType::now();
        m_PauseDur  = DurationType::zero();
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
        m_LastCallTime = 0.0;
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

    mutable RepType m_LastCallTime;

    bool m_IsStarted; // ? started : un-started
    bool m_IsRunning; // ? running : paused
};

#endif // !CORE_TIMER_H_