#pragma once

#if defined(WIN32)|defined(_WIN32)|defined(__NT__)|defined(__WINDOWS__)|defined(__WINDOWS_386__)
#ifdef GAMELIBRARY_EXPORTS
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif
#else //Unix-like
#define GAME_API
#endif //WIN32

#include "BaseScrim.hpp"

class GAME_API CGame : public CBaseGame
{
public:
    CGame();
    ~CGame(void);
    int Init();

    void Play();
    void Stop();

private:
    std::unique_ptr<Scrim::Canvas> m_pMainCanvas = nullptr;
};

typedef CGame Game;

