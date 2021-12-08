#pragma once

#include <ScrimEngine.hpp>

#include <sstream>

class CBaseState : public Scrim::IState
{
public:
    CBaseState(const char* name, Scrim::ICanvas* pCanvas)
    {
        stateName = name;
        m_pCanvas = pCanvas;
    }
    virtual ~CBaseState() = default;
    virtual Scrim::ICanvas* GetCanvas()
    {
        return m_pCanvas;
    }
    const char* GetName()
    {
        return stateName;
    }
    virtual void OnEnter() = 0;
    virtual void OnLeave() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void OnResize(Scrim::IRenderWindow* wnd) = 0;
    virtual void ProcessCmd(const char* cmd, void* params) = 0;
protected:

    Scrim::StateCallback BindStateCallback(Scrim::StateCallbackFunc func, Scrim::IState* pState, Scrim::String mark)
    {
        return Scrim::StateCallback(func, pState, std::move(mark));
    }

    template<class T>
    void on(T* pState, void (T::*method)(Scrim::EventObject), Scrim::IStateManager* pStateManager, Scrim::EIT type)
    {
        std::ostringstream mark;
        mark << "_" << pState << "_" << reinterpret_cast<void*>(method);
        Scrim::StateCallbackFunc func = std::bind(method, pState, std::placeholders::_1);
        if(pStateManager)
            pStateManager->on(type, BindStateCallback(func, pState, mark.str()));
    }
    template<class T>
    void off(T* pState, void (T::*method)(Scrim::EventObject), Scrim::IStateManager* pStateManager)
    {
        std::ostringstream mark;
        mark << "_" << pState << "_" << reinterpret_cast<void*>(method); 
        Scrim::StateCallbackFunc func = std::bind(method, pState, std::placeholders::_1);
        if(pStateManager)
            pStateManager->off(BindStateCallback(func, pState, mark.str())); 
    }
    template<class T>
    void once(T* pState, void (T::*method)(Scrim::EventObject), Scrim::IStateManager* pStateManager, Scrim::EIT type)
    {
        on(pState, method, pStateManager, type);
        std::function<void(Scrim::EventObject)> helper; 
        std::ostringstream mark;
        mark << "anon_" << type << "_" << pState << "_" << reinterpret_cast<void*>(method);
        Scrim::String markstr = mark.str(); 
        helper = [=](Scrim::EventObject) -> void {
            off(pState, method, pStateManager);
            if(pStateManager)
                pStateManager->off(BindStateCallback(helper, pState, markstr));
        };
        if(pStateManager)
            pStateManager->on(type, BindStateCallback(helper, pState, markstr));
    }

protected:
    const char* stateName;
    Scrim::ICanvas* m_pCanvas;
};
