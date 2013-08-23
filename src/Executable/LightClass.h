#pragma once

class LightClass
{
private:
    XMFLOAT4 lightColor;
    XMFLOAT3 lightDirection;
    ID3D11BufferPtr lightBuffer;

public:
    LightClass(_In_ ID3D11DevicePtr Device, _In_ const XMFLOAT4& LightColor, _In_ const XMFLOAT3& LightDirection);

    void onLoad(_In_ ID3D11DeviceContextPtr DeviceContext);
};

