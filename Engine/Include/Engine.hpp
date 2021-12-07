#pragma once

#include "EngineInterfaces.hpp"

namespace Scrim
{
    class Canvas : public ICanvas
    {
    public:
        //ICanvas
        Canvas(void);
        ~Canvas(void);
        void AttachObject(ITile2D* Object) override;
        void AttachObject(ILine2D* Object) override;
        void DetachObject(ITile2D* Object) override;
        void DetachObject(ILine2D* Object) override;
        ISprite2D* Pick(float x, float y) override;
        bool Raycast2D(const vec3& ray_origin, const vec3& ray_dir, RayHit& hit) override;
        void Move(int x, int y) override;
        void OnEnable() override;
        void OnDisable() override;
        void Update() override;
        void Draw() override;
        void OnResize(IRenderWindow* pWnd) override;
        //~ICanvas
    private:
        CanvasImpl* pImpl;
    };
}

