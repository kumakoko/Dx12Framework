#ifndef framework_h__
#define framework_h__

#if defined(FRAMEWORK_EXPORTS)
#define DX12_FRAMEWORK_DLL _declspec(dllexport)
#else
#define DX12_FRAMEWORK_DLL _declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN // 从Windows头文件中排除极少使用的内容  

#include <windows.h>
#include <tchar.h>

// STL
#include <string>
#include <vector>
#include <sstream>
#include <exception>

// DirectX
#include <dxgi1_6.h>
#include <DirectXMath.h>

#if defined(_DEBUG)
#include <dxgidebug.h>
#endif

#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>

using namespace DirectX;

// TinyXML
#include "tinyxml2.h"

using namespace tinyxml2;

#include "iconv.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "libiconv.lib")

#if defined(_DEBUG)
  #if defined(DX12_FRAMEWORK_X64)
    #pragma message("WIN64_DEBUG_MODE")
    #pragma comment(lib,"tinyxml2_x64_d.lib") 
#else
  #pragma message("WIN32_DEBUG_MODE")
    #pragma comment(lib,"tinyxml2_win32_d.lib" ) 
  #endif
#else
  #if defined(DX12_FRAMEWORK_X64)
    #pragma message("WIN64_RELEASE_MODE")
    #pragma comment(lib,"tinyxml2_x64.lib" )
  #else
    #pragma message("WIN32_RELEASE_MODE")
    #pragma comment(lib,"tinyxml2_win32.lib" ) 
  #endif
#endif

#define DX12_FRAMEWORK_SAFE_RELEASE(ptr) do{ if(nullptr !=ptr){ptr->Release();ptr=nullptr;} }while(0)

#endif // framework_h__