#include "stdafx.h"
#include "CameraClass.h"

using namespace DirectX;

CameraClass::CameraClass(ID3D11DevicePtr Device, const XMFLOAT3& EyePosition, const XMFLOAT3& FocusPosition)
{
    // Make view transform matrix
    XMMATRIX ViewMatrix = XMMatrixLookAtRH(XMLoadFloat3(&EyePosition), XMLoadFloat3(&FocusPosition), XMVectorSet(0, 0, 1, 1) );
    XMStoreFloat4x4(&viewMatrix, ViewMatrix);
}

XMMATRIX CameraClass::getViewMatrix()
{
    return XMLoadFloat4x4(&viewMatrix);
}