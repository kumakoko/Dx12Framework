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
#ifndef dx12_application_h__
#define dx12_application_h__

#include "dx12_renderer.h"

class DX12_FRAMEWORK_DLL Dx12Application
{
public:
    const static int nFrameBackBufCount = 2;

    /*********************************************************************************
     * @brief:
     * @return: LRESULT WINAPI
     * @param:  HWND hWnd
     * @param:  UINT msg
     * @param:  WPARAM wParam
     * @param:  LPARAM lParam
     *********************************************************************************/
    static LRESULT WINAPI WindowsProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  const TCHAR * app_name
     * @param:  long wnd_width
     * @param:  long wnd_height
     *********************************************************************************/
    Dx12Application(const TCHAR* app_name = _T("Direct3D 12 Application"), long wnd_width = 1024L, long wnd_height = 768L );

    /*********************************************************************************
     * @brief:
     * @return:
     *********************************************************************************/
    virtual ~Dx12Application();

    /*********************************************************************************
     * @brief:
     * @return: LRESULT WINAPI
     * @param:  HWND hWnd
     * @param:  UINT msg
     * @param:  WPARAM wParam
     * @param:  LPARAM lParam
     *********************************************************************************/
    LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    /*********************************************************************************
     * @brief: 应用程序进程执行的主入口函数，基类的Init函数调用了：
                1 CoInitializeEx函数，初始化了COM库，Direct3D 12初始化时要用到COM
                2 Dx12Application::CreateAppWindow()函数，用以创建应用程序窗口
                3 Dx12Application::CreateDX12Renderer()函数，创建DX12渲染器
     * @return: void
     *********************************************************************************/
    virtual void Init();

    /*********************************************************************************
     * @brief:
     * @return: void
     *********************************************************************************/
    virtual void Run();

protected:
    /*********************************************************************************
     * @brief:  创建应用程序窗口
     * @return: void
     *********************************************************************************/
    virtual void CreateAppWindow();

    /*********************************************************************************
     * @brief: 创建一个DX12 Renderer的实例，每一个不同的Demo应该继承Dx12Renderer类。实现
               一个本demo适用的渲染器
     * @return: void
     *********************************************************************************/
    virtual void CreateDX12Renderer() = 0;

protected:
    tstring wnd_name_;
    Dx12Renderer*  dx12_renderer_ = nullptr;
    HWND m_hWnd;
    long m_WindowWidth;
    long m_WindowHeight;
    UINT nDXGIFactoryFlags = 0U; // DXGI的创建标识
    UINT nRTVDescriptorSize = 0U;
    UINT nFrameIndex = 0U;
    D3D_FEATURE_LEVEL d3d_feature_level_;
    UINT n64FenceValue;
    HANDLE hFenceEvent;
    HANDLE phWait;
#if defined(_DEBUG)
    ID3D12Debug* debugController = nullptr;
#endif
    IDXGIFactory5* pIDXGIFactory5 = nullptr;
    IDXGIAdapter1* pIAdapter = nullptr;
    ID3D12Device4* pID3DDevice = nullptr;
    ID3D12CommandQueue* pICommandQueue = nullptr;
    IDXGISwapChain1* pISwapChain1 = nullptr;
    IDXGISwapChain3* pISwapChain3 = nullptr;
    ID3D12DescriptorHeap* pIRTVHeap = nullptr;
    ID3D12Resource* pIARenderTargets[nFrameBackBufCount];
    ID3D12CommandAllocator* pICommandAllocator = nullptr;
    ID3D12RootSignature* pIRootSignature = nullptr;
    ID3D12PipelineState* pIPipelineState = nullptr;
    ID3D12GraphicsCommandList* pICommandList = nullptr;
    ID3D12Resource* pIVertexBuffer = nullptr;
    ID3D12Fence* pIFence;
};

extern "C" DX12_FRAMEWORK_DLL Dx12Application* g_pDx12App;

#endif // dx12_application_h__