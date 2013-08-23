#pragma once
#include "GameClass.h"

class SystemClass : Uncopyable
{
private:
    HINSTANCE instanceHandle;
    bool displaySettingChanged;

    HWND windowHandle;
    unique_ptr<GameClass> game;

    const double freq;
    double last;

public:
    SystemClass(HINSTANCE InstanceHandle, size_t Width, size_t Height, bool FullScreen);
    ~SystemClass();

    void Run(int ShowCommand);
    LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
    void onIdle();
};
