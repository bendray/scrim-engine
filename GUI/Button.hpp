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
    class GUI_API CButton
    {
        friend class CGUI;
    public:
        CButton(ICanvas* pCanvas, ICanvas* pSpecialCanvas);
        ~CButton(void);
        void SetButton(const char* text, unsigned int x, unsigned int y, unsigned int size);
    private:
        //todo: layers
        ICanvas* m_pCanvas;
        ICanvas* m_pSpecialCanvas;

        ITile2D* m_pTrigger;
        std::vector<ITile2D*> m_pSprites;
    };
}
