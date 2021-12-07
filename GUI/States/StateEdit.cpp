#include "StateEdit.hpp"

#include <GUI.hpp> //global variables

#include <Debug.hpp>

using namespace Scrim;

StateEdit::StateEdit(const Scrim::String& name, Scrim::ICanvas* pCanvas): 
    bEnabled(false)
{
    stateName = name;
    m_pCanvas = pCanvas;
    m_pCursorSprite = nullptr;
}

StateEdit::~StateEdit()
{

}

ICanvas* StateEdit::GetCanvas()
{
    return m_pCanvas;
}

void StateEdit::OnEnter()
{ 
    Debug::Log() << "Entered : " << stateName.c_str() << std::endl;
    if(m_pCursorSprite == nullptr)
    {
        m_pCursorSprite = (ITile2D*)0xBADC0DE;//CreateObject2D("font.tga", 586, 0, 1, 12);
        m_pCursorSprite->SetScale(0.04f, 0.3f);
    }
    vec2 curPos = g_pGUI->GetCursorPos();
    m_pCursorSprite->GetSprite()->SetPos(curPos.x, curPos.y, 0);
}

void StateEdit::OnLeave()
{
    Debug::Log() << "Leave : " << stateName.c_str() << std::endl;
    if(m_pCursorSprite != nullptr)
        m_pCanvas->DetachObject(m_pCursorSprite);
}

void StateEdit::Update()
{
    m_frame++;
    if(m_frame > 1000) m_frame = 0;
    if(m_frame % 120 > 60) 
        m_pCanvas->AttachObject(m_pCursorSprite);
    else 
        m_pCanvas->DetachObject(m_pCursorSprite);
}

void StateEdit::Draw()
{
    GUI::Label_ptr pStateLabel = g_pGUI->Label(stateName.c_str(), 50, 30, 16);
    if(m_pCanvas)
        m_pCanvas->Draw();
}

void StateEdit::ProcessCmd(const char* cmd, void* params)
{
}

void StateEdit::OnResize(IRenderWindow* wnd)
{
}

bool StateEdit::keyPressed(const EventObject& evt)
{ 
    return true;
}

bool StateEdit::keyReleased(const EventObject& evt)
{ 
    return true;
}

bool StateEdit::mouseMoved(const EventObject& evt)
{ 
    return true;
}

bool StateEdit::mousePressed(const EventObject& evt)
{
    return true;
}

bool StateEdit::mouseReleased(const EventObject& evt)
{
    return true;
}
