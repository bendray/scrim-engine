#include "BaseScrim.hpp"

#include "Application.hpp"

#include <Debug.hpp>

CBaseGame::CBaseGame() 
{
}

CBaseGame::~CBaseGame(void)
{
    Application::GetInput()->RemoveListener(m_pStates.get());
    Scrim::Debug::Log() << "~BaseGame" << std::endl;
}

int CBaseGame::Init()
{
    Scrim::Debug::Log() << "Creating state manager..." << std::endl;
    m_pStates = std::make_unique<Scrim::StateManager>();
    if(m_pStates == nullptr)
    {
        Scrim::Debug::Log() << "Error while creating state manager" << std::endl;
        return 1;
    }
    Scrim::Debug::Log() << "Adding input listener..." << std::endl;
    Application::GetInput()->AddListener(m_pStates.get());
    Scrim::Debug::Log() << "done." << std::endl;
    return 0;
}

void CBaseGame::Shutdown()
{
}

Scrim::ICanvas* CBaseGame::GetCanvas()
{
    return Application::GetStateManager()->GetState()->GetCanvas();
}

void CBaseGame::Draw()
{
    m_pStates->Draw();
}

void CBaseGame::Update()
{
    m_pStates->Update();
}

void CBaseGame::OnResize(Scrim::IRenderWindow* pWnd)
{
    m_pStates->OnResize(pWnd);
}
