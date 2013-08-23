#include "stdafx.h"
#include "D3DClass.h"
#include "GameClass.h"

using namespace DirectX;



D3DClass::D3DClass(_In_ HWND WindowHandle,
                   _In_ size_t ScreenWidth, _In_ size_t ScreenHeight, _In_ bool FullScreen,
                   _In_ float YFovAngle, _In_ float ZNearest, _In_ float ZFarthest, _In_ bool VSync)
                   // Store the vsync setting
                   : vSync(VSync)
{
    IDXGIFactoryPtr factory;
    #pragma region Create a DirectX graphics interface factory
    HR_ERROR( CreateDXGIFactory( IID_PPV_ARGS(&factory)) );
    #pragma endregion
    IDXGIAdapterPtr adapter;
    #pragma region Enumerate the primary adapter (video card)
    HR_ERROR( factory->EnumAdapters(0, &adapter) );
    #pragma endregion

    #pragma region Create a device and device context those represent the display adapter
    D3D_FEATURE_LEVEL featureLevel;
    D3D_FEATURE_LEVEL desiredLevelList[] = 
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };
    UINT deviceFlags = 
        #ifdef _DEBUG
        D3D11_CREATE_DEVICE_DEBUG |
        #endif
        0;
    HR_ERROR( D3D11CreateDevice( adapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr,
        deviceFlags, desiredLevelList, ARRAYSIZE(desiredLevelList), D3D11_SDK_VERSION,
        &device, &featureLevel, &deviceContext ));
    #pragma endregion

    #pragma region Create a swap chain
    // Enumerate the primary adapter ouput (monitor)
    IDXGIOutputPtr adapterOutput;
    HR_ERROR( adapter->EnumOutputs(0, &adapterOutput) );

    // Find the display mode which most closely matches the desired display mode
    DXGI_MODE_DESC displayMode;
    DXGI_MODE_DESC desiredMode = {};
    desiredMode.Width = ScreenWidth;
    desiredMode.Height = ScreenHeight;
    desiredMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desiredMode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desiredMode.Scaling = DXGI_MODE_SCALING_STRETCHED;
    HRESULT hr;
    HR_WARNING( hr = adapterOutput->FindClosestMatchingMode(&desiredMode, &displayMode, device) );
    if ( FAILED(hr) ) displayMode = desiredMode;

    // Create a swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc = displayMode;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = WindowHandle;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = !FullScreen;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;
    HR_ERROR( factory->CreateSwapChain(device, &swapChainDesc, &swapChain) );
    #pragma endregion

    #pragma region Create a render-target view for accessing resource data
    ID3D11Texture2DPtr backBuffer;
    HR_ERROR( swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)) );
    HR_ERROR( device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView) );
    #pragma endregion
    #pragma region Create one texture as a depth-stencil target for the output-merger stage
    D3D11_TEXTURE2D_DESC depthStencilBufferDesc = {};
    depthStencilBufferDesc.Width = ScreenWidth;
    depthStencilBufferDesc.Height = ScreenHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilBufferDesc.SampleDesc.Count = 1;
    depthStencilBufferDesc.SampleDesc.Quality = 0;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;
    HR_ERROR( device->CreateTexture2D(&depthStencilBufferDesc, nullptr, &depthStencilBuffer) );
    #pragma endregion
    #pragma region Create a depth-stencil state object that encapsulates depth-stencil test information for the output-merger stage
    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
    // Set up the description of the z buffer
    depthStencilStateDesc.DepthEnable = true;
    depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
    // Set up the description of the stencil buffer
    depthStencilStateDesc.StencilEnable = true;
    depthStencilStateDesc.StencilReadMask = 0xFF;
    depthStencilStateDesc.StencilWriteMask = 0xFF;
    depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    HR_ERROR( device->CreateDepthStencilState(&depthStencilStateDesc, &depthStencilState) );
    #pragma endregion
    #pragma region Create a depth-stencil view for accessing resource data
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
    depthStencilViewDesc.Format = depthStencilBufferDesc.Format;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;
    depthStencilViewDesc.Flags = 0;
    HR_ERROR( device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView) );
    #pragma endregion
    #pragma region Create a rasterizer state object that tells the rasterizer stage how to behave
    D3D11_RASTERIZER_DESC rasterizerStateDesc = {};
    rasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerStateDesc.CullMode = D3D11_CULL_BACK;
    rasterizerStateDesc.FrontCounterClockwise = true;
    rasterizerStateDesc.DepthBias = 0;
    rasterizerStateDesc.DepthBiasClamp = 0.0f;
    rasterizerStateDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerStateDesc.DepthClipEnable = true;
    rasterizerStateDesc.ScissorEnable = false;
    rasterizerStateDesc.MultisampleEnable = false;
    rasterizerStateDesc.AntialiasedLineEnable = false;
    HR_ERROR( device->CreateRasterizerState(&rasterizerStateDesc, &rasterizerState) );
    #pragma endregion

    
    
    // make projection transform matrix
    XMMATRIX ProjectionMatrix = XMMatrixPerspectiveFovRH(YFovAngle, (float)ScreenWidth/(float)ScreenHeight, ZNearest, ZFarthest);
    XMStoreFloat4x4(&projectionMatrix, ProjectionMatrix);
    // Initialize projectionMatrixBuffer
    D3D11_BUFFER_DESC projectionMatrixBufferDesc = {};
    projectionMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    projectionMatrixBufferDesc.ByteWidth = sizeof(ProjectionMatrix);
    projectionMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    projectionMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    D3D11_SUBRESOURCE_DATA projectionMatrixBufferData = { &ProjectionMatrix };
    HR_ERROR( device->CreateBuffer(&projectionMatrixBufferDesc, &projectionMatrixBufferData, &projectionMatrixBuffer) );



    // Bind the projection matrix buffer to the constant buffer
    ID3D11Buffer* cbufferList[] = { projectionMatrixBuffer };
    deviceContext->VSSetConstantBuffers(2, ARRAYSIZE(cbufferList), cbufferList);
    // Bind the rasterizer state to the rasterizer
    deviceContext->RSSetState(rasterizerState);
    // Bind the viewport to the rasterizer
    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (float)ScreenWidth, (float)ScreenHeight, 0.0f, 1.0f };
    deviceContext->RSSetViewports(1, &viewport);
    // Bind the render target and depth stencil buffer to the output-merger
    ID3D11RenderTargetView* renderTargetViewList[] = { renderTargetView };
    deviceContext->OMSetRenderTargets(ARRAYSIZE(renderTargetViewList), renderTargetViewList, depthStencilView);
    // Bind the depth stencil state to the output-merger
    deviceContext->OMSetDepthStencilState(depthStencilState, 0);
}

D3DClass::~D3DClass(void)
{
    if ( swapChain )
    {
        HR_WARNING_MSG( swapChain->SetFullscreenState(false, nullptr),
            L"releasing the swap chain without setting it windowed mode may cause exception" );
    }
}

void D3DClass::BeginScene()
{
    deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3DClass::EndScene()
{
    HR_WARNING( swapChain->Present( vSync?1:0 , 0 ) );
}

ID3D11DevicePtr D3DClass::getDevice()
{
    return device;
}

ID3D11DeviceContextPtr D3DClass::getDeviceContext()
{
    return deviceContext;
}