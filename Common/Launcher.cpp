#include <Application.hpp>
#include "Launcher.hpp"
//Common engine header
#include <enums.hpp>
//end common engine header
#include <Scrim.hpp>
#include <Debug.hpp>

#include <ctime>

#if defined(_WIN32) || defined(_WIN64)
#include "../Win/Launcher/RenderWindow.hpp"
#elif defined(__linux__)
#include "../Linux/Launcher/RenderWindow.hpp"
#endif

using namespace Scrim;

bool CLauncher::Load()
{
    int error = 1;

    std::time_t t = std::time(nullptr); 

    std::tm* tm = std::localtime(&t);

    Debug::Log() << std::endl << std::endl << std::setfill('-') << std::setw(49) << '-' << std::endl; 
    Debug::Log() << std::put_time(tm, "%c") << std::endl;

    Debug::Log() << std::setfill('-') << std::setw(49) << '-' << std::endl;

    Application::output = std::make_unique<RenderWindow>();
    if(!Application::output) return false;

    Application::output->SetSize(640, 480);

    Application::render = std::make_unique<Scrim::Render>();
    if(!Application::render) return false;
    error = Application::render->Load(Application::output.get());
    if(error)
    {
        Debug::Log() << "Unable to create device! (" << error << ")";
        return false;
    }

    Application::audio = std::make_unique<Scrim::Audio>();
    if(!Application::audio) return false;
    error = Application::audio->Load("Audio/Beep.wav", "Audio/Music.mp3"); 
    if(error)
    {
        Debug::Log() << "Unable to create audio device! (" << error << ")";
        return false;
    }

    Application::input = std::make_unique<Scrim::Input>();
    if(!Application::input) return false;
    error = Application::input->Load(Application::output.get(), false); // set window && !fullscreen;
    if(error)
    {
        Debug::Log() << "Unable to create input! (" << error << ")";
        return false;
    }

    Application::gui = std::make_unique<Scrim::GUI::CGUI>(
                    Application::input.get(),
                    Application::audio.get());

    if(!Application::gui) return false;
    error = Application::gui->Init(1);
    if(error)
    {
        Debug::Log() << "Unable to create GUI (" << error << ")";
        return false;
    }

    Application::game = std::make_unique<CGame>();
    if(!Application::game) return false;
    error = Application::game->Init();
    if(error)
    {
        Debug::Log() << "Unable to create game! (" << error << ")";
        return false;
    }

    //if we are here, we may call resize methods.
    Application::output->Event_SwitchFullscreen += NewDelegate(Application::render.get(), &IRender::OnResize);
    Application::output->Event_Resize += [](IRenderWindow* wnd){
        Application::render->OnResize(wnd);
        Application::game->OnResize(wnd);
        Application::gui->OnResize(wnd);
        Application::input->OnResize(wnd);
    };
    Application::output->Event_Quit += []()
    {
        Application::Exit();
    };

    m_updateCounter = 0;
    m_frameCounter = 0;
    m_framesPerSecondCounter = 0;
    m_elapsedFrames = 0;
    m_elapsedTime = 0;


    return true;
}

int CLauncher::Run()
{
    m_elapsedFrames = 0;
    m_elapsedTime = clock();
    Debug::Log() << "run\n";

    while(Application::bRunning)
    {
        Application::input->CaptureInput();
        Application::render->ClearTargets();
        if(AE_OK == Application::render->BeginScene())
        {
            int start = clock();
            Application::game->Update();
            int stop = clock() - start;
            m_updateCounter += stop;

            start = clock();
            Application::game->Draw();
            stop = clock() - start;
            m_frameCounter += stop;

            Application::render->EndScene();
            Application::render->Present();

            Application::audio->Update();
            m_elapsedFrames++;
            if(clock() > m_elapsedTime + 1000)
            {
                m_elapsedTime = clock();
                m_framesPerSecondCounter = m_elapsedFrames;
                m_elapsedFrames = 0;
                //Debug::Log() << m_framesPerSecondCounter << std::endl;
            }
        }
        Application::output->Update();
    }
    
    Cleanup();
    return AE_OK;
}

int CLauncher::Execute()
{
        if(Load())
        {
                return Run();
        }
        return 0;
}

void CLauncher::Cleanup()
{
    Application::audio->Shutdown();
}
