#pragma once

class ModelClass : Uncopyable
{
private:
    ID3D11BufferPtr vertexBuffer;
    ID3D11BufferPtr indexBuffer;
    
    ID3D11ShaderResourceViewPtr textureView;

    XMFLOAT4X4 worldMatrix;
    ID3D11BufferPtr worldMatrixBuffer;

public:
    ModelClass(_In_ ID3D11DevicePtr Device);
    
    void onRender(_In_ ID3D11DeviceContextPtr DeviceContext);
};
