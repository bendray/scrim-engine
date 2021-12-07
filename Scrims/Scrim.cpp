#include "Scrim.hpp"
#include "States/StateScene.hpp"

#include <Debug.hpp>

CGame::CGame() : CBaseGame() 
{
}

int CGame::Init() 
{
    int error =  CBaseGame::Init();
    if (error)
    {
        return error;
    }

    Scrim::Debug::Log() << "Creating canvas..." << std::endl;
    m_pMainCanvas = std::make_unique<Scrim::Canvas>();
    if(!m_pMainCanvas)
        Scrim::Debug::Log() << "Failed to create canvas." << std::endl;

    Scrim::Debug::Log() << "Creating states..." << std::endl;

    m_pStates->AddState<StateScene>("scene", m_pMainCanvas.get());

    m_pStates->SelectState("scene");

    return 0;
}

CGame::~CGame(void)
{
    Scrim::Debug::Log() << "~Game" << std::endl;
}

void CGame::Play(void)
{
}

void CGame::Stop(void)
{
}
