#pragma once

#include <IRenderWindow.hpp>

#include <X11/Xlib.h>
#include <GL/glx.h>

extern Display* g_pDisplay;
extern Window* g_pWindow;
extern XVisualInfo* g_pVisualInfo;


//Window class
//TODO: add fullscreen mode to interface
class RenderWindow : public Scrim::IRenderWindow
{
public:
	RenderWindow();
	//RenderWindow(RenderWindow& other);
	~RenderWindow(void);
	virtual void Update();
	virtual void SetCaption(const Scrim::UString& caption);
	virtual void SetSize(int w, int h);
	virtual void CenterWindow();

	virtual size_t GetWindowHandle() { return (size_t)m_window; }

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
			
		}
		Scrim::IRenderWindow::OnResize();
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
	Scrim::DisplayMode m_mode_fullscreen;
	bool        m_bFullscreen;
	bool        m_bModeSwitching;
	bool        m_bAltEnterLocked;

	Display* m_pDisplay;
	XVisualInfo* m_visualInfo;

	XSetWindowAttributes m_frameAttributes;
	Window               m_window;

	Atom m_wmDeleteWindow;

	XKeyEvent m_event;

};
