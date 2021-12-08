#include "RenderWindow.hpp"

Display* g_pDisplay = NULL;
Window* g_pWindow = NULL;
XVisualInfo* g_pVisualInfo = NULL;

RenderWindow::RenderWindow() : IRenderWindow(),
	m_bFullscreen(false), m_bModeSwitching(false), m_bAltEnterLocked(false)
{ 
	m_pDisplay = XOpenDisplay(NULL);

	GLint  attr[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	m_visualInfo = glXChooseVisual(m_pDisplay, 0, attr);
	if(m_visualInfo == NULL)
	{
			printf("error vi\n");
	}

	Colormap cm = XCreateColormap(m_pDisplay, DefaultRootWindow(m_pDisplay), m_visualInfo->visual, AllocNone);
	
	m_frameAttributes.colormap = cm;
	m_frameAttributes.event_mask = ExposureMask;

    	/* create the application window */
	m_window = XCreateWindow(	m_pDisplay,
					DefaultRootWindow(m_pDisplay), //XRootWindow(m_pDisplay, 0),
					0,
					0,
					640,
					480,
					5,
					m_visualInfo->depth,
					InputOutput, 
					m_visualInfo->visual, 
					CWColormap | CWEventMask, //CWBackPixel,
					&m_frameAttributes);

	XStoreName(m_pDisplay, m_window, "GUI Application");
	XSelectInput(m_pDisplay, m_window, ExposureMask | StructureNotifyMask);
	XMapWindow(m_pDisplay, m_window);

	m_wmDeleteWindow = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", true);
	XSetWMProtocols(m_pDisplay, m_window, &m_wmDeleteWindow, 1);
	
	g_pVisualInfo = m_visualInfo;
	g_pWindow = &m_window;
	g_pDisplay = m_pDisplay;
}

RenderWindow::~RenderWindow(void)
{
	XDestroyWindow(m_pDisplay, m_window);
	XCloseDisplay(m_pDisplay);
	m_window = None;
	m_pDisplay = NULL;
	g_pWindow = NULL;
	g_pDisplay = NULL;
}

void RenderWindow::Update()
{
	XWindowAttributes windowAttributes;
	XEvent e;
	while(XPending(m_pDisplay) > 0)
	{
		XNextEvent(m_pDisplay, &e);
		switch (e.type)
		{
		case Expose:
			{
				printf("exposed\n");
			}
			break;
		case ConfigureNotify:
			{
				XGetWindowAttributes(m_pDisplay, m_window, &windowAttributes);
				m_width = windowAttributes.width;
				m_height = windowAttributes.height;
				printf("resize\n");
				OnResize();
			}
			break;
		case DestroyNotify:
			{
				printf("destroy\n");
			}
			break;
		case ClientMessage:
			{
				if(e.xclient.data.l[0] == m_wmDeleteWindow)
				{
					printf("event quit\n");
					Event_Quit.Invoke();
				}
			}
			break;
		default:
			break;
		}
	}
}

void RenderWindow::SetCaption(const Scrim::UString& caption)
{
	m_title = caption;
}

bool RenderWindow::SwitchMode(bool fullscreen)
{
	m_bFullscreen = fullscreen;

	Event_SwitchFullscreen.Invoke(this);
	return true;
}

void RenderWindow::CenterWindow()
{
	
}

void RenderWindow::SetFullscreenMode(Scrim::DisplayMode mode)
{
	m_mode_fullscreen = mode;
}

void RenderWindow::SetSize(int w, int h)
{
	if(!IsFullScreen())
	{
		m_width = w;
		m_height = h;
		CenterWindow();
	}
}
