#pragma once

#include "BaseState.hpp"

class StateScene: public CBaseState
{
public:
    StateScene(const char* name, Scrim::ICanvas* pCanvas);
    ~StateScene();

    void OnEnter();
    void OnLeave();
    void Update();
    void Draw();
    void ProcessCmd(const char* cmd, void* params);
    void OnResize(Scrim::IRenderWindow* wnd);

};

