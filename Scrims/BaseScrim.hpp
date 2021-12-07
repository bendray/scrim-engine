#pragma once

#include "IGame.hpp"

class CBaseGame :
  public IGame
{
public:
    CBaseGame();
    virtual ~CBaseGame(void);
    //IGame
    virtual Scrim::ICanvas* GetCanvas() override;
    Scrim::IStateManager* GetStateManager() override
    {
        return m_pStates.get();
    }
    int Init() override;
    void Shutdown();

    void Draw() override;
    void Update() override;
    void OnResize(Scrim::IRenderWindow* pWnd) override;
    //~IGame
protected:
    std::unique_ptr<Scrim::StateManager> m_pStates = nullptr;
};
