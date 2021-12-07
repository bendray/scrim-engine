#pragma once

namespace Scrim
{
    class ICanvas;
    class IState
    {
    protected:
        IState& operator=(const IState&) = default;
    public:
        virtual ~IState() = default;
        virtual ICanvas* GetCanvas() = 0;
        virtual const char* GetName() = 0;

        virtual void OnEnter() = 0;
        virtual void OnLeave() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void OnResize(IRenderWindow* wnd) = 0;
        virtual void ProcessCmd(const char* cmd, void* params) = 0;
    };
}
