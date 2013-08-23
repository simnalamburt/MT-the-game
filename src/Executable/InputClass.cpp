#include "stdafx.h"
#include "InputClass.h"

#pragma warning( disable : 4351 )



InputClass::InputClass()
    : VirtualKeyStates()
{
}

void InputClass::KeyDown(int VirtualKey)
{
    VirtualKeyStates[VirtualKey] = true;
}

void InputClass::KeyUp(int VirtualKey)
{
    VirtualKeyStates[VirtualKey] = false;
}

bool InputClass::isKeyDown(int VirtualKey)
{
    return VirtualKeyStates[VirtualKey];
}