#pragma once

class ShaderClass : Uncopyable
{
private:
    ID3D11VertexShaderPtr vertexShader;
    ID3D11PixelShaderPtr pixelShader;
    
    ID3D11InputLayoutPtr inputLayout;
    ID3D11SamplerStatePtr samplerState;

public:
    ShaderClass(_In_ ID3D11DevicePtr Device);

    void onLoad(_In_ ID3D11DeviceContextPtr DeviceContext);
};
