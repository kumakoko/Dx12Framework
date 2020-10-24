#include "pch.h"
#include "dx12_renderer.h"
#include "string_convertor.h"
#include "xml_config_helper.h"
#include "d3d12_resource_desc_ex.h"
#include "d3d12_heap_properties_ex.h"
#include "d3d12_clear_value_ex.h"
#include "d3d12_depth_stencil_view_desc_ex.h"
#include "d3d12_descriptor_heap_desc_ex.h"
#include "d3d12_render_target_view_desc_ex.h"
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

Dx12Renderer::Dx12Renderer(HWND wnd_handle, UINT wnd_width, UINT wnd_height) :
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

    const XMLElement* depth_buffer_elem = elem->FirstChildElement("depth_buffer");

    // 资源描述结构体
    const XMLElement* res_desc_elem = depth_buffer_elem->FirstChildElement("D3D12_RESOURCE_DESC");
    D3D12ResourceDescEx res_desc(res_desc_elem, desc.Width, desc.Height);

    // 深度缓冲区的堆属性描述结构 
    const XMLElement* heap_props_elem = depth_buffer_elem->FirstChildElement("D3D12_HEAP_PROPERTIES");
    D3D12HeapPropertiesEx depth_heap_prop(heap_props_elem);

    // 深度/模板缓冲区的清理填充用颜色值
    const XMLElement* clear_value_elem = depth_buffer_elem->FirstChildElement("D3D12_CLEAR_VALUE");
    D3D12ClearValueEx depth_clear_value(clear_value_elem);// (DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

    result = _dev->CreateCommittedResource(
        &depth_heap_prop,
        XmlConfigHelper::GetHeapFlagType(elem->Attribute("heap_flags")),//D3D12_HEAP_FLAG_NONE,
        &res_desc,
        XmlConfigHelper::GetD3D12ResourceStates(elem->Attribute("resource_states")),//D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &depth_clear_value,
        IID_PPV_ARGS(_depthBuffer.ReleaseAndGetAddressOf()));

    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommittedResource");

    // 从XML文件中读取descriptor heap 描述结构
    const XMLElement* descriptor_heap_desc_elem = depth_buffer_elem->FirstChildElement("D3D12_DESCRIPTOR_HEAP_DESC");
    D3D12DescriptorHeapDescEx dsv_heap_desc(descriptor_heap_desc_elem);// () = {};//
    result = _dev->CreateDescriptorHeap(&dsv_heap_desc, IID_PPV_ARGS(_dsvHeap.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateDescriptorHeap");

    // 从XML文件中读取D3D12_DEPTH_STENCIL_VIEW_DESC类型的结构体
    const XMLElement* dsv_desc_elem = depth_buffer_elem->FirstChildElement("D3D12_DEPTH_STENCIL_VIEW_DESC");
    D3D12DepthStencilViewDescEx dsv_desc;
    dsv_desc.Init(dsv_desc_elem);

    // 根据前面获得的D3D12_DEPTH_STENCIL_VIEW_DESC， D3D12_DESCRIPTOR_HEAP_DESC，D3D12_CLEAR_VALUE
    // 和D3D12_CLEAR_VALUE四个结构体，创建出一个depth-stencil-value接口出来。
    _dev->CreateDepthStencilView(_depthBuffer.Get(), &dsv_desc, _dsvHeap->GetCPUDescriptorHandleForHeapStart());
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateDepthStencilView");
}


Dx12Renderer::~Dx12Renderer()
{
}

void Dx12Renderer::InitializeDXGIDevice(const XMLElement* elem)
{
    /* 1 创建DXGIFactory接口
    在D3D12中，一个重要的概念是将设备对象概念进行了扩展。将原来在D3D9中揉在一起的图形子系统（从硬件子系统角度抽象），
    显示器，适配器，3D设备等对象进行了分离，而分离的标志就是使用IDXGIFactory来代表整个图形子系统，它主要的功用之一就
    是创建适配器、3D设备等对象接口用的，这就是设计模式中的工厂模式的一种应用。这个对象接口就是要创建的第一个接口：*/
    UINT flagsDXGI = 0;
    flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
    HRESULT result = CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"CreateDXGIFactory2");

    /*如果你很奇怪接口和函数名后面的数字，那么你现在就理解他们为对应接口或函数的版本号，默认为0，也就是第一个原始
    版本，不用写出来，2就表示升级的第三个版本，依此类推。因为例子代码中要稍微用到一点扩展的功能，所以我们就用较
    高版本的函数和接口。*/
    UINT flags = XmlConfigHelper::ParseWindowAssociationFlag(elem->Attribute("window_association")); 
    Error::GRS_THROW_IF_FAILED(_dxgiFactory->MakeWindowAssociation(window_handle_, flags), __FILE__, __LINE__);

    // 2 枚举所有支持Direct3D 12的显示适配器
    const char* feature_level_sub_ver = elem->Attribute("feature_level_sub_ver");

    if (nullptr != feature_level_sub_ver && _stricmp(feature_level_sub_ver, "1") == 0)
        d3d_feature_level_ = D3D_FEATURE_LEVEL_12_1; // 将来能够调用DXR的话要是设置为12.155
    else
        d3d_feature_level_ = D3D_FEATURE_LEVEL_12_0;

    IDXGIAdapter1* pIAdapter = nullptr;

    for (UINT adapterIndex = 1; DXGI_ERROR_NOT_FOUND != _dxgiFactory->EnumAdapters1(adapterIndex, &pIAdapter); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc = {};
        pIAdapter->GetDesc1(&desc);

        /*特别需要提醒的是，未来的一些例子中，请你在代码的创建循环中的if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        语句上设置断点，然后仔细查看desc中的内容，确认你用于创建设备对象的适配器是你系统中最强的一块显卡。一般系统
        中默认序号0的设备是集显，如果不是独显，那就请你修改adapterIndex这个循环初值，比如改为1或2过更高的值试试，
        当然前提是你的系统中确定有那么多适配器（也就是显卡），直到使用了性能最强的一个适配器来创建设备。这样做的目
        的不是为了跑性能，而是目前我发现集显在运行一些高级功能时会出现一些问题，很多高级功能是不支持的，用功能比较
        强的独显是不错的一个方法。*/
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) // 跳过软件虚拟适配器设备
        {
            continue;
        }

        /*检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
        就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！*/
        if (SUCCEEDED(D3D12CreateDevice(pIAdapter, d3d_feature_level_, _uuidof(ID3D12Device), nullptr)))
        {
            break;
        }
    }

    Error::GRS_THROW_IF_FAILED(D3D12CreateDevice(pIAdapter, d3d_feature_level_, IID_PPV_ARGS(&_dev)), __FILE__, __LINE__);
}

void Dx12Renderer::CreateSwapChain(const XMLElement* elem)
{
    RECT rc = {};
    ::GetWindowRect(window_handle_, &rc);

    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
    swapchainDesc.Width = _winSize.cx;
    swapchainDesc.Height = _winSize.cy;
    swapchainDesc.Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("swapchain_format"));//DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.Stereo = false;
    swapchainDesc.SampleDesc.Count = XmlConfigHelper::AttributeValue(elem, "sample_desc_count", 1);//1;
    swapchainDesc.SampleDesc.Quality = XmlConfigHelper::AttributeValue(elem, "sample_desc_quality", 0);// 0;
    swapchainDesc.BufferUsage = XmlConfigHelper::GetDXGIUsage(elem->Attribute("buffer_usage"));//DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchainDesc.BufferCount = 2;
    swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapchainDesc.SwapEffect = XmlConfigHelper::GetDXGISwapEffect(elem->Attribute("swap_effect"));//DXGI_SWAP_EFFECT_FLIP_DISCARD;
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

void Dx12Renderer::InitializeCommand(const XMLElement* elem)
{
    D3D12_COMMAND_LIST_TYPE cmd_list_type = XmlConfigHelper::GetCommandListType(elem->Attribute("command_list_type"));

    HRESULT result = _dev->CreateCommandAllocator(cmd_list_type, IID_PPV_ARGS(_cmdAllocator.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommandAllocator");

    result = _dev->CreateCommandList(0, cmd_list_type, _cmdAllocator.Get(), nullptr, IID_PPV_ARGS(_cmdList.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommandList");

    /*再接下去如果你熟悉D3D11的话，我们就需要创建DeviceContext对象及接口了，而在D3D9中有了设备接口就相当
    于有了一切，直接就可以加载资源，设置管线状态，然后开始渲染（注意我跳过了说D3D10，你又猜对了，我是
    故意跳过的，想想为什么？）。

    其实我一直觉得在D3D11中这个接口对象及名字DeviceContext不是那么直观。在D3D12中就直接改叫CommandQueue
    了。这是为什么呢？其实现代的显卡上或者说GPU中，已经包含多个可以同时并行执行命令的引擎了，不是游戏引擎，
    可以理解为执行某类指令的专用微核。也请注意这里的概念，一定要理解并行执行的引擎这个概念，因为将来的重要
    示例如多线程渲染，多显卡渲染示例等中还会用到这个概念。

    这里再举个例子来加深理解这个概念，比如支持D3D12的GPU中至少就有执行3D命令的引擎，执行复制命令的引擎
    （就是从CPU内存中复制内容到显存中或反之或GPU内部以及引擎之间），执行通用计算命令的引擎（执行Computer
    Shader的引擎）以及可以进行视频编码解码的视频引擎等。而在D3D12中针对这些不同的引擎，就需要创建不同的命
    令队列接口来代表不同的引擎对象了。这相较于传统的D3D9或者D3D11设备接口来说，不但接口被拆分了，而且在对
    象概念层级上都进行了拆分。形象的理解如下图所示：*/
    const XMLElement* desc_element = elem->FirstChildElement("D3D12_COMMAND_QUEUE_DESC");
    D3D12_COMMAND_QUEUE_DESC cmd_queue_desc = {};
    cmd_queue_desc.Flags = XmlConfigHelper::GetCommandQueueFlag(desc_element->Attribute("flags")); //D3D12_COMMAND_QUEUE_FLAG_NONE;//
    cmd_queue_desc.NodeMask = XmlConfigHelper::AttributeValue(desc_element, "node_mask", 0);
    cmd_queue_desc.Priority = XmlConfigHelper::GetCommandQueuePriority(desc_element->Attribute("priority"));//D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//
    cmd_queue_desc.Type = cmd_list_type;// D3D12_COMMAND_LIST_TYPE_DIRECT;//
    result = _dev->CreateCommandQueue(&cmd_queue_desc, IID_PPV_ARGS(_cmdQueue.ReleaseAndGetAddressOf()));//
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateCommandQueue");
}

void Dx12Renderer::CreateSceneView(const XMLElement* elem)
{
}

void Dx12Renderer::CreateFinalRenderTargets(const XMLElement* elem)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    HRESULT result = _swapchain->GetDesc1(&desc);
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"IDXGISwapChain4::GetDesc1");

    // 从XML中读取描述符堆的描述体
    const XMLElement* heap_desc_elem = elem->FirstChildElement("D3D12_DESCRIPTOR_HEAP_DESC");
    D3D12DescriptorHeapDescEx heap_desc(heap_desc_elem);
    result = _dev->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(_rtvHeaps.ReleaseAndGetAddressOf()));
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"ID3D12Device::CreateDescriptorHeap");

    // 获取到交换链的描述结构
    DXGI_SWAP_CHAIN_DESC swapchain_desc = {};
    result = _swapchain->GetDesc(&swapchain_desc);
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"IDXGISwapChain4::GetDesc");

    _backBuffers.resize(swapchain_desc.BufferCount);
    D3D12_CPU_DESCRIPTOR_HANDLE handle = _rtvHeaps->GetCPUDescriptorHandleForHeapStart();

    const XMLElement* rt_view_elem = elem->FirstChildElement("D3D12_RENDER_TARGET_VIEW_DESC");
    D3D12RenderTargetViewDescEx rtv_desc(rt_view_elem);

    for (UINT i = 0U; i < swapchain_desc.BufferCount; ++i)
    {
        result = _swapchain->GetBuffer(i, IID_PPV_ARGS(&_backBuffers[i]));
        Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"IDXGISwapChain4::GetBuffer");

        rtv_desc.Format = _backBuffers[i]->GetDesc().Format;
        _dev->CreateRenderTargetView(_backBuffers[i], &rtv_desc, handle);
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

void Dx12Renderer::BeginDraw()
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
    _cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_backBuffers[bbIdx],
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