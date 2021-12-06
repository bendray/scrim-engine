#pragma once

#include <Windows.h>
#include "resource.h"

#include <IRenderWindow.hpp>

class RenderWindow : public Scrim::IRenderWindow
{
protected:
    RenderWindow(const RenderWindow&) = default;
    RenderWindow& operator=(const RenderWindow&) = default;
public:
    RenderWindow();
    ~RenderWindow(void);
    virtual void Update();
    virtual void SetCaption(const Scrim::UString& caption);
    virtual void SetSize(int w, int h);
    virtual void CenterWindow();

    virtual size_t GetWindowHandle() { return (size_t)m_hwnd; };
    virtual int GetWidth()
    {
        if(!IsFullScreen())
            return m_width;
        else
            return m_mode_fullscreen.width;
    }
    virtual int GetHeight()
    {
        if(!IsFullScreen())
            return m_height;
        else
            return m_mode_fullscreen.height;
    }
    virtual void OnResize()
    {
        if(!IsFullScreen() || !m_bModeSwitching)
        {
            RECT r;
            ::GetClientRect(m_hwnd, &r);
            m_width = r.right - r.left;
            m_height = r.bottom - r.top;
        }
        IRenderWindow::OnResize();
    }


    bool SwitchMode(bool fullscreen);
    void SetFullscreenMode(Scrim::DisplayMode mode);

    bool IsFullScreen()
    {
        return m_bFullscreen;
    }
    const Scrim::DisplayMode& GetFullscreenMode()
    {
        return m_mode_fullscreen;
    }
    bool IsModeSwitching()
    {
        return m_bModeSwitching;
    }
    void SetAltEnterLocked(bool state)
    {
        m_bAltEnterLocked = state;
    }
    bool IsAltEnterLocked()
    {
        return m_bAltEnterLocked;
    }

protected:
    HWND        m_hwnd;
    HINSTANCE   m_hInst;
    Scrim::DisplayMode m_mode_fullscreen{};
    DEVMODE     m_mode_window{};
    bool        m_bFullscreen;
    bool        m_bModeSwitching;
    bool        m_bAltEnterLocked;

};
