#include "Application.hpp"

std::unique_ptr<Scrim::IRenderWindow> Application::output = nullptr;
std::unique_ptr<Scrim::IRender> Application::render = nullptr;
std::unique_ptr<Scrim::Audio> Application::audio = nullptr;
std::unique_ptr<Scrim::Input> Application::input = nullptr;
std::unique_ptr<Scrim::GUI::CGUI> Application::gui = nullptr;
std::unique_ptr<CGame> Application::game = nullptr;
bool Application::bRunning = true;

void Application::OnResize(Scrim::IRenderWindow* wnd)
{
    render->OnResize(wnd);
    input->OnResize(wnd);
}

void Application::Exit()
{
    bRunning = false;
}

