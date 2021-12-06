#pragma once

#include <memory>
#include <functional>

#include <string>
#ifdef _UNICODE
#define _text(str) L##str
#else
#define _text(str) str
#endif

#undef INLINE
#ifdef _WIN32
#ifdef _MSC_VER
#define INLINE __forceinline
#endif
#else
#ifdef __GNUC__ 
#define INLINE __attribute__((always_inline))
#endif
#endif

#ifndef INLINE
#define INLINE inline
#endif

#include "InputEvent.hpp"

namespace Scrim
{
#ifdef _UNICODE
    using UString = std::wstring;
#else
    using UString = std::string;
#endif
    using String = std::string;
    using WString = std::wstring;

    using StateCallbackFunc = std::function<void(EventObject)>;
}
