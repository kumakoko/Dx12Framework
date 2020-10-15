#pragma once

#include "resource.h"

#include "../Framework/framework.h"
#include "../Framework/dx12_application.h"

#if defined(_DEBUG)
  #if defined(DX12_FRAMEWORK_X64)
    #pragma message("WIN64_DEBUG_MODE")
    #pragma comment(lib,"Framework_x64_d.lib") 
  #else
    #pragma message("WIN32_DEBUG_MODE")
    #pragma comment(lib,"Framework_win32_d.lib" ) 
  #endif
#else
  #if defined(DX12_FRAMEWORK_X64)
    #pragma message("WIN64_RELEASE_MODE")
    #pragma comment(lib,"Framework_x64.lib" )
  #else
    #pragma message("WIN32_RELEASE_MODE")
    #pragma comment(lib,"Framework_win32.lib" ) 
  #endif
#endif

class TriangleApp : public Dx12Application
{
public:
protected:
    /*********************************************************************************
     * @brief: 创建一个DX12 Renderer的实例，每一个不同的Demo应该继承Dx12Renderer类。实现
               一个本demo适用的渲染器
     * @return: void
     *********************************************************************************/
    virtual void CreateDX12Renderer() override;
};