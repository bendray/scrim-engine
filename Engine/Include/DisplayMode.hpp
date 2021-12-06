#pragma once

#include "types.hpp"

namespace Scrim
{
    struct DisplayMode
    {
        int width;
        int height;
        int refreshRate;
        int bpp;

        INLINE bool operator ==(const DisplayMode& other)
        {
            return this->width == other.width 
                && this->height == other.height 
                && this->refreshRate == other.refreshRate 
                && this->bpp == other.bpp;
        }

        INLINE bool operator !=(const DisplayMode& other)
        {
            return this->width != other.width 
                || this->height != other.height 
                || this->refreshRate != other.refreshRate 
                || this->bpp != other.bpp;
        }
    };
}
