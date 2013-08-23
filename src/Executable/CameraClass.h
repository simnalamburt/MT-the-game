#pragma once

class CameraClass : Uncopyable
{
private:
    XMFLOAT4X4 viewMatrix;
    ID3D11BufferPtr viewMatrixBuffer;

public:
    CameraClass(_In_ ID3D11DevicePtr Device, _In_ const XMFLOAT3& EyePosition, _In_ const XMFLOAT3& FocusPosition);

    void onLoad(_In_ ID3D11DeviceContextPtr DeviceContext);
};

