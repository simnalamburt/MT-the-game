#pragma once

#pragma region windows header
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma endregion
#pragma region DX header
// Direct3D11
#pragma comment ( lib, "dxgi.lib" )
#pragma comment ( lib, "d3d11.lib" )
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

// DirectXMath
#include <DirectXMath.h>
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;
using DirectX::XMFLOAT4X4;

// _com_ptr_t
#include <comdef.h>
#define COM_SMARTPTR_TYPEDEF(T) _COM_SMARTPTR_TYPEDEF( T, __uuidof(T) )
COM_SMARTPTR_TYPEDEF( IDXGIFactory );
COM_SMARTPTR_TYPEDEF( IDXGIAdapter );
COM_SMARTPTR_TYPEDEF( IDXGIOutput );
COM_SMARTPTR_TYPEDEF( ID3D11Device );
COM_SMARTPTR_TYPEDEF( ID3D11DeviceContext );
COM_SMARTPTR_TYPEDEF( IDXGISwapChain );
COM_SMARTPTR_TYPEDEF( ID3D11RenderTargetView );
COM_SMARTPTR_TYPEDEF( ID3D11Texture2D );
COM_SMARTPTR_TYPEDEF( ID3D11DepthStencilState );
COM_SMARTPTR_TYPEDEF( ID3D11DepthStencilView );
COM_SMARTPTR_TYPEDEF( ID3D11RasterizerState );

COM_SMARTPTR_TYPEDEF( ID3D11Buffer );

COM_SMARTPTR_TYPEDEF( ID3D11VertexShader );
COM_SMARTPTR_TYPEDEF( ID3D11PixelShader );
COM_SMARTPTR_TYPEDEF( ID3D11InputLayout );
COM_SMARTPTR_TYPEDEF( ID3D11SamplerState );

COM_SMARTPTR_TYPEDEF( ID3D11ShaderResourceView );

#pragma endregion
#pragma region C++ header
// smart pointers
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

// etc
#include <string>
#include <exception>
#pragma endregion
#pragma region User-defined header
// Core
#include "ErrorReporter.h"
#include "Uncopyable.h"

// DirectXTK
#include "DDSTextureLoader.h"
#include "Effects.h"
#include "Model.h"
using DirectX::Model;
#pragma endregion