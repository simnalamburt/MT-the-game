#pragma once
#include "D3DClass.h"

#include "ShaderClass.h"
#include "ModelClass.h"
#include "CameraClass.h"
#include "LightClass.h"

class GameClass : Uncopyable
{
private:
    unique_ptr<D3DClass> d3d;

    unique_ptr<ShaderClass> shader;
    unique_ptr<ModelClass> model;
    unique_ptr<CameraClass> camera;
    unique_ptr<LightClass> light;

public:
    static const float YFovAngle;
    static const float ZNearest;
    static const float ZFarthest;
    static const bool VSync;

public:
    GameClass(_In_ HWND WindowHandle, _In_ size_t ScreenWidth, _In_ size_t ScreenHeight, _In_ bool FullScreen);

    void onIdle();
};