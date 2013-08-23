#include "stdafx.h"
#include "LightClass.h"

using namespace DirectX;

LightClass::LightClass(_In_ ID3D11DevicePtr Device, _In_ const XMFLOAT4& LightColor, _In_ const XMFLOAT3& LightDirection)
    : lightColor(LightColor), lightDirection(LightDirection)
{
    // make light data
    struct
    {
        XMVECTOR LightColor;
        XMVECTOR LightDirection;
    } Light = { XMLoadFloat4(&LightColor), XMLoadFloat3(&LightDirection) };


    // initialize lightBuffer
    D3D11_BUFFER_DESC lightBufferDesc = {};
    lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    lightBufferDesc.ByteWidth = sizeof(Light);
    lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    D3D11_SUBRESOURCE_DATA lightBufferData = { &Light };
    HR_ERROR( Device->CreateBuffer(&lightBufferDesc, &lightBufferData, &lightBuffer) );
}

void LightClass::onLoad(_In_ ID3D11DeviceContextPtr DeviceContext)
{
    ID3D11Buffer* cbufferList[] = { lightBuffer };
    DeviceContext->PSSetConstantBuffers(0, ARRAYSIZE(cbufferList), cbufferList);
}
