#pragma once

namespace Scrim
{
    enum eAPP_ERROR
    {
        AE_OK = 0,
        AE_FAIL = 1 << 0,
        AE_BAD_CONFIG = 1 << 1
    };

    enum eAPP_STATE
    {
        AS_SETTINGS = 0,
        AS_EDITOR = 1 << 0
    };
}
