#pragma once

#include <ScrimEngine.hpp>

template<int X,int Y, int K>
class InputControllerStub : public IInputController
{
public:
    InputControllerStub() = default;
    ~InputControllerStub() = default;
    //IInputController
    int Load(IInputModel* pInput, IRenderWindow* pOutput, bool exclusive)
    {
            SetModel(pInput);
            return true;
    }
    void CaptureInput()
    {
            SetKeyState(m_key, true);
            SetMouseState(MouseState{0,m_x,m_y});
    }
    void OnResize(IRenderWindow* pWnd){}
    //~IInputController
private:
    const int m_x = X; 
    const int m_y = Y;
    const int m_key = K;
};



