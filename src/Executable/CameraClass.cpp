#include "stdafx.h"
#include "CameraClass.h"

using namespace DirectX;

CameraClass::CameraClass(ID3D11DevicePtr Device, const XMFLOAT3& EyePosition, const XMFLOAT3& FocusPosition)
{
    // Make view transform matrix
    XMMATRIX ViewMatrix = XMMatrixLookAtRH(XMLoadFloat3(&EyePosition), XMLoadFloat3(&FocusPosition), XMVectorSet(0, 0, 1, 1) );
    XMStoreFloat4x4(&viewMatrix, ViewMatrix);


    // Initialize viewMatrixBuffer
    D3D11_BUFFER_DESC viewMatrixBufferDesc = {};
    viewMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    viewMatrixBufferDesc.ByteWidth = sizeof(ViewMatrix);
    viewMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    viewMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    D3D11_SUBRESOURCE_DATA viewMatrixBufferData = { &ViewMatrix };
    HR_ERROR( Device->CreateBuffer(&viewMatrixBufferDesc, &viewMatrixBufferData, &viewMatrixBuffer) );
}

void CameraClass::onLoad(ID3D11DeviceContextPtr DeviceContext)
{
    ID3D11Buffer* cbufferList[] = { viewMatrixBuffer };
    DeviceContext->VSSetConstantBuffers(1, ARRAYSIZE(cbufferList), cbufferList);
}

XMMATRIX CameraClass::getViewMatrix()
{
    return XMLoadFloat4x4(&viewMatrix);
}