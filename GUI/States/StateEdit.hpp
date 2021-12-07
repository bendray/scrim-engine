#pragma once

#include <EngineInterfaces.hpp>

class StateEdit: public Scrim::IState, public Scrim::IInputListener
{
public:
    StateEdit(const Scrim::String& name, Scrim::ICanvas* pCanvas);
    ~StateEdit();

    Scrim::ICanvas* GetCanvas();
    const char* GetName() override
    {
        return stateName.c_str();
    }

    void OnEnter() override;
    void OnLeave() override;
    void Update() override;
    void Draw() override;
    void ProcessCmd(const char* cmd, void* params) override;
    void OnResize(Scrim::IRenderWindow* pWnd) override;

    using EventObject = Scrim::EventObject;
    bool keyPressed(const EventObject& arg) override;
    bool keyReleased(const EventObject& arg) override;
    bool mouseMoved(const EventObject& arg) override;
    bool mousePressed(const EventObject& arg) override;
    bool mouseReleased(const EventObject& arg) override;
protected:
    Scrim::String stateName;
    Scrim::ICanvas* m_pCanvas;
private: 
    bool bEnabled;
    unsigned int m_frame;
    Scrim::ITile2D* m_pCursorSprite;
};
