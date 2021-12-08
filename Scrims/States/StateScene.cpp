#include "Application.hpp"
#include "StateScene.hpp"

#include <Debug.hpp>

using namespace Scrim;

StateScene::StateScene(const char* name, ICanvas* pCanvas)
    : CBaseState(name, pCanvas) 
{
	on(this, &StateScene::onKeyPressed, Application::GetStateManager(), Scrim::KEY_PRESS);
}

StateScene::~StateScene()
{
	off(this, &StateScene::onKeyPressed, Application::GetStateManager());
}

void StateScene::OnEnter()
{
    Scrim::Debug::Log() << "Entered: " << stateName << std::endl;
    Application::GetAudioManager()->PlayMusic(); 
}

void StateScene::OnLeave()
{
    Scrim::Debug::Log() << "Leave: " << stateName << std::endl;
    Application::GetAudioManager()->StopMusic(); 
}

void StateScene::Update()
{
}

void StateScene::Draw()
{
    if(m_pCanvas)
        m_pCanvas->Draw();
}

void StateScene::ProcessCmd(const char* cmd, void* params)
{
}

void StateScene::OnResize(IRenderWindow* wnd)
{
}

void StateScene::onKeyPressed(Scrim::EventObject event)
{
	auto arg = std::get<Scrim::KeyboardEventType>(event);
	Debug::Log() << arg.keyId << std::endl;
}
