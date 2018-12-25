#pragma once


class Clock
{
public:
    static void startTimer();
    static void stopTimer();

private:
    static long long m_lastTime;
};