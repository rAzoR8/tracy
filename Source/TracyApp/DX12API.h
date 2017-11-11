#ifndef TRACY_DX12API_H
#define TRACY_DX12API_H

#if defined(WIN32) || defined(_WIN32)
// Windows
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

// D3D12
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")
// DXGI 1.6
#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")
// D3DCompiler
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#endif // !defined(WIN32) || defined(_WIN32)

#endif // !TRACY_DX12API_H

