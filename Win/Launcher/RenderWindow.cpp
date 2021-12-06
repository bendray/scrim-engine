#include "RenderWindow.hpp"
#include <winuser.h>
#include <sstream>

#include <Debug.hpp>

#define MAX_LOADSTRING 100

//forward declaration
LRESULT __stdcall WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

RenderWindow::RenderWindow()
    :m_bFullscreen(false), m_bModeSwitching(false), m_bAltEnterLocked(false)
{
    //TCHAR szCaption[MAX_LOADSTRING];
    const wchar_t* szCaption = L"Window";
    //TCHAR szWindowClass[MAX_LOADSTRING];
    const wchar_t* szWindowClass = L"rApplication";

    m_width = 256;
    m_height = 256;

    m_hInst = GetModuleHandle(NULL);
    m_hwnd = NULL;

    //LoadString(m_hInst, IDC_WIN32, szWindowClass, MAX_LOADSTRING);

    WNDCLASSEX g_wndClass = {NULL};
    g_wndClass.cbSize = sizeof(WNDCLASSEX);
    g_wndClass.cbClsExtra = NULL;
    g_wndClass.cbWndExtra = NULL;
    g_wndClass.hbrBackground = (HBRUSH)GetStockObject(1);
    g_wndClass.hCursor  = NULL;//(HCURSOR)LoadCursor(NULL, IDC_ARROW);
    g_wndClass.hIcon = NULL;//LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON4));
    g_wndClass.hIconSm = NULL;//LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON4));
    g_wndClass.hInstance = m_hInst;
    g_wndClass.lpfnWndProc = WndProc;
    g_wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    g_wndClass.lpszMenuName = NULL;
    g_wndClass.lpszClassName = szWindowClass;

    if(!RegisterClassEx(&g_wndClass))
    {
         int lasterror = GetLastError();
         MessageBox(m_hwnd, _text("Can not create window class! We all gonna die!!"), _text("OMM!"), MB_OK);
    }

    //calculate window size
    RECT NewWindowSize;
    NewWindowSize.top = 30;
    NewWindowSize.left = 300;
    NewWindowSize.bottom = NewWindowSize.top + m_width;
    NewWindowSize.right = NewWindowSize.left + m_height;

    AdjustWindowRect(&NewWindowSize,WS_OVERLAPPEDWINDOW ,false);

    //LoadString(m_hInst, IDS_CAPTION, szCaption, MAX_LOADSTRING);
 

    if(!(m_hwnd = CreateWindowEx(NULL, szWindowClass, szCaption, WS_OVERLAPPEDWINDOW, 
    NewWindowSize.left, NewWindowSize.top,  NewWindowSize.right - NewWindowSize.left, NewWindowSize.bottom - NewWindowSize.top, NULL, NULL, m_hInst, NULL)))
    {
        MessageBox(m_hwnd, _text("Can not create window! We all gonna die!!"), _text("OMM!"), MB_OK);
    }

    ShowWindow(m_hwnd, SW_SHOWNORMAL);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);



    std::wostringstream st; 

    st << m_mode_window.dmSize << _text(" ") << m_mode_window.dmPelsWidth ; 

    m_mode_window.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &m_mode_window);

    RenderWindow* ptr = this;
    LONG_PTR val = (LONG_PTR)ptr;
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, val);

    m_mode_fullscreen.width = 1920;
    m_mode_fullscreen.height = 1080;
    m_mode_fullscreen.refreshRate = 60;
    m_mode_fullscreen.bpp = 4;

    CenterWindow();

    SetCaption(st.str());
}


RenderWindow::~RenderWindow(void)
{
    ChangeDisplaySettings(&m_mode_window, 0);
}


void RenderWindow::Update()
{
    MSG msg = {0};
    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        switch(msg.message)
        {
        case WM_QUIT:
        {
            Event_Quit.Invoke();
            //exit(0);
        }
        break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void RenderWindow::SetCaption(const Scrim::UString& caption)
{
    m_title = caption;
    SetWindowText(m_hwnd,caption.c_str());
}

bool RenderWindow::SwitchMode(bool fullscreen)
{
    m_bFullscreen = fullscreen;

    if(m_bFullscreen)
    {
        m_bModeSwitching = true;
        DEVMODE fmode{};
        fmode.dmSize = sizeof(DEVMODE);
        fmode.dmPelsWidth = m_mode_fullscreen.width;
        fmode.dmPelsHeight = m_mode_fullscreen.height;
        fmode.dmBitsPerPel = m_mode_window.dmBitsPerPel;
        fmode.dmDisplayFrequency = m_mode_fullscreen.refreshRate;
        fmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

        //if(ChangeDisplaySettings(&fmode,0)!= DISP_CHANGE_SUCCESSFUL)
        //return false;

        SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
        SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP);
        SetWindowPos(m_hwnd, HWND_TOPMOST,0,0,m_mode_fullscreen.width, m_mode_fullscreen.height, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
        m_bModeSwitching = false;
    }
    else
    {
        //if(ChangeDisplaySettings(&mode_window,0)!= DISP_CHANGE_SUCCESSFUL)
        //return false;
        SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW);
        SetWindowLong(m_hwnd, GWL_STYLE,  WS_OVERLAPPEDWINDOW);
        SetSize(m_width, m_height);
        CenterWindow();
    }
    Event_SwitchFullscreen.Invoke(this);
    return true;
}

void RenderWindow::CenterWindow()
{
    int mx = GetSystemMetrics(SM_CXSCREEN);
    int my = GetSystemMetrics(SM_CYSCREEN);

    int nx = (mx - m_width) / 2;
    int ny = (my - m_height) / 2;

    SetWindowPos(m_hwnd, NULL, nx, ny, -1, -1,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}
//Метод установки полноэкранного режима окну
void RenderWindow::SetFullscreenMode(Scrim::DisplayMode mode)
{
    m_mode_fullscreen = mode;
}
//Установка размера окна. Нараметры W и H
//являются соответственно шириной и высотой
//клиентской области окна. Общий размер окна подгоняется автоматически
void RenderWindow::SetSize(int w, int h)
{
    //нельзя менять размер окна если приложение работает в полноэкранном режиме
    if(!IsFullScreen())
    {
        m_width = w;
        m_height = h;
        RECT NewWindowSize{};
        NewWindowSize.top = 50;
        NewWindowSize.left = 50;
        NewWindowSize.bottom = NewWindowSize.top + h;
        NewWindowSize.right = NewWindowSize.left + w;
 
        AdjustWindowRect(&NewWindowSize,WS_OVERLAPPEDWINDOW,false);
        SetWindowPos(m_hwnd, HWND_TOP, NewWindowSize.left, NewWindowSize.top, NewWindowSize.right - NewWindowSize.left, NewWindowSize.bottom - NewWindowSize.top, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
        //::MoveWindow(m_hwnd,NewWindowSize.left, NewWindowSize.top, NewWindowSize.right - NewWindowSize.left, NewWindowSize.bottom - NewWindowSize.top, true);
        CenterWindow();
    }
}

LRESULT __stdcall WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch(message)
    {
    case WM_SIZE:
        {
            //не ресайзим девайс если окно свёрнуто
            if(wparam != SIZE_MINIMIZED)
            {
                LONG_PTR val = GetWindowLongPtr(hwnd, GWLP_USERDATA);
                if(val)
                {
                    RenderWindow* wnd = (RenderWindow*)val;
                    wnd->OnResize();
                }
            }
        }
        break;
    case WM_SETCURSOR:
        {
            static bool hiddencursor = false;
            WORD ht = LOWORD(lparam);

            LONG_PTR val = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if(val)
            {
                RenderWindow* wnd = (RenderWindow*)val;
                if(wnd->IsCursorVisible())
                {
                    ShowCursor(true);
                }
                else
                {
                    if (HTCLIENT==ht && !hiddencursor)
                    {
                        hiddencursor = true;
                        ShowCursor(false);
                    }
                    else if (HTCLIENT!=ht && hiddencursor) 
                    {
                        hiddencursor = false;
                        ShowCursor(true);
                    }
                }
            }
            
            
            
        }
        break;
    case WM_ACTIVATE: //Catch Alt + Tab
        {
            switch (wparam)
            {
            case WA_ACTIVE:
                {
                    LONG_PTR val = GetWindowLongPtr(hwnd, GWLP_USERDATA);
                    if(val)
                    {
                        RenderWindow* wnd = (RenderWindow*)val;
                        wnd->OnActivate();
                    }
                }
                break;
            case WA_INACTIVE:
                {
                    LONG_PTR val = GetWindowLongPtr(hwnd, GWLP_USERDATA);
                    if(val)
                    {
                        RenderWindow* wnd = (RenderWindow*)val;
                        wnd->OnDeactivate();
                    }
                }
                break;
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        DestroyWindow(hwnd);
        break;
    case WM_SYSKEYDOWN:
        switch(wparam)
        {
        case VK_RETURN:
            {
                if(GetKeyState(VK_MENU)) //Alt + Enter
                {
                    LONG_PTR val = GetWindowLongPtr(hwnd, GWLP_USERDATA);
                    if(val)
                    {
                        
                        RenderWindow* wnd = (RenderWindow*)val;
                        if(!wnd->IsAltEnterLocked())
                        {
                            wnd->SetAltEnterLocked(true);
                            wnd->SwitchMode(!wnd->IsFullScreen());
                            wnd->SetCursorVisible(false);
                        }
                    }
                }
            }
            break;
        }
        break;
    case WM_SYSKEYUP:
        {
            switch(wparam)
            {
            case VK_RETURN:
                {
                    LONG_PTR val = GetWindowLongPtr(hwnd, GWLP_USERDATA);
                    if(val)
                    {

                        RenderWindow* wnd = (RenderWindow*)val;
                        wnd->SetAltEnterLocked(false);
                    }
                }
                break;
            }
        }
        break;
    /*case WM_KEYDOWN:
        switch(wparam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            //exit(0);
            break;
        }*/
    }
    return DefWindowProc(hwnd, message, wparam, lparam);
}
