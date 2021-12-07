#pragma once

#include <GUI.hpp>

#include <EngineInterfaces.hpp>

class StateMain: public Scrim::IState, public Scrim::IInputListener
{
public:
    StateMain(const Scrim::String& name, Scrim::ICanvas* pCanvas);
    ~StateMain();

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

    Scrim::ITile2D* picked;
    Scrim::GUI::Label_ptr pStateLabel;
};
