#pragma once

// TODO : Where's XInput ??
class InputClass : Uncopyable
{
private:
    bool VirtualKeyStates[256];

public:
    InputClass();

    void KeyDown(int VirtualKey);
    void KeyUp(int VirtualKey);
    bool isKeyDown(int VirtualKey);
};
