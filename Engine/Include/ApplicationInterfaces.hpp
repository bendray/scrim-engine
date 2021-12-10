#pragma once

#include "EngineInterfaces.hpp"

namespace Scrim
{
    class Render : public IRender 
    {
    protected:
        Render(const Render&) = default;
        Render& operator=(const Render&) = default;
    public:
        Render();
        ~Render();

        //IRender
        int Load(IRenderWindow*) override;
        void ClearTargets() override;
        int BeginScene() override;
        void EndScene() override;
        void Present() override;
        void TurnZBufferOn() override;
        void TurnZBufferOff() override;
        void OnResize(IRenderWindow* pWnd) override;
        //size_t GetDevice() override;
        //size_t GetDeviceContext() override;
        ModeList GetDisplayModes() override;
        //~IRender
    private:
        RenderImpl* m_pImpl = nullptr;
    };
    class Input : public IInput
    {
    protected:
        Input(const Input&) = default;
        Input& operator=(const Input&) = default;
    public:
        Input();
        ~Input();

        //controller
        int Load(IRenderWindow* pOutput, bool exclusive);
        void CaptureInput();
        void OnResize(IRenderWindow* pWnd);

        //IInputModel
        void AddListener(IInputListener* listener) override;
        void RemoveListener(IInputListener* listener) override;
        void NotifyListeners(EIT type, const EventObject& object) override;
        void on(EIT type, void (*pfn)(EventObject evt), int obj) override;
        void once(EIT type, void (*pfn)(EventObject evt), int obj) override;
        void off(EIT type, void (*pfn)(EventObject evt), int obj) override;
        IInputController* GetController();
        bool GetKeyState(int) const;
        MouseState GetMouseState() const;
        int GetControllerAxisState(int) const;
        int GetControllerButtonState(int) const;
        void SetKeyState(int key, bool state);
        void SetMouseState(const MouseState&& state);
        void SetControllerAxisState(ControllerAxisState&&);
        void SetControllerButtonState(ControllerButtonState&&);
        //~IInputModel
    private:
        InputImpl* m_pImpl = nullptr;
    };
    class StateManager : public IStateManager
    {
   protected:
        StateManager(const StateManager&) = default;
        StateManager& operator=(const StateManager&) = default;
    public:
        StateManager();
        ~StateManager();
        //IStateManager
        void SelectState(const char* name) override;
        template<typename T, typename ... Args>
        void AddState(Args&& ... args)
        {
             auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
             AddState(std::move(ptr));
        }        
        void AddState(std::unique_ptr<IState>&& pState) override;
        IState* GetState() override;
        void Update() override;
        void Draw() override;
        void OnResize(IRenderWindow* pWnd) override;
        void on(EIT type, StateCallback&& callback) override;
        void off(const StateCallback& callback) override;
        //~IStateManager
        //IInputListener
        bool keyPressed(const EventObject& arg) override;
        bool keyReleased(const EventObject& arg) override;
        bool mouseMoved(const EventObject& arg) override;
        bool mousePressed(const EventObject& arg) override;
        bool mouseReleased(const EventObject& arg) override;
        //~IInputListener

    private: 
        StateManagerImpl* m_pImpl = nullptr;
    };
    class Audio : public IAudioManager
    {
    public:
        Audio();
        ~Audio();

        int Load(const char* beep, const char* music) override;
        void Shutdown() override;
        int Beep() const override;
        int PlayMusic() override;
        void PauseMusic() override;
        void ResumeMusic() override;
        void StopMusic() override;
        void Update() override;
    private:
        AudioManagerImpl* m_pImpl = nullptr;
    };

}
