#pragma once

#include <variant>

namespace Scrim
{
    enum EIT
    {
            NONE = 0,
            CLICK,
            DOUBLECLICK,
            MOUSE_MOVE,
            MOUSE_PRESS,
            MOUSE_RELEASE,
            MOUSE_WHEEL,
            KEY_PRESS,
            KEY_RELEASE,
            X_AXIS,
            Y_AXIS,
            Z_AXIS
    };
    struct KeyboardEventType
    {
        unsigned short keyId;
        unsigned short modId;
    };
    struct MouseEventType
    {
        unsigned short x;
        unsigned short y;
        unsigned short mouseButtonId;
    };

    using EventObject = std::variant<int, KeyboardEventType, MouseEventType>;
}
