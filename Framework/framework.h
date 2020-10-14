/**************************************************************************************************************************
Copyright(C) 2014-2020 www.xionggf.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute,sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************************************/
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
#include <map>
#include <sstream>
#include <exception>

// BOOST
#include "boost/algorithm/string.hpp"

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

#include "d3dx12.h"

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

#if defined(UNICODE)
  typedef std::wstring tstring;
#else
  typedef std::string tstring;
#endif

#endif // framework_h__