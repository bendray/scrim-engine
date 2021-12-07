#pragma once
#include <ScrimEngine.hpp>

#include "Label.hpp"
#include "Edit.hpp"
#include "Button.hpp"

namespace Scrim::GUI
{
    typedef std::shared_ptr<CLabel> Label_ptr;
    typedef std::shared_ptr<CEdit> Edit_ptr;
    typedef std::shared_ptr<CButton> Button_ptr;

    class IGUI
    {
    protected:
        IGUI& operator=(const IGUI&) = default;
    public:
        virtual ~IGUI() = default;
        virtual int Init(unsigned int flags) = 0;
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void OnResize(Scrim::IRenderWindow* pWnd) = 0;
        virtual Label_ptr Label(const char* text, unsigned int x, unsigned int y, unsigned int size) = 0;
        virtual Button_ptr Button(const char* text, unsigned int x, unsigned int y, unsigned int size) = 0;
        virtual void Dispose(Label_ptr ptr) = 0;
    };

    
    /*
    class Label_ptr
    {
    friend class CGUI;
    public:
        Label_ptr(){}
        CLabel* operator->(){ return m_pLabel; }
    private:
        Label_ptr(CLabel* pLabel) {m_pLabel = pLabel; }
        CLabel* m_pLabel;
    };
    */

    class GUI_API CGUI : public IGUI
    {
    public:
        CGUI(IInput* pInput, IAudioManager* pAudio);
        ~CGUI(void);
        int Init(unsigned int eGUI_Flags) override;
        void Draw() override;
        void Update() override;
        void OnResize(Scrim::IRenderWindow* pWnd) override;
        Label_ptr Label(const char* text, unsigned int x, unsigned int y, unsigned int size) override;
        Button_ptr Button(const char* text, unsigned int x, unsigned int y, unsigned int size) override;
        void Dispose(Label_ptr ptr) override;
        IStateManager* GetStateManager()
        { 
            return m_pStates.get();
        }
        const vec2& GetCursorPos()
        {
            return m_vCursor;
        }
        void SetCursorPos(float x, float y) 
        { 
            m_vCursor = vec2(x, y); 
        }
        Button_ptr Pick(float x, float y);
        IInput* GetInput()
        {
            return m_pInput;
        }
        IAudioManager* GetAudioManager()
        {
            return m_pAudio;
        }

    private:
        IInput* m_pInput = nullptr;
        IAudioManager* m_pAudio = nullptr;
        //TODO: layers
        std::unique_ptr<Scrim::Canvas> m_pCanvas = nullptr;
        std::unique_ptr<Scrim::Canvas> m_pSpecialCanvas = nullptr;
        //TODO: extended state manager
        std::unique_ptr<Scrim::StateManager> m_pStates = nullptr;
        std::unique_ptr<Scrim::StateManager> m_pControlStates = nullptr;

        std::vector<std::shared_ptr<CEdit>> m_widgets;
        vec2 m_vCursor;
    };
}

extern GUI_API Scrim::GUI::CGUI* g_pGUI;

