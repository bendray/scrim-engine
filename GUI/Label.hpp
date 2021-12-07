#pragma once

#if defined(WIN32)|defined(_WIN32)|defined(__NT__)|defined(__WINDOWS__)|defined(__WINDOWS_386__)
#ifdef GUILIBRARY_EXPORTS
#define GUI_API __declspec(dllexport)
#else
#define GUI_API __declspec(dllimport)
#endif
#else //Unix-like
#define GUI_API
#endif //WIN32

#include <EngineInterfaces.hpp>

namespace Scrim::GUI
{
    class CGUI;
    class GUI_API CLabel
    {
    friend class CGUI;
    public:
        CLabel(ICanvas* pCanvas);
        ~CLabel(void);
        void SetLabel(const char* text, unsigned int x, unsigned int y, unsigned int size);
    private:
        ICanvas* m_pCanvas;
        std::vector<ITile2D*> m_pSprites;
    };
}
