#include "Edit.hpp"

#include "BitmapFont.hpp"

namespace Scrim::GUI
{
    CEdit::~CEdit(void)
    {
        for(auto p = m_pSprites.begin(); p != m_pSprites.end(); p++ )
        {
            m_pCanvas->DetachObject(*p);
        }

        m_pSprites.clear();
        m_pCanvas = nullptr;
    }

    CEdit::CEdit(ICanvas* pCanvas) : m_pCanvas(nullptr)
    {
        m_pCanvas = pCanvas;
    }

    void CEdit::SetText(const char* text, unsigned int x, unsigned int y, unsigned int size)
    {
        for(auto p = m_pSprites.begin(); p != m_pSprites.end(); p++ )
        {
            m_pCanvas->DetachObject(*p);
        }

        m_pSprites.clear();

        CBitmapFont font;
        font.Load("fontdata1.txt", "font.tga"); //move loading fonts to gui

        String stext = String(text);
        int i = 0;
        for(auto pc = stext.begin(); pc != stext.end(); pc++)
        {	

            ITile2D* pSprite = nullptr;
            char c = *pc;
            CBitmapFont::SFontData fontData = font.m_fontData[c - 32];

            pSprite = (ITile2D*)0xBADC0DE;//CreateObject2D("font.tga", fontData.x, 2.0f, fontData.w, 16.0f);

            pSprite->GetSprite()->SetPos((float)x+i, (float)y, 0);

            pSprite->SetSize(fontData.w, 16.0f);
            pSprite->SetScale(0.1878f, 0.36f);

            m_pCanvas->AttachObject(pSprite);
            m_pSprites.push_back(pSprite);
            i += 11.0f;
        }
    }
}
