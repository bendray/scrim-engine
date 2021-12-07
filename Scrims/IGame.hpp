#pragma once

#include <ScrimEngine.hpp>

class IGame
{
public:
    virtual ~IGame() = default;
    virtual Scrim::ICanvas* GetCanvas() = 0;
    virtual Scrim::IStateManager* GetStateManager() = 0;
    virtual int Init() = 0;
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void OnResize(Scrim::IRenderWindow* wnd) = 0;
};
