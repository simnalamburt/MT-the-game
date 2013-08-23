#include "stdafx.h"
#include "ShaderClass.h"

#include "VertexShader.h"
#include "PixelShader.h"


ShaderClass::ShaderClass(_In_ ID3D11DevicePtr Device)
{
    // Initialize vertexShader, pixelShader
    HR_ERROR( Device->CreateVertexShader(VertexShader, sizeof(VertexShader), nullptr, &vertexShader) );
    HR_ERROR( Device->CreatePixelShader(PixelShader, sizeof(PixelShader), nullptr, &pixelShader) );
    
    // Initialize inputLayout
    D3D11_INPUT_ELEMENT_DESC inputElementDescList[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    HR_ERROR( Device->CreateInputLayout(inputElementDescList, ARRAYSIZE(inputElementDescList), VertexShader, sizeof(VertexShader), &inputLayout) );

    // Initialize sampler state
    D3D11_SAMPLER_DESC samplerStateDesc = {};
    samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerStateDesc.MinLOD = -D3D11_FLOAT32_MAX;
    samplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
    samplerStateDesc.MipLODBias = 0.0f;
    HR_ERROR( Device->CreateSamplerState(&samplerStateDesc, &samplerState) );
}

void ShaderClass::onLoad(ID3D11DeviceContextPtr DeviceContext)
{
    // Set the vertex input layout
    DeviceContext->IASetInputLayout(inputLayout);
    
    // Set the vertex and pixel shaders that will be used to render this triangle
    DeviceContext->VSSetShader(vertexShader, nullptr, 0);
    DeviceContext->PSSetShader(pixelShader, nullptr, 0);

    // Set the sampler state
    ID3D11SamplerState* samplerStateList[] = { samplerState };
    DeviceContext->PSSetSamplers(0, ARRAYSIZE(samplerStateList), samplerStateList);
}