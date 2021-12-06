#pragma once

#include "DisplayMode.hpp"
#include "Delegate.hpp"

namespace Scrim
{
    class IRenderWindow
    {
    protected:
        IRenderWindow& operator=(const IRenderWindow&) = default;
    public:
        virtual ~IRenderWindow(void) = default;
        EVENT(ExitEvent);

        EVENT1(WindowEvent, IRenderWindow*);
        WindowEvent Event_Resize;
        WindowEvent Event_SwitchFullscreen;
        WindowEvent Event_Deactivate;
        WindowEvent Event_Activate;

        ExitEvent Event_Quit;

        virtual void Update() = 0;
        virtual void SetCaption(const UString& caption) = 0;
        virtual void SetSize(int w, int h) = 0;
        virtual void CenterWindow() = 0;
        virtual size_t GetWindowHandle() = 0;
        virtual int GetWidth() = 0;
        virtual int GetHeight() = 0;

        virtual const UString& GetCaption()
        {
            return m_title;
        }
        virtual void OnActivate()
        {
            m_bActive = true;
            Event_Activate.Invoke(this);
        }
        virtual void OnDeactivate()
        {
            m_bActive = false;
            Event_Deactivate.Invoke(this);
        }
        virtual bool IsActive()
        {
            return m_bActive;
        }
        virtual void OnResize()
        {
            Event_Resize.Invoke(this);
        }
        virtual void SetCursorVisible(bool state)
        {
            m_bCursorVisible = state;
        }
        virtual bool IsCursorVisible()
        {
            return m_bCursorVisible;
        }

    protected:
        UString m_title;
        int    m_width;
        int    m_height;
        bool   m_bActive = true;
        bool   m_bCursorVisible = true;
    };
}
