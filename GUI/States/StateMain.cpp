#include "StateMain.hpp"

#include <Debug.hpp>

using namespace Scrim;

StateMain::StateMain(const String& name, ICanvas* pCanvas): 
   bEnabled(false)
{
    stateName = name;
    m_pCanvas = pCanvas;

    ITile2D* stub = (ITile2D*)0xBADC0DE; //CreateTileTexture2D("unknownbutwillcheckeranyway.tga", 0.0f, 0.0f, 1.0f, 1.0f); 
    stub->SetSize(0.0f, 0.0f);
    m_pCanvas->AttachObject(stub);

    picked = nullptr;
}

StateMain::~StateMain()
{

}

ICanvas* StateMain::GetCanvas()
{
    return m_pCanvas;
}

void StateMain::OnEnter()
{ 
    Debug::Log() << "Entered : " << stateName.c_str() << std::endl;
    pStateLabel = g_pGUI->Label(stateName.c_str(), 50, 10, 16);
}

void StateMain::OnLeave()
{
    Debug::Log() << "Leave : " << stateName.c_str() << std::endl;
    pStateLabel = nullptr;
}

void StateMain::Update()
{
}

void StateMain::Draw()
{
    //GUI::Label_ptr pStateLabel = g_pGUI->Label(stateName.c_str(), 50, 10, 16);
    if(m_pCanvas)
        m_pCanvas->Draw();
}

void StateMain::ProcessCmd(const char* cmd, void* params)
{
}

void StateMain::OnResize(IRenderWindow* wnd)
{
}

bool StateMain::keyPressed(const EventObject& evt)
{ 
    auto arg = std::get<KeyboardEventType>(evt);
/*
    switch (arg.keyId)
    {
            
    case OIS::KC_LEFT:
        break;
    case OIS::KC_RIGHT:
        break;
    case OIS::KC_UP:
        break;
    case OIS::KC_DOWN:
        break;
    case OIS::KC_NUMPAD2:
        break;
    case OIS::KC_NUMPAD8:
        break;
    case OIS::KC_NUMPAD4:
        break;
    case OIS::KC_NUMPAD6:
        break;
    case OIS::KC_DELETE:
        break;
    case OIS::KC_SPACE:
        break;
    }
*/
    return true;

}

bool StateMain::keyReleased(const EventObject& evt)
{
    /* 
    switch(arg.key){
    case OIS::KC_LEFT:
        break;
    case OIS::KC_RIGHT:
        break;
    case OIS::KC_UP:
        break;
    case OIS::KC_DOWN:
        break;
    case OIS::KC_NUMPAD2:
        break;
    case OIS::KC_NUMPAD8:
        break;
    case OIS::KC_NUMPAD4:
        break;
    case OIS::KC_NUMPAD6:
        break;
    case OIS::KC_SPACE:
        break;
    }
    */
    return true;

}

bool StateMain::mouseMoved(const EventObject& evt)
{ 
    return true;
}

bool StateMain::mousePressed(const EventObject& evt)
{
    return true;
}

bool StateMain::mouseReleased(const EventObject& evt)
{
    auto arg = std::get<MouseEventType>(evt);
    /*
    ISprite2D* obj = GetCanvas()->Pick((float)arg.state.X.abs, (float)arg.state.Y.abs);
    if(obj != NULL)
    {
        if(picked == nullptr)
        {
            picked = CreateObject2D("blue.tga", 6.0f, 3.0f, 8.0f, 16.0f);
    
            picked->GetSprite()->SetPos(obj->GetPosX() + 20.0f, obj->GetPosY() + 64.0f - 24.0f, 0);
    
            picked->SetScale(1.0f, 2.0f);
    
            m_pCanvas->AttachObject(picked);
        }
    }
    else
    {
        if(picked)
        {
            m_pCanvas->DetachObject(picked);
            picked = nullptr;
        }
    }
    */
    /*
    ISprite2D* pObj = GetCanvas()->Pick((float)arg.state.X.abs, (float)arg.state.Y.abs);
    if(pObj != NULL) //todo: get label
    {
        g_pGUI->SetCursorPos(pObj->GetPosX()+6.0f, pObj->GetPosY()); //get label char edge
        g_pGUI->GetStateMgr()->SelectState("edit");
    }
    */

    GUI::Button_ptr pObj = g_pGUI->Pick((float)arg.x, (float)arg.y);
    if(pObj != nullptr)
    {
        //g_pGUI->SetCursorPos(pObj->GetPosX()+6.0f, pObj->GetPosY()); //get label char edge

        //g_pGUI->GetStateMgr()->SelectState("edit");
        //pObj->SetLabel("dddd", 50, 50, 16);
    }
    return true;
}
