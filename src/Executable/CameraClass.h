#pragma once

class CameraClass : Uncopyable
{
private:
    XMFLOAT4X4 viewMatrix;
    
public:
    CameraClass(_In_ ID3D11DevicePtr Device, _In_ const XMFLOAT3& EyePosition, _In_ const XMFLOAT3& FocusPosition);

    XMMATRIX getViewMatrix();
};
