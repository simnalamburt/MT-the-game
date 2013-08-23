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

    shader ( new ShaderClass(d3d->getDevice()) ),
    model ( new ModelClass(d3d->getDevice()) ), 
    camera ( new CameraClass(d3d->getDevice(), XMFLOAT3(-1.0f, 0.5f, -2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f)) ),
    light ( new LightClass(d3d->getDevice(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.70710678118654752440084436210485f, 0.0f, 0.70710678118654752440084436210485f)) )
{
    shader->onLoad(d3d->getDeviceContext());
    camera->onLoad(d3d->getDeviceContext());
    light->onLoad(d3d->getDeviceContext());
}



void GameClass::onFrame(double elapsed)
{
}

void GameClass::onDraw()
{
    // Clear the buffer to begin the scene
    d3d->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

    model->onRender(d3d->getDeviceContext());

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