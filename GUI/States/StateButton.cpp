#include "StateButton.hpp"

#include <GUI.hpp> //global variables

#include <Debug.hpp>

using namespace Scrim;

StateButton::StateButton(const String& name, ICanvas* pCanvas):
    bEnabled(false)
{
    stateName = name;
    m_pCanvas = pCanvas;
}

StateButton::~StateButton()
{

}

ICanvas* StateButton::GetCanvas()
{
    return m_pCanvas;
}

void StateButton::OnEnter()
{
    Debug::Log() << "Entered : " << stateName.c_str() << std::endl;
}

void StateButton::OnLeave()
{
    Debug::Log() << "Leave : " << stateName.c_str() << std::endl;
}

void StateButton::Update()
{

}

void StateButton::Draw()
{
    GUI::Label_ptr pStateLabel = g_pGUI->Label(stateName.c_str(), 50, 30, 16);
    if(m_pCanvas)
        m_pCanvas->Draw();
}

void StateButton::ProcessCmd(const char* cmd, void* params)
{

}

void StateButton::OnResize(IRenderWindow* wnd)
{

}

bool StateButton::keyPressed(const EventObject& event)
{ 
    return true;
}

bool StateButton::keyReleased(const EventObject& event)
{ 
    return true;

}

bool StateButton::mouseMoved(const EventObject& event)
{ 
    return true;
}

bool StateButton::mousePressed(const EventObject& event)
{
    return true;
}

bool StateButton::mouseReleased(const EventObject& event)
{
    return true;
}
