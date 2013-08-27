#include "stdafx.h"
#include "GameClass.h"

using namespace DirectX;



// TODO : 데이터드리븐으로 바꾸기
const float GameClass::YFovAngle = DirectX::XM_PIDIV4;
const float GameClass::ZNearest = 0.001f;
const float GameClass::ZFarthest = 1000.0f;
const bool GameClass::VSync = true;



GameClass::GameClass(_In_ HWND WindowHandle, _In_ size_t ScreenWidth, _In_ size_t ScreenHeight, _In_ bool FullScreen) :
    d3d ( new D3DClass(WindowHandle, ScreenWidth, ScreenHeight, FullScreen, YFovAngle, ZNearest, ZFarthest, VSync) ),

    camera ( new CameraClass(d3d->getDevice(), XMFLOAT3(2.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f)) )
{
}



void GameClass::onFrame(double elapsed)
{
}

void GameClass::onDraw()
{
    CommonStates states(d3d->getDevice());

    // Clear the buffer to begin the scene
    d3d->BeginScene();

    


    // Present the rendered scene to the screen
    d3d->EndScene();
}



void GameClass::onKeyDown(char vkey)
{
    switch (vkey)
    {
    case VK_LEFT:
        return;
    case VK_RIGHT:
        return;
    case VK_UP:
        return;
    case VK_DOWN:
        return;

    case VK_SPACE:
        return;

    default:
        return;
    }
}

void GameClass::onKeyUp(char vkey)
{
    switch (vkey)
    {
    case VK_LEFT:
        return;
    case VK_RIGHT:
        return;
    case VK_UP:
        return;
    case VK_DOWN:
        return;

    default:
        return;
    }
}