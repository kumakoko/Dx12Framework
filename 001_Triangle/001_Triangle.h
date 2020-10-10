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

};