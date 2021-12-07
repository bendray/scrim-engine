#pragma once

class CBitmapFont
{
public:
    struct SFontData
    {
        float x, y, w, h, size;
    };

    CBitmapFont(void);
    ~CBitmapFont(void);

    int Load(const char* fontData, const char* fontName);

    SFontData m_fontData[95];
};
