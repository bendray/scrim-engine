#pragma once

#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>

namespace Scrim::Debug
{
    class Log 
    {
    public:
        Log() = default;
        ~Log() = default;
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator=(Log&&) = delete;     
        Log& operator<<(std::_Setw&& manipulator)
        {
#ifdef DEBUG
            std::cout << manipulator;
#endif
            return *this;
        }
        template< typename CharT>
        Log& operator<<(std::_Put_time<CharT>&& manipulator)
        {
#ifdef DEBUG
            std::cout << manipulator;
#endif
            return *this;
        }
        template< typename T>
        Log& operator<<(T str)
        {
#ifdef DEBUG
            std::cout << str;
#endif
            return *this;
        }
        template< typename T>
        Log& operator<<(T* str)
        {
#ifdef DEBUG
            std::cout << str;
#endif
            return *this;
        }
        Log& operator<<(std::ostream&(*manipulator)(std::ostream&))
        {
#ifdef DEBUG
            std::cout << manipulator;
#endif
            return *this;
        }
    private:
    };
}
