#pragma once

#include <ScrimEngine.hpp>

template<int X, int Y, int PK, int RK>
class InputControllerStub : public Scrim::IInputController
{
public:
    InputControllerStub() = default;
    ~InputControllerStub() = default;
    InputControllerStub(const InputControllerStub&) = default;
    //IInputController
    int Load(Scrim::IInputModel* pInput, Scrim::IRenderWindow* pOutput, bool exclusive)
    {
            SetModel(pInput);
            return true;
    }
    void CaptureInput()
    {
            SetKeyState(m_pkey, true);
            SetKeyState(m_rkey, false);
            SetMouseState(Scrim::MouseState{ 3, m_x, m_y }); // pressed both
            SetMouseState(Scrim::MouseState{ 1, m_x, m_y }); // release second
    }
    void OnResize(Scrim::IRenderWindow* pWnd){}
    //~IInputController
private:
    const int m_x = X; 
    const int m_y = Y;
    const int m_pkey = PK;
    const int m_rkey = RK;
};



