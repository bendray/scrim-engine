#pragma once

#include <EngineInterfaces.hpp>

class CButton;

class StateButton: public Scrim::IState, public Scrim::IInputListener
{
public:
    StateButton(const Scrim::String& name, Scrim::ICanvas* pCanvas);
    ~StateButton();

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
    bool keyPressed(const EventObject& event) override;
    bool keyReleased(const EventObject& event) override;
    bool mouseMoved(const EventObject& event) override;
    bool mousePressed(const EventObject& event) override;
    bool mouseReleased(const EventObject& event) override;
protected:
    Scrim::String stateName;
    Scrim::ICanvas* m_pCanvas;
private:
    bool bEnabled;
    CButton* m_pInstance;
};
