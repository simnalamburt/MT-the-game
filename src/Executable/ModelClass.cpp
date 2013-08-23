#include "stdafx.h"
#include "ModelClass.h"

using namespace DirectX;



// Hard-coded data
struct { XMVECTOR position; XMFLOAT2 tex; XMFLOAT3 normal; } vertices[] =
{
    { XMVectorSet(1.0f,0.0f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
    { XMVectorSet(0.5f,0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
    { XMVectorSet(-0.5f,0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
    { XMVectorSet(-1.0f,0.0f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
    { XMVectorSet(-0.5f,-0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
    { XMVectorSet(0.5f,-0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
    { XMVectorSet(1.0f,0.0f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
    { XMVectorSet(0.5f,0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
    { XMVectorSet(-0.5f,0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
    { XMVectorSet(-1.0f,0.0f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
    { XMVectorSet(-0.5f,-0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
    { XMVectorSet(0.5f,-0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
    { XMVectorSet(1.0f,0.0f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(0.5f,0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(1.0f,0.0f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(0.5f,0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(0.5f,0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
    { XMVectorSet(-0.5f,0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
    { XMVectorSet(0.5f,0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
    { XMVectorSet(-0.5f,0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
    { XMVectorSet(-0.5f,0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(-0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(-1.0f,0.0f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(-0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(-0.5f,0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(-0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(-1.0f,0.0f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(-0.866025403784f,0.5f,0.0f) },
    { XMVectorSet(-1.0f,0.0f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(-0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(-0.5f,-0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(-0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(-1.0f,0.0f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(-0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(-0.5f,-0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(-0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(-0.5f,-0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
    { XMVectorSet(0.5f,-0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
    { XMVectorSet(-0.5f,-0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
    { XMVectorSet(0.5f,-0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
    { XMVectorSet(0.5f,-0.866025403784f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(1.0f,0.0f,0.0f,1.0f), XMFLOAT2(0.5f,0.0f), XMFLOAT3(0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(0.5f,-0.866025403784f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.866025403784f,-0.5f,0.0f) },
    { XMVectorSet(1.0f,0.0f,0.2f,1.0f), XMFLOAT2(0.5f,1.0f), XMFLOAT3(0.866025403784f,-0.5f,0.0f) },
};
UINT32 indices[] =
{
    1,0,5,
    2,1,5,
    4,2,5,
    3,2,4,
    6,7,11,
    7,8,11,
    8,10,11,
    8,9,10,
    12,13,14,
    13,15,14,
    16,17,18,
    17,19,18,
    20,21,22,
    21,23,22,
    24,25,26,
    25,27,26,
    28,29,30,
    29,31,30,
    32,33,34,
    33,35,34,
};

const wchar_t* textureFileName = L"Assets/texture.dds";



ModelClass::ModelClass(ID3D11DevicePtr Device)
{
    // Initialize vertexBuffer
    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.StructureByteStride = sizeof(vertices[0]);
    D3D11_SUBRESOURCE_DATA vertexData = { vertices };
    HR_ERROR( Device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer) );

    // Initialize indexBuffer
    D3D11_BUFFER_DESC indexBufferDesc = {};
    indexBufferDesc.ByteWidth = sizeof(indices);
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.StructureByteStride = sizeof(indices[0]);
    D3D11_SUBRESOURCE_DATA indexData = { indices };
    HR_ERROR( Device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer) );



    // Load the texture for this model
    HR_ERROR( CreateDDSTextureFromFile(Device, textureFileName, nullptr, &textureView) );



    // make world transform matrix
    XMMATRIX WorldMatrix = XMMatrixIdentity();
    XMStoreFloat4x4(&worldMatrix, WorldMatrix);
    // Initialize worldMatrixBuffer
    D3D11_BUFFER_DESC worldMatrixBufferDesc = {};
    worldMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    worldMatrixBufferDesc.ByteWidth = sizeof(WorldMatrix);
    worldMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    worldMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    D3D11_SUBRESOURCE_DATA worldMatrixBufferData = { &WorldMatrix };
    HR_ERROR( Device->CreateBuffer(&worldMatrixBufferDesc, &worldMatrixBufferData, &worldMatrixBuffer) );
}

void ModelClass::onRender(ID3D11DeviceContextPtr DeviceContext)
{
    UINT stride = sizeof(vertices[0]);
    UINT offset = 0;

    // Bind a vertex buffer to the input-assembler
    ID3D11Buffer* vertexBufferList[] = { vertexBuffer };
    DeviceContext->IASetVertexBuffers(0, ARRAYSIZE(vertexBufferList), vertexBufferList, &stride, &offset);
    // Bind a index buffer to the input-assembler
    DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, offset);
    // Bind information about the primitve type, and data order which describes input data for the input-assembler
    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Bind world matrix to the constant buffer of vertex shader
    ID3D11Buffer* cbufferList[] = { worldMatrixBuffer };
    DeviceContext->VSSetConstantBuffers(0, ARRAYSIZE(cbufferList), cbufferList);

    // Bind texture to the pixel shader
    ID3D11ShaderResourceView* textureViewList[] = { textureView };
    DeviceContext->PSSetShaderResources(0, ARRAYSIZE(textureViewList), textureViewList);

    // Draw object
    DeviceContext->DrawIndexed(ARRAYSIZE(indices), 0, 0);
}
