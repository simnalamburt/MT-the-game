#pragma once
#include "InputClass.h"
#include "GameClass.h"

class SystemClass : Uncopyable
{
private:
    HINSTANCE instanceHandle;
    size_t width;
    size_t height;
    bool fullscreen;

    HWND windowHandle;
    unique_ptr<InputClass> input;
    unique_ptr<GameClass> game;

public:
    SystemClass(_In_ HINSTANCE InstanceHandle, _In_ size_t Width, _In_ size_t Height, _In_ bool FullScreen);
    ~SystemClass();

    void Run(_In_ int ShowCommand);
    LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
    void onIdle();
};
