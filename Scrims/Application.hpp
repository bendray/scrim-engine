#pragma once

#include <ScrimEngine.hpp>
#include <Scrim.hpp>
#include <GUI.hpp>

#if defined(_WIN32) | defined(_WIN64)
  #ifdef GAMELIBRARY_EXPORTS
    #define GAME_API __declspec(dllexport)
  #else
    #define GAME_API __declspec(dllimport)
  #endif
#else
  #define GAME_API
#endif

class CLauncher;

class GAME_API Application 
{
    friend class CLauncher;
public:
    Application() = default;
    Application(Application &other) = delete;
    void operator=(const Application &other) = delete;
    ~Application() = default;
    static Scrim::IAudioManager* GetAudioManager()
    {
        return audio.get();
    }
    static Scrim::GUI::IGUI* GetGUI()
    {
        return gui.get();
    }
    static Scrim::IRender* GetRender()
    {
        return render.get();
    }
    static Scrim::IRenderWindow* GetOutput()
    {
        return output.get();
    }
    static Scrim::IInput* GetInput()
    {
        return input.get();
    }
    static Scrim::IStateManager* GetStateManager()
    {
        return game->GetStateManager();
    }
protected:
    static std::unique_ptr<Scrim::Input> input;
    static std::unique_ptr<Scrim::IRender> render;
    static std::unique_ptr<Scrim::Audio> audio;
    static std::unique_ptr<Scrim::GUI::CGUI> gui;
    static std::unique_ptr<Scrim::IRenderWindow> output;
    static std::unique_ptr<CGame> game;
    static bool bRunning;
protected:
    static void OnResize(Scrim::IRenderWindow* wnd);
    static void Exit();
};
