#pragma once

class D3DClass : Uncopyable
{
private:
    ID3D11DevicePtr 				device;
    ID3D11DeviceContextPtr 		deviceContext;

    IDXGISwapChainPtr 			swapChain;
    ID3D11RenderTargetViewPtr 	renderTargetView;
    ID3D11Texture2DPtr 			depthStencilBuffer;
    ID3D11DepthStencilStatePtr 	depthStencilState;
    ID3D11DepthStencilViewPtr 	depthStencilView;
    ID3D11RasterizerStatePtr 		rasterizerState;

    const bool vSync;

    XMFLOAT4X4 projectionMatrix;
    ID3D11BufferPtr projectionMatrixBuffer;

public:
    D3DClass(_In_ HWND WindowHandle,
        _In_ size_t ScreenWidth, _In_ size_t ScreenHeight, _In_ bool FullScreen,
        _In_ float YFovAngle, _In_ float ZNearest, _In_ float ZFarthest, _In_ bool VSync);
    ~D3DClass();

    void BeginScene();
    void EndScene();

    ID3D11DevicePtr getDevice();
    ID3D11DeviceContextPtr getDeviceContext();

    XMMATRIX getProjectionMatrix();
};

