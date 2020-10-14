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

class DX12_FRAMEWORK_DLL Dx12Application
{
public:
    const static int nFrameBackBufCount = 2;
    static LRESULT WINAPI WindowsProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    Dx12Application();
    virtual ~Dx12Application();
    LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void Go();
protected:
    /*********************************************************************************
     * Method:    ReleaseRenderer
     * FullName:  Dx12Application::ReleaseRenderer
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     *********************************************************************************/
    virtual void ReleaseRenderer();

    /*********************************************************************************
     * Method:    InitRenderer
     * FullName:  Dx12Application::InitRenderer
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void InitRenderer(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateDXGIFactory
     * FullName:  Dx12Application::CreateDXGIFactory
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreateDXGIFactory(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateD3DDevice
     * FullName:  Dx12Application::EnumerateAdapterAndCreateDevice
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void EnumerateAdapterAndCreateDevice(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateDefaultCommandQueue
     * FullName:  Dx12Application::CreateDefaultCommandQueue
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreateDefaultCommandQueue(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateSwapchain
     * FullName:  Dx12Application::CreateSwapchain
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreateSwapchain(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateHeapDescriptor
     * FullName:  Dx12Application::CreateHeapDescriptor
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreateHeapDescriptor(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateRenderTargetViewDescriptor
     * FullName:  Dx12Application::CreateRenderTargetViewDescriptor
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreateRenderTargetViewDescriptor(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreateDefaultRootSignature
     * FullName:  Dx12Application::CreateDefaultRootSignature
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreateDefaultRootSignature(XMLElement* desc_element);

    /*********************************************************************************
     * Method:    CreatePipelineState
     * FullName:  Dx12Application::CreatePipelineState
     * Access:    virtual protected 
     * Returns:   void
     * Qualifier:
     * Parameter: XMLElement * desc_element
     *********************************************************************************/
    virtual void CreatePipelineState(XMLElement* desc_element);
protected:
    HWND m_hWnd;
    long m_WindowWidth;
    long m_WindowHeight;
    UINT nDXGIFactoryFlags = 0U; // DXGI的创建标识
    UINT nRTVDescriptorSize = 0U;
    UINT nFrameIndex = 0U;
    D3D_FEATURE_LEVEL d3d_feature_level_;
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