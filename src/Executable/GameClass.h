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

    unique_ptr<Model> gun;
    unique_ptr<Model> pilliar;

public:
    static const float YFovAngle;
    static const float ZNearest;
    static const float ZFarthest;
    static const bool VSync;

public:
    GameClass(HWND WindowHandle, size_t ScreenWidth, size_t ScreenHeight, bool FullScreen);

    void onFrame(double elapsed);
    void onDraw();
    void onKeyDown(char vkey);
    void onKeyUp(char vkey);
};