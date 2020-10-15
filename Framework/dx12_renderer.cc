#include "pch.h"
#include "dx12_renderer.h"
#include "xml_config_helper.h"
#include "error.h"

/**
///デバッグレイヤーを有効にする
void EnableDebugLayer() {
    ComPtr<ID3D12Debug> debugLayer = nullptr;
    auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
    debugLayer->EnableDebugLayer();
}
*/

Dx12Renderer* g_dx12_renderer = nullptr;

Dx12Renderer::Dx12Renderer(HWND wnd_handle, UINT wnd_width, UINT wnd_height):
    window_handle_(wnd_handle)
{
    window_handle_ = wnd_handle;
    _winSize.cx = wnd_width;
    _winSize.cy = wnd_height;
    /*
#ifdef _DEBUG
    //デバッグレイヤーをオンに
    EnableDebugLayer();
#endif

    auto& app = Application::Instance();
    _winSize = app.GetWindowSize();

    //DirectX12関連初期化
    if (FAILED(InitializeDXGIDevice())) {
        assert(0);
        return;
    }
    if (FAILED(InitializeCommand())) {
        assert(0);
        return;
    }
    if (FAILED(CreateSwapChain(hwnd))) {
        assert(0);
        return;
    }
    if (FAILED(CreateFinalRenderTargets())) {
        assert(0);
        return;
    }

    if (FAILED(CreateSceneView())) {
        assert(0);
        return;
    }

    //テクスチャローダー関連初期化
    CreateTextureLoaderTable();



    //深度バッファ作成
    if (FAILED(CreateDepthStencilView())) {
        assert(0);
        return;
    }

    //フェンスの作成
    if (FAILED() {
        assert(0);
        return;
    }
    */

    g_dx12_renderer = this;
}

void Dx12Renderer::CreateFence(const XMLElement* elem)
{
    HRESULT result = _dev->CreateFence(_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateFence");
}

void Dx12Renderer::CreateDepthStencilView(const XMLElement* elem)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    HRESULT result = _swapchain->GetDesc1(&desc);
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::GetDesc1");

    D3D12_RESOURCE_DESC resdesc = {};
    resdesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resdesc.DepthOrArraySize = 1;
    resdesc.Width = desc.Width;
    resdesc.Height = desc.Height;
    resdesc.Format = DXGI_FORMAT_D32_FLOAT;
    resdesc.SampleDesc.Count = 1;
    resdesc.SampleDesc.Quality = 0;
    resdesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    resdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resdesc.MipLevels = 1;
    resdesc.Alignment = 0;

    auto depthHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

    CD3DX12_CLEAR_VALUE depthClearValue(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

    result = _dev->CreateCommittedResource(
        &depthHeapProp,
        D3D12_HEAP_FLAG_NONE,
        &resdesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE, //
        &depthClearValue,
        IID_PPV_ARGS(_depthBuffer.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommittedResource");

    //
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};//
    dsvHeapDesc.NumDescriptors = 1;//
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    result = _dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(_dsvHeap.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateDescriptorHeap");

    //
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;// 
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;// 
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;//
    _dev->CreateDepthStencilView(_depthBuffer.Get(), &dsvDesc, _dsvHeap->GetCPUDescriptorHandleForHeapStart());
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateDepthStencilView");
}


Dx12Renderer::~Dx12Renderer()
{
}

void Dx12Renderer::InitializeDXGIDevice(const XMLElement* elem)
{
    UINT flagsDXGI = 0;
    flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
    HRESULT result = CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"CreateDXGIFactory2");

    D3D_FEATURE_LEVEL levels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    std::vector <IDXGIAdapter*> adapters;
    IDXGIAdapter* tmpAdapter = nullptr;
    for (int i = 0; _dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        adapters.push_back(tmpAdapter);
    }
    for (auto adpt : adapters) {
        DXGI_ADAPTER_DESC adesc = {};
        adpt->GetDesc(&adesc);
        std::wstring strDesc = adesc.Description;
        if (strDesc.find(L"NVIDIA") != std::string::npos) {
            tmpAdapter = adpt;
            break;
        }
    }
    result = S_FALSE;
    //Direct3Dデバイスの初期化
    D3D_FEATURE_LEVEL featureLevel;
    for (auto l : levels) {
        if (SUCCEEDED(D3D12CreateDevice(tmpAdapter, l, IID_PPV_ARGS(_dev.ReleaseAndGetAddressOf())))) {
            featureLevel = l;
            result = S_OK;
            break;
        }
    }
}

void Dx12Renderer::CreateSwapChain(const XMLElement* elem)
{
    RECT rc = {};
    ::GetWindowRect(window_handle_, &rc);

    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
    swapchainDesc.Width = _winSize.cx;
    swapchainDesc.Height = _winSize.cy;
    swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.Stereo = false;
    swapchainDesc.SampleDesc.Count = 1;
    swapchainDesc.SampleDesc.Quality = 0;
    swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchainDesc.BufferCount = 2;
    swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    HRESULT result = _dxgiFactory->CreateSwapChainForHwnd(_cmdQueue.Get(),
        window_handle_,
        &swapchainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)_swapchain.ReleaseAndGetAddressOf());

    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"IDXGIFactory4::CreateSwapChainForHwnd");
}

//コマンドまわり初期化
void Dx12Renderer::InitializeCommand(const XMLElement* elem)
{
    HRESULT result = _dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(_cmdAllocator.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommandAllocator");

    result = _dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAllocator.Get(), nullptr, IID_PPV_ARGS(_cmdList.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommandList");

    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//
    cmdQueueDesc.NodeMask = 0;
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//
    result = _dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(_cmdQueue.ReleaseAndGetAddressOf()));//
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommandQueue");
}

//ビュープロジェクション用ビューの生成
void Dx12Renderer::CreateSceneView(const XMLElement* elem)
{
}

void Dx12Renderer::CreateFinalRenderTargets(const XMLElement* elem)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    HRESULT result = _swapchain->GetDesc1(&desc);

    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビューなので当然RTV
    heapDesc.NodeMask = 0;
    heapDesc.NumDescriptors = 2;//表裏の２つ
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//特に指定なし

    result = _dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(_rtvHeaps.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateDescriptorHeap");


    DXGI_SWAP_CHAIN_DESC swcDesc = {};
    result = _swapchain->GetDesc(&swcDesc);
    _backBuffers.resize(swcDesc.BufferCount);

    D3D12_CPU_DESCRIPTOR_HANDLE handle = _rtvHeaps->GetCPUDescriptorHandleForHeapStart();

    //SRGBレンダーターゲットビュー設定
    D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

    for (UINT i = 0U; i < swcDesc.BufferCount; ++i)
    {
        result = _swapchain->GetBuffer(i, IID_PPV_ARGS(&_backBuffers[i]));
        Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"IDXGISwapChain4::GetBuffer");

        rtvDesc.Format = _backBuffers[i]->GetDesc().Format;
        _dev->CreateRenderTargetView(_backBuffers[i], &rtvDesc, handle);
        handle.ptr += _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    _viewport.reset(new CD3DX12_VIEWPORT(_backBuffers[0]));
    _scissorrect.reset(new CD3DX12_RECT(0, 0, desc.Width, desc.Height));
}

ComPtr<ID3D12Device> Dx12Renderer::Device() 
{
    return _dev;
}

ComPtr<ID3D12GraphicsCommandList> Dx12Renderer::CommandList()
{
    return _cmdList;
}

void Dx12Renderer::Update()
{
}

void
Dx12Renderer::BeginDraw() 
{
    //DirectX処理
    auto bbIdx = _swapchain->GetCurrentBackBufferIndex();

    _cmdList->ResourceBarrier(1,
        &CD3DX12_RESOURCE_BARRIER::Transition(_backBuffers[bbIdx],
            D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

    auto rtvH = _rtvHeaps->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += bbIdx * _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    auto dsvH = _dsvHeap->GetCPUDescriptorHandleForHeapStart();
    _cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
    _cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


    //float clearColor[] = { 0.5f,0.5f,0.5f,1.0f };//白色
    float clearColor[] = { 1.0f,0.0f,0.0f,1.0f };//白色
    _cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

    _cmdList->RSSetViewports(1, _viewport.get());
    _cmdList->RSSetScissorRects(1, _scissorrect.get());
}

void Dx12Renderer::SetScene() 
{
    ID3D12DescriptorHeap* sceneheaps[] = { _sceneDescHeap.Get() };
    _cmdList->SetDescriptorHeaps(1, sceneheaps);
    _cmdList->SetGraphicsRootDescriptorTable(0, _sceneDescHeap->GetGPUDescriptorHandleForHeapStart());
}

void Dx12Renderer::EndDraw()
{
    auto bbIdx = _swapchain->GetCurrentBackBufferIndex();
    _cmdList->ResourceBarrier(1,&CD3DX12_RESOURCE_BARRIER::Transition(_backBuffers[bbIdx],
            D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
    ExecuteCommand();
}

void Dx12Renderer::ExecuteCommand()
{
    _cmdList->Close();

    ID3D12CommandList* cmdlists[] = { _cmdList.Get() };
    _cmdQueue->ExecuteCommandLists(1, cmdlists);
    _cmdQueue->Signal(_fence.Get(), ++_fenceVal);

    if (_fence->GetCompletedValue() < _fenceVal) 
    {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        _fence->SetEventOnCompletion(_fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }

    _cmdAllocator->Reset();//キューをクリア
    _cmdList->Reset(_cmdAllocator.Get(), nullptr);//再びコマンドリストをためる準備
}

ComPtr<IDXGISwapChain4> Dx12Renderer::Swapchain()
{
    return _swapchain;
}