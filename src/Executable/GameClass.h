#pragma once
#include "D3DClass.h"

#include "CameraClass.h"



class GameClass : Uncopyable
{
private:
    unique_ptr<D3DClass> d3d;

    unique_ptr<CameraClass> camera;

    unique_ptr<Model> box;

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