﻿#ifndef dx12_renderer_h__
#define dx12_renderer_h__

#include "framework.h"

class DX12_FRAMEWORK_DLL Dx12Renderer
{
protected:
    HWND window_handle_;
    SIZE _winSize;

    ComPtr<IDXGIFactory4> _dxgiFactory = nullptr;
    ComPtr<IDXGISwapChain4> _swapchain = nullptr;
    ComPtr<ID3D12Device> _dev = nullptr;
    ComPtr<ID3D12CommandAllocator> _cmdAllocator = nullptr;
    ComPtr<ID3D12GraphicsCommandList> _cmdList = nullptr;
    ComPtr<ID3D12CommandQueue> _cmdQueue = nullptr;
    ComPtr<ID3D12Resource> _depthBuffer = nullptr;
    ComPtr<ID3D12Resource> _sceneConstBuff = nullptr;
    ComPtr<ID3D12DescriptorHeap> _rtvHeaps = nullptr;
    ComPtr<ID3D12DescriptorHeap> _dsvHeap = nullptr;
    ComPtr<ID3D12DescriptorHeap> _sceneDescHeap = nullptr;

    std::vector<ID3D12Resource*> _backBuffers;
    std::unique_ptr<D3D12_VIEWPORT> _viewport;
    std::unique_ptr<D3D12_RECT> _scissorrect;

    ComPtr<ID3D12Fence> _fence = nullptr;
    UINT64 _fenceVal = 0;

    D3D_FEATURE_LEVEL d3d_feature_level_ = D3D_FEATURE_LEVEL_12_1;
public:
    /*********************************************************************************
     * @brief:  生成深度/模板缓冲区
     * @return: void
     * @param:  const MLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    virtual void CreateDepthStencilView(const XMLElement* elem);

    /*********************************************************************************
     * @brief:  创建交换链的相关信息
     * @return: void
     * @param:  const XMLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    virtual void CreateSwapChain(const XMLElement* elem);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    virtual void InitializeDXGIDevice(const XMLElement* elem);

    /*********************************************************************************
     * @brief:  创建和GPU绘制/计算命令相关的各种接口，包括：
                命令分配器接口ID3D12CommandAllocator
                命令列表接口ID3D12GraphicsCommandLis
                命令队列接口ID3D12CommandQueue
     * @return: void
     * @param:  const XMLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    void InitializeCommand(const XMLElement* elem);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    virtual void CreateSceneView(const XMLElement* elem);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    virtual void CreateFinalRenderTargets(const XMLElement* elem);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem 创建接口时包含有各种配置参数的XML Element实例指针
     *********************************************************************************/
    virtual void CreateFence(const XMLElement* elem);
public:
    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  HWND wnd_handle
     * @param:  UINT wnd_width
     * @param:  UINT wnd_height
     *********************************************************************************/
    Dx12Renderer(HWND wnd_handle,UINT wnd_width,UINT wnd_height);

    /*********************************************************************************
     * @brief:
     * @return: 
     *********************************************************************************/
    virtual ~Dx12Renderer();

    /*********************************************************************************
     * @brief:
     * @return: void
     *********************************************************************************/
    virtual void Update();
    /*********************************************************************************
     * @brief:
     * @return: void
     *********************************************************************************/
    virtual void BeginDraw();
    /*********************************************************************************
     * @brief:
     * @return: void
     *********************************************************************************/
    virtual void EndDraw();
    /*********************************************************************************
     * @brief:
     * @return: void
     *********************************************************************************/
    virtual void ExecuteCommand();

    /*********************************************************************************
     * @brief:
     * @return: Microsoft::WRL::ComPtr<ID3D12Device>
     *********************************************************************************/
    ComPtr<ID3D12Device> Device();

    /*********************************************************************************
     * @brief:
     * @return: Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>
     *********************************************************************************/
    ComPtr<ID3D12GraphicsCommandList> CommandList();

    /*********************************************************************************
     * @brief:
     * @return: Microsoft::WRL::ComPtr<IDXGISwapChain4>
     *********************************************************************************/
    ComPtr<IDXGISwapChain4> Swapchain();

    /*********************************************************************************
     * @brief:
     * @return: void
     *********************************************************************************/
    virtual void SetScene();
};

extern "C" Dx12Renderer* g_dx12_renderer;

#endif // dx12_renderer_h__