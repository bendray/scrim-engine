#include "Button.hpp"
#include "BitmapFont.hpp"

#include <Debug.hpp>

namespace Scrim::GUI
{
    CButton::CButton(ICanvas* pCanvas, ICanvas* pSpecialCanvas): m_pSpecialCanvas(pSpecialCanvas), m_pCanvas(pCanvas), m_pTrigger(nullptr)
    {}

    CButton::~CButton(void)
    {
        for(auto p = m_pSprites.begin(); p != m_pSprites.end(); p++ )
        {
            m_pCanvas->DetachObject(*p);
        }

        m_pSprites.clear();
        if(m_pTrigger != nullptr)
            m_pSpecialCanvas->DetachObject(m_pTrigger);
        m_pCanvas = nullptr;
    }

    void CButton::SetButton(const char* text, unsigned int x, unsigned int y, unsigned int size)
    {
        for(auto p = m_pSprites.begin(); p != m_pSprites.end(); p++ )
        {
            m_pCanvas->DetachObject(*p);
        }

        m_pSprites.clear();

        m_pTrigger = (ITile2D*)0xBADC0DE;//CreateObject2D("blue.tga", 0, 0, 1, 1);
        m_pTrigger->GetSprite()->SetPos((float)x+18, (float)y, 0);
        m_pTrigger->SetScale(1.5f, 0.5f);
        m_pSpecialCanvas->AttachObject(m_pTrigger);

        CBitmapFont font;
        if(font.Load("fontdata2.txt", "droid.tga")) //move loading fonts to gui
        {
            Debug::Log() << "Can't load font" << std::endl;
            return;
        }
        String stext = String(text);
        int i = 0;
        for(auto pc = stext.begin(); pc != stext.end(); pc++)
        {	

            ITile2D* pSprite = nullptr;
            char c = *pc;
            CBitmapFont::SFontData fontData = font.m_fontData[c - 32];

            pSprite = (ITile2D*)0xBADC0DE;//CreateObject2D("droid.tga", (int)fontData.x, 0, (int)fontData.w, 16);

            pSprite->GetSprite()->SetPos((float)x+i, (float)y, 0);

            pSprite->SetSize(fontData.w, 16.0f);
            pSprite->SetScale(0.188f, 0.34f);

            m_pCanvas->AttachObject(pSprite);
            m_pSprites.push_back(pSprite);
            i += 11;
        }
    }
}
