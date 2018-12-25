#include <Clock.hpp>

#include <chrono>
#include <iostream>


long long Clock::m_lastTime = 0;

void Clock::startTimer()
{
    m_lastTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

void Clock::stopTimer()
{
    std::cout << "\nTime passed: " << (std::chrono::high_resolution_clock::now().time_since_epoch().count() - m_lastTime)/1000000000. << " seconds" << std::endl;
}
