#pragma once

#include "types.hpp"
#include "IRenderWindow.hpp"
#include "IState.hpp"
#include "StateCallback.hpp"

#include <nv_math\nv_math.h>

namespace Scrim
{
    struct ISprite2D
    {
        ~ISprite2D() = delete;
        void SetPos(float x, float y, float z);
        float GetPosX();
        float GetPosY();
        float GetPosZ();

        float GetRotX();
        float GetRotY();
        float GetRotZ();

        void SetRotX(float deg);
        void SetRotY(float deg);
        void SetRotZ(float deg);

        void SetScaleX(float scale);
        void SetScaleY(float scale);
        void SetScaleZ(float scale);
        void SetScale(float scale);
        void SetScale(float scaleX, float scaleY, float scaleZ);
    };

    struct ITile2D
    {
        ~ITile2D() = delete;
        ISprite2D* GetSprite();
        void SetSize(float w, float h);
        void SetTexCoordsRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        void SetRotZ(float deg);
        void SetScale(float scale);
        void SetScale(float scaleX, float scaleY);
    };

    struct ILine2D
    {
        ~ILine2D() = delete;
        ISprite2D* GetSprite();
        void LinkTo(ILine2D* object);
        void SetEndPoints(float x1, float y1, float x2, float y2);
    };


    struct RayHit
    {
        vec3 point;
        vec3 normal;
        ISprite2D* target;
    };

    class ICanvas
    {
    protected:
        ICanvas& operator=(const ICanvas&) = default;
        virtual ~ICanvas(void) = default;
    public:
        virtual void AttachObject(ITile2D* Object) = 0;
        virtual void AttachObject(ILine2D* Object) = 0;
        virtual void DetachObject(ITile2D* Object) = 0;
        virtual void DetachObject(ILine2D* Object) = 0;
        virtual ISprite2D* Pick(float x, float y) = 0;
        /*
        *  Raycast2D:
        *  ray_origin - position of ray;
        *  ray_dir - direction of ray;
        *  hit - structure which returns result of raycast;
        */
        virtual bool Raycast2D(const vec3& ray_origin, const vec3& ray_dir, RayHit& hit) = 0;
        virtual void Move(int x, int y) = 0;
        virtual void OnEnable() = 0;
        virtual void OnDisable() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void OnResize(IRenderWindow* pWnd) = 0;
    };

    class IInputListener
    {
    protected:
        IInputListener& operator=(const IInputListener&) = default;
        virtual ~IInputListener() = default;
    public:
        virtual bool keyPressed(const EventObject& arg) = 0;
        virtual bool keyReleased(const EventObject& arg) = 0;	
        virtual bool mouseMoved(const EventObject& arg) = 0;
        virtual bool mousePressed(const EventObject& arg) = 0;
        virtual bool mouseReleased( const EventObject &arg) = 0;
    };

    struct MouseState
    {
        uint32_t buttons;
        int x;
        int y;
    };

    using ControllerAxisState = int;
    using ControllerButtonState = int;

    class IInputModel
    {
    protected:
        IInputModel& operator=(const IInputModel&) = default;
        virtual ~IInputModel() = default;
        friend class IInputController;
    public:
        //IInputObservable
        virtual void AddListener(IInputListener* listener) = 0;
        virtual void RemoveListener(IInputListener* listener) = 0;
        virtual void NotifyListeners(EIT type, const EventObject& object) = 0;    
        virtual void on(EIT type, void (*pfn)(EventObject evt), int obj) = 0;
        virtual void once(EIT type, void (*pfn)(EventObject evt), int obj) = 0;
        virtual void off(EIT type, void (*pfn)(EventObject evt), int obj) = 0;
        //~IInputObservable
        virtual bool GetKeyState(int) const = 0;
        virtual MouseState GetMouseState() const = 0;
        virtual int GetControllerAxisState(int) const = 0;
        virtual int GetControllerButtonState(int) const = 0;
    protected:
        virtual void SetKeyState(int key, bool state) = 0;
        virtual void SetMouseState(const MouseState&& state) = 0;
        virtual void SetControllerAxisState(ControllerAxisState&&) = 0;
        virtual void SetControllerButtonState(ControllerButtonState&&) = 0;
    };

    class IInputController
    {
    protected:
        IInputController& operator=(const IInputController&) = default;
    public:
        virtual ~IInputController() = default;
        //IInputController
        virtual int Load(IInputModel* pInput, IRenderWindow* pOutput, bool fullscreen) = 0;
        virtual void CaptureInput() = 0;
        virtual void OnResize(IRenderWindow* pWnd) = 0;
        //~IInputController
        void SetModel(IInputModel* pInput)
        {
            pModel = pInput;
        }
    protected:
        void SetKeyState(int key, bool state)
        {
            pModel->SetKeyState(key, state);
        }
        void SetMouseState(const MouseState&& state)
        {
            pModel->SetMouseState(std::move(state));
        }
        void SetControllerAxisState(ControllerAxisState&& state)
        {
            pModel->SetControllerAxisState(std::move(state));
        }
        void SetControllerButtonState(ControllerButtonState&& state)
        {
            pModel->SetControllerButtonState(std::move(state));
        }
    protected:
        IInputModel* pModel;
    };

    class IInput : public IInputModel
    {
    protected:
        IInput& operator=(const IInput&) = default;
    public:
        ~IInput() = default;
        bool IsKeyPressed(int);
        bool IsKeyReleased(int);
        vec2 GetMousePosition();
        bool IsMouseButtonPressed(int);
        bool IsMouseButtonReleased(int);
        bool IsControllerButtonPressed(int);
        bool IsControllerButtonReleased(int); 
        int  GetControllerAxisPosition(int);
    };

    class IStateManager : public IInputListener
    {
    public:
        virtual ~IStateManager() = default;
        virtual void AddState(std::unique_ptr<IState>&& pState) = 0;
        virtual void SelectState(const char* name) = 0;
        virtual IState* GetState() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void OnResize(IRenderWindow* pWnd) = 0;
        virtual void on(EIT type, StateCallback&& callback) = 0;
        virtual void off(const StateCallback& callback) = 0;
    };

    class IAudioManager 
    {
    public:
        virtual ~IAudioManager() = default;
        virtual int Load(const char* beepSound, const char* music) = 0;
        virtual void Shutdown() = 0;
        virtual int Beep() const = 0;
        virtual int PlayMusic() = 0;
        virtual void PauseMusic() = 0;
        virtual void ResumeMusic() = 0;
        virtual void StopMusic() = 0;
        virtual void Update() = 0;
    };


    typedef std::list<DisplayMode> ModeList;

    class IRender
    {
    protected:
        IRender& operator=(const IRender&) = default;
    public:
        virtual ~IRender() = default;
        EVENT1(RenderEvent, IRender*);
        RenderEvent Event_LostDevice;
        RenderEvent Event_RestoreDevice;
        virtual int Load(IRenderWindow* pWnd) = 0;
        virtual void ClearTargets() = 0;
        virtual int BeginScene() = 0;
        virtual void EndScene() = 0;
        virtual void Present() = 0;
        virtual void TurnZBufferOn() = 0;
        virtual void TurnZBufferOff() = 0;
        virtual void OnResize(IRenderWindow* pWnd) = 0;
        //virtual /*IRenderDevice**/ size_t GetDevice() = 0;
        //virtual /*IRenderContext**/size_t GetDeviceContext() = 0;
        virtual ModeList GetDisplayModes() = 0;
    };
}
