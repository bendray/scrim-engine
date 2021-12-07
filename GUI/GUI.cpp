#include "GUI.hpp"
#include "States/StateMain.hpp"
#include "States/StateEdit.hpp"
#include "States/StateButton.hpp"

#include <Debug.hpp>

Scrim::GUI::CGUI* g_pGUI;

namespace Scrim::GUI
{
    CGUI::CGUI(IInput* pInput, IAudioManager* pAudio)
        : m_pAudio(pAudio)
        , m_pInput(pInput)
    {
        Debug::Log() << "creating gui..." << std::endl;

        g_pGUI = this;

        m_vCursor = vec2(-1000.0f, -1000.0f);
    }

    CGUI::~CGUI(void)
    {
        Debug::Log() << "~GUI" << std::endl;
    }

    int CGUI::Init(unsigned int flags)
    {

        Debug::Log() << "GUI::creating canvas..." << std::endl;
        m_pCanvas = std::make_unique<Scrim::Canvas>();
        if(m_pCanvas == nullptr)
        {
            Debug::Log() << "failed to create canvas" << std::endl;
            return 1;
        }
        //2
        m_pSpecialCanvas = std::make_unique<Scrim::Canvas>();
        if(m_pSpecialCanvas == nullptr)
        {
            Debug::Log() << "failed to create canvas 2" << std::endl;
            return 1;
        }

        Debug::Log() << "GUI::creating state manager..." << std::endl;

        m_pStates = std::make_unique<Scrim::StateManager>();
        if(m_pStates == nullptr)
        {
            Debug::Log() << "failed to create state manager" << std::endl;
            return 1;
        }

        Debug::Log() << "GUI::add input listener..." << std::endl;

        GetInput()->AddListener(m_pStates.get());

        Debug::Log() << "done." << std::endl;

        Debug::Log() << "GUI::creating state..." << std::endl;

        m_pStates->AddState(std::make_unique<StateMain>(String("main"), m_pCanvas.get()));

        m_pStates->SelectState("main");

        //2

        m_pControlStates = std::make_unique<Scrim::StateManager>();
        if(m_pControlStates == nullptr)
        {
            Debug::Log() << "failed to create state manager 2" << std::endl;
            return 1;
        }

        Debug::Log() << "GUI::add input listener 2..." << std::endl;

        GetInput()->AddListener(m_pControlStates.get());

        Debug::Log() << "done." << std::endl;

        m_pControlStates->AddState(std::make_unique<StateButton>(String("button"), m_pCanvas.get()));
        m_pControlStates->AddState(std::make_unique<StateEdit>(String("edit"), m_pCanvas.get()));
        m_pControlStates->SelectState("button");

        return 0;
    }

    void CGUI::Draw()
    {
        m_pStates->Draw();
        m_pControlStates->Draw();
    }

    void CGUI::Update()
    {
        m_pStates->Update();
        m_pControlStates->Update();
    }

    void CGUI::OnResize(IRenderWindow* pWnd)
    {
    }

    Label_ptr CGUI::Label(const char* text, unsigned int x, unsigned int y, unsigned int size) 
    {
        //create label attach
        std::shared_ptr<CLabel> pLabel = std::make_shared<CLabel>(m_pCanvas.get());
        pLabel->SetLabel(text, x, y, size);
        //m_widgets.push_back(pLabel);

        return pLabel;
    }

    Button_ptr CGUI::Button(const char* text, unsigned int x, unsigned int y, unsigned int size) 
    {
        std::shared_ptr<CButton> pButton = std::make_shared<CButton>(m_pCanvas.get(), m_pSpecialCanvas.get());
        pButton->SetButton(text, x, y, size);
        //m_widgets.push_back(pButton);

        return pButton;
    }

    void CGUI::Dispose(Label_ptr ptr) 
    {
        //m_widgets.clear();
    }

    Button_ptr CGUI::Pick(float x, float y)
    {
        ISprite2D* pObj = m_pSpecialCanvas->Pick(x, y);
        if(pObj != nullptr)
        {
            GetAudioManager()->Beep();
        }
        return nullptr;
    }
    
}
