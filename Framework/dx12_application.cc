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
#include "pch.h"
#include "dx12_application.h"
#include "error.h"
#include "string_convertor.h"
#include "xml_config_helper.h"

Dx12Application* g_pDx12App = nullptr;

LRESULT Dx12Application::WindowsProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (WM_DESTROY == msg)
    {
        PostQuitMessage(0);
        return 0;
    }
    else
    {
        return g_pDx12App->MessageHandler(hWnd, msg, wParam, lParam);
    }
}

Dx12Application::Dx12Application(const TCHAR* app_name, long wnd_width, long wnd_height)
{
    wnd_name_ = app_name;
    m_WindowWidth = wnd_width;
    m_WindowHeight = wnd_height;
}

void Dx12Application::Init()
{
    HRESULT result = CoInitializeEx(0, COINIT_MULTITHREADED);
    Error::GRS_THROW_IF_FAILED(result, __FILE__, __LINE__, L"CoInitializeEx");
    CreateAppWindow();
    CreateDX12Renderer();
    //  dx12_renderer_->ExecuteCommand();
}

void Dx12Application::Run()
{
    ShowWindow(m_hWnd, SW_SHOW);

    float angle = 0.0f;
    MSG msg = {};
    unsigned int frame = 0;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }

        dx12_renderer_->BeginDraw();
     //   dx12_renderer_->SetScene();
        dx12_renderer_->EndDraw();        
        dx12_renderer_->Swapchain()->Present(0, 0);
    }
}

void Dx12Application::CreateAppWindow()
{
    WNDCLASSEX windowClass = { sizeof(WNDCLASSEX),
                          CS_CLASSDC,
                          WindowsProcedure,
                          0,
                          0,
                          GetModuleHandle(nullptr),
                          nullptr,
                          nullptr,
                          nullptr,
                          nullptr,
                          _T("DirectD12APP"),
                          nullptr };

    RegisterClassEx(&windowClass);

    RECT wrc = { 0,0, m_WindowWidth, m_WindowHeight };//
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//

    m_hWnd = CreateWindow(_T("DirectD12APP"),
        _T("DirectD12APP"),//
        WS_OVERLAPPEDWINDOW,//
        CW_USEDEFAULT,//
        CW_USEDEFAULT,//
        wrc.right - wrc.left,//
        wrc.bottom - wrc.top,//
        nullptr,//
        nullptr,//
        windowClass.hInstance,//
        nullptr);

    if (nullptr == m_hWnd)
    {
        Error::ThrowErrorOfLastError(__FILE__,__LINE__);
    }
}





//
//void Dx12Application::PrepareWaitableTimer()
//{
//    //创建定时器对象，以便于创建高效的消息循环
//    phWait = CreateWaitableTimer(nullptr, FALSE, nullptr);
//    LARGE_INTEGER liDueTime = {};
//
//    liDueTime.QuadPart = -1i64;//1秒后开始计时
//
//    // 每40ms唤醒一次
//    SetWaitableTimer(phWait, &liDueTime, 1, nullptr, nullptr, 0);//40ms的周期
//}
//
//void Dx12Application::Render()
//{
//}
//
//const ID3D12Device4* Dx12Application::D3DDevice() const
//{
//    return pID3DDevice;
//}
//
//ID3D12Device4* Dx12Application::D3DDevice()
//{
//    return pID3DDevice;
//}
//
//void Dx12Application::Run()
//{
//    WNDCLASSEX WindowClass = { sizeof(WNDCLASSEX),CS_CLASSDC,
//                              Dx12Application::WindowsProcedure,
//                              0,0,GetModuleHandle(nullptr),
//                              nullptr,nullptr,nullptr,nullptr,
//                              _T("Dx12 Application"),
//                              nullptr };
//    RegisterClassEx(&WindowClass);
//
//    m_hWnd = CreateWindow(_T("Dx12 Application"), _T("Dx12 Application"), WS_OVERLAPPEDWINDOW,
//        0, 0, m_WindowWidth, m_WindowHeight, GetDesktopWindow(), nullptr, WindowClass.hInstance, nullptr);
//
//    if (m_hWnd)
//        ShowWindow(m_hWnd, SW_SHOW);
//    else
//        return;
//
//    tinyxml2::XMLDocument doc;
//    tinyxml2::XMLError ret = doc.LoadFile("default_renderer_setting.xml");
//    Error::ThrowTinyXMLException(ret, std::wstring(L"default_renderer_setting.xml"), __FILE__, __LINE__);
//
//    InitRenderer(doc.FirstChildElement("renderer"));
//    PrepareWaitableTimer();
//
//    //开始消息循环，并在其中不断渲染
//    DWORD dwRet = 0;
//    BOOL bExit = FALSE;
//    MSG msg;
//
//    while (!bExit)
//    {
//        // https://www.cnblogs.com/shangdawei/p/4015772.html
//        /*MsgWaitForMultipleObjects阻塞时仍可以响应消息,类似WaitForMultipleObjects()，
//        但它会在“对象被激发”或“消息到达队列”时被唤醒而返回。
//        MsgWaitForMultipleObjects()多接收一个参数，允许指定哪些消息是观察对象。*/
//        dwRet = ::MsgWaitForMultipleObjects(
//            1,  // 表示pHandles所指的handles数组的元素个数，最大容量是MAXIMUM_WAIT_OBJECTS 
//            &phWait, // 指向一个由对象handles组成的数组，这些handles的类型不需要相同
//            FALSE, // 是否等待所有的handles被激发才返回
//                   // 都得到通知才返回，设置为FALSE，有一个内核对象得到通知就返回
//            INFINITE, // 超时时间
//            QS_ALLINPUT);// 欲观察的用户输入消息类型，现在是所有的用户输入都观察
//
//        switch (dwRet - WAIT_OBJECT_0)
//        {
//        case 0:
//        case WAIT_TIMEOUT:
//        {
//            Render();
//        }
//        break;
//        case 1:
//        {
//            //处理消息
//            while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//            {
//                if (WM_QUIT != msg.message)
//                {
//                    ::TranslateMessage(&msg);
//                    ::DispatchMessage(&msg);
//                }
//                else
//                {
//                    bExit = TRUE;
//                }
//            }
//        }
//        break;
//        default:
//            break;
//        }
//
//    }
//
//    /*
//    MSG Message;
//    PeekMessage(&Message, 0, 0, 0, PM_REMOVE);
//
//    while (Message.message != WM_QUIT)
//    {
//        const float clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart()
//            , nFrameIndex
//            , nRTVDescriptorSize);
//        pICommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
//        pICommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
//
//        Error::GRS_THROW_IF_FAILED(pISwapChain3->Present(1, 0),__FILE__,__LINE__);
//
//        TranslateMessage(&Message);
//        DispatchMessage(&Message);
//        PeekMessage(&Message, 0, 0, 0, PM_REMOVE);
//    }
//    */
//}
//

Dx12Application::~Dx12Application()
{
    if (m_hWnd)
        DestroyWindow(m_hWnd);
}

//
//void Dx12Application::EnumerateAdapterAndCreateDevice(XMLElement* desc_element)
//{
//    const char* feature_level_sub_ver = desc_element->Attribute("feature_level_sub_ver");
//
//    if (nullptr != feature_level_sub_ver && _stricmp(feature_level_sub_ver, "1") == 0)
//        d3d_feature_level_ = D3D_FEATURE_LEVEL_12_1; // 将来能够调用DXR的话要是设置为12.155
//    else
//        d3d_feature_level_ = D3D_FEATURE_LEVEL_12_0;
//
//    for (UINT adapterIndex = 1; DXGI_ERROR_NOT_FOUND != pIDXGIFactory5->EnumAdapters1(adapterIndex, &pIAdapter); ++adapterIndex)
//    {
//        DXGI_ADAPTER_DESC1 desc = {};
//        pIAdapter->GetDesc1(&desc);
//
//        /*
//        特别需要提醒的是，未来的一些例子中，请你在代码的创建循环中的if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
//        语句上设置断点，然后仔细查看desc中的内容，确认你用于创建设备对象的适配器是你系统中最强的一块显卡。一般系统
//        中默认序号0的设备是集显，如果不是独显，那就请你修改adapterIndex这个循环初值，比如改为1或2过更高的值试试，
//        当然前提是你的系统中确定有那么多适配器（也就是显卡），直到使用了性能最强的一个适配器来创建设备。这样做的目
//        的不是为了跑性能，而是目前我发现集显在运行一些高级功能时会出现一些问题，很多高级功能是不支持的，用功能比较
//        强的独显是不错的一个方法。
//        */
//        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) // 跳过软件虚拟适配器设备
//        {
//            continue;
//        }
//
//        //检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
//        //就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！
//        if (SUCCEEDED(D3D12CreateDevice(pIAdapter, d3d_feature_level_, _uuidof(ID3D12Device), nullptr)))
//        {
//            break;
//        }
//    }
//
//    Error::GRS_THROW_IF_FAILED(D3D12CreateDevice(pIAdapter, d3d_feature_level_, IID_PPV_ARGS(&pID3DDevice)), __FILE__, __LINE__);
//}
//
//
//void Dx12Application::CreateDXGIFactory(XMLElement* desc_element)
//{
//    /*在D3D12中，一个重要的概念是将设备对象概念进行了扩展。将原来在D3D9中揉在一起的图形子系统（从硬件子系统角度抽象），
//    显示器，适配器，3D设备等对象进行了分离，而分离的标志就是使用IDXGIFactory来代表整个图形子系统，它主要的功用之一就
//    是创建适配器、3D设备等对象接口用的，这就是设计模式中的工厂模式的一种应用。这个对象接口就是要创建的第一个接口：*/
//    Error::GRS_THROW_IF_FAILED(CreateDXGIFactory2(nDXGIFactoryFlags, IID_PPV_ARGS(&pIDXGIFactory5)), __FILE__, __LINE__);
//
//    /*如果你很奇怪接口和函数名后面的数字，那么你现在就理解他们为对应接口或函数的版本号，默认为0，也就是第一个原始
//    版本，不用写出来，2就表示升级的第三个版本，依此类推。因为例子代码中要稍微用到一点扩展的功能，所以我们就用较
//    高版本的函数和接口。*/
//    UINT flags = XmlConfigHelper::ParseWindowAssociationFlag(desc_element->Attribute("window_association"));
//    Error::GRS_THROW_IF_FAILED(pIDXGIFactory5->MakeWindowAssociation(m_hWnd, flags), __FILE__, __LINE__);
//}
//
//// https://blog.csdn.net/u014038143/article/details/82730776
//void Dx12Application::CreateDefaultCommandQueue(XMLElement* desc_element)
//{
//    /*再接下去如果你熟悉D3D11的话，我们就需要创建DeviceContext对象及接口了，而在D3D9中有了设备接口就相当
//    于有了一切，直接就可以加载资源，设置管线状态，然后开始渲染（注意我跳过了说D3D10，你又猜对了，我是
//    故意跳过的，想想为什么？）。
//
//    其实我一直觉得在D3D11中这个接口对象及名字DeviceContext不是那么直观。在D3D12中就直接改叫CommandQueue
//    了。这是为什么呢？其实现代的显卡上或者说GPU中，已经包含多个可以同时并行执行命令的引擎了，不是游戏引擎，
//    可以理解为执行某类指令的专用微核。也请注意这里的概念，一定要理解并行执行的引擎这个概念，因为将来的重要
//    示例如多线程渲染，多显卡渲染示例等中还会用到这个概念。
//
//    这里再举个例子来加深理解这个概念，比如支持D3D12的GPU中至少就有执行3D命令的引擎，执行复制命令的引擎
//    （就是从CPU内存中复制内容到显存中或反之或GPU内部以及引擎之间），执行通用计算命令的引擎（执行Computer
//    Shader的引擎）以及可以进行视频编码解码的视频引擎等。而在D3D12中针对这些不同的引擎，就需要创建不同的命
//    令队列接口来代表不同的引擎对象了。这相较于传统的D3D9或者D3D11设备接口来说，不但接口被拆分了，而且在对
//    象概念层级上都进行了拆分。形象的理解如下图所示：*/
//    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
//    queueDesc.Type = XmlConfigHelper::GetCommandListType(desc_element->Attribute("command_list_type"));//D3D12_COMMAND_LIST_TYPE_DIRECT;
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pICommandQueue)), __FILE__, __LINE__);
//}
//
//void Dx12Application::CreateSwapchain(XMLElement* desc_element)
//{
//    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
//    swapChainDesc.BufferCount = nFrameBackBufCount;
//    swapChainDesc.Width = m_WindowWidth;
//    swapChainDesc.Height = m_WindowHeight;
//    swapChainDesc.Format = XmlConfigHelper::GetDXGIFormat(desc_element->Attribute("swapchain_format"));//DXGI_FORMAT_R8G8B8A8_UNORM;
//    swapChainDesc.BufferUsage = XmlConfigHelper::GetDXGIUsage(desc_element->Attribute("buffer_usage"));// DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    swapChainDesc.SwapEffect = XmlConfigHelper::GetDXGISwapEffect(desc_element->Attribute("swap_effect"));//DXGI_SWAP_EFFECT_FLIP_DISCARD;
//    swapChainDesc.SampleDesc.Count = XmlConfigHelper::AttributeValue(desc_element->Attribute("sample_desc_count"), 1);//1;
//
//    Error::GRS_THROW_IF_FAILED(pIDXGIFactory5->CreateSwapChainForHwnd(
//        pICommandQueue,     // Swap chain needs the queue so that it can force a flush on it.
//        m_hWnd,
//        &swapChainDesc,
//        nullptr,
//        nullptr,
//        &pISwapChain1), __FILE__, __LINE__);
//
//    Error::GRS_THROW_IF_FAILED(pISwapChain1->QueryInterface<IDXGISwapChain3>(&pISwapChain3), __FILE__, __LINE__);
//    DX12_FRAMEWORK_SAFE_RELEASE(pISwapChain1);
//
//    nFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();
//}
//
//void Dx12Application::CreateHeapDescriptor(XMLElement* desc_element)
//{
//    //7、创建RTV(渲染目标视图)描述符堆(这里堆的含义应当理解为数组或者固定大小元素的固定大小显存池)
//    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
//    rtvHeapDesc.NumDescriptors = nFrameBackBufCount;
//    rtvHeapDesc.Type = XmlConfigHelper::GetDescriptorHeapType(desc_element->Attribute("descriptor_heap_type")); //D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
//    rtvHeapDesc.Flags = XmlConfigHelper::GetDescriptorHeapFlags(desc_element->Attribute("descriptor_heap_flags")); //D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&pIRTVHeap)), __FILE__, __LINE__);
//
//    //得到每个描述符元素的大小
//    nRTVDescriptorSize = pID3DDevice->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
//}
//
////9、创建一个空的根描述符，也就是默认的根描述符
//void Dx12Application::CreateDefaultRootSignature(XMLElement* desc_element)
//{
//    CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
//    rootSignatureDesc.Init(0, nullptr, 0, nullptr,
//        XmlConfigHelper::GetRootSignatureFlags(desc_element->Attribute("root_signature_flags"))//D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
//    );
//
//    ID3DBlob* signature = nullptr;
//    ID3DBlob* error = nullptr;
//    Error::GRS_THROW_IF_FAILED(D3D12SerializeRootSignature(&rootSignatureDesc,
//        XmlConfigHelper::GetRootSignatureVersion(desc_element->Attribute("root_signature_version")),//D3D_ROOT_SIGNATURE_VERSION_1
//        &signature, &error), __FILE__, __LINE__);
//
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&pIRootSignature)), __FILE__, __LINE__);
//    DX12_FRAMEWORK_SAFE_RELEASE(signature);
//    DX12_FRAMEWORK_SAFE_RELEASE(error);
//}
//
//void Dx12Application::CreateRenderTargetViewDescriptor(XMLElement* desc_element)
//{
//    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart());
//
//    for (UINT i = 0; i < nFrameBackBufCount; i++)
//    {
//        Error::GRS_THROW_IF_FAILED(pISwapChain3->GetBuffer(i, IID_PPV_ARGS(&pIARenderTargets[i])), __FILE__, __LINE__);
//        pID3DDevice->CreateRenderTargetView(pIARenderTargets[i], nullptr, rtvHandle);
//        rtvHandle.Offset(1, nRTVDescriptorSize);
//    }
//}
//
//void Dx12Application::CreatePipelineState(XMLElement* desc_element)
//{
//    ID3DBlob* vertexShader = nullptr;
//    ID3DBlob* pixelShader = nullptr;
//
//#if defined(_DEBUG)
//    UINT compileFlags = XmlConfigHelper::ParseShaderCompileFlags(desc_element->Attribute("debug_compile_flags"));
//#else
//    UINT compileFlags = XmlConfigHelper::ParseShaderCompileFlags(desc_element->Attribute("compile_flags"));
//#endif
//
//    TCHAR* pszShaderFileName = nullptr;
//    const char* utf8_shader_file_name = desc_element->Attribute("shader_file_name");
//    tstring shader_file_name;
//#if defined(UNICODE)
//    shader_file_name = StringConvertor::UTF8toUTF16LE(utf8_shader_file_name);
//#else
//    shader_file_name = StringConvertor::UTF8toGBK(utf8_shader_file_name);
//#endif
//
//    const char* vertex_shader_entry_point = desc_element->Attribute("vertex_shader_entry_point");
//    const char* vertex_shader_target_version = desc_element->Attribute("vertex_shader_target_version");
//    const char* fragment_shader_entry_point = desc_element->Attribute("fragment_shader_entry_point");
//    const char* fragment_shader_target_version = desc_element->Attribute("fragment_shader_target_version");
//
//    Error::GRS_THROW_IF_FAILED(D3DCompileFromFile(shader_file_name.c_str(), nullptr, nullptr,
//        vertex_shader_entry_point, vertex_shader_target_version, compileFlags, 0, &vertexShader, nullptr), __FILE__, __LINE__);
//    Error::GRS_THROW_IF_FAILED(D3DCompileFromFile(shader_file_name.c_str(), nullptr, nullptr,
//        fragment_shader_entry_point, fragment_shader_target_version, compileFlags, 0, &pixelShader, nullptr), __FILE__, __LINE__);
//
//    // Define the vertex input layout.
//    //D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
//    //{
//    //    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//    //    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
//    //};
//
//    std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescs;
//    XmlConfigHelper::GetInputElementDesc(inputElementDescs, desc_element->FirstChildElement("all_input_element_desc"));
//    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
//    psoDesc.InputLayout = { inputElementDescs.data(), inputElementDescs.size()/*_countof(inputElementDescs)*/ };
//    psoDesc.pRootSignature = pIRootSignature;
//    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
//    psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
//    XmlConfigHelper::InitGraphicsPipelineStateDesc(&psoDesc, desc_element->FirstChildElement("D3D12_GRAPHICS_PIPELINE_STATE_DESC"));
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pIPipelineState)), __FILE__, __LINE__);
//}
//
//void Dx12Application::CreateRenderStuff(XMLElement* render_stuff_elem)
//{
//
//}
//
//void Dx12Application::CreateCommands(XMLElement* cmd_alloc_elem)
//{
//    D3D12_COMMAND_LIST_TYPE cmd_list_type = XmlConfigHelper::GetCommandListType(cmd_alloc_elem->Attribute("command_list_type"));
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateCommandAllocator(
//        cmd_list_type, IID_PPV_ARGS(&pICommandAllocator)), __FILE__, __LINE__);
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateCommandList(
//        0, cmd_list_type, pICommandAllocator, pIPipelineState, IID_PPV_ARGS(&pICommandList)), __FILE__, __LINE__);
//}
//
//void Dx12Application::CreateFence(XMLElement* fence_elem)
//{
//    // 14、创建一个同步对象——围栏，用于等待渲染完成，因为现在Draw Call是异步的了
//    Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pIFence)), __FILE__, __LINE__);
//    n64FenceValue = 1;
//
//    // 15、创建一个Event同步对象，用于等待围栏事件通知
//    hFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
//
//    if (hFenceEvent == nullptr)
//    {
//        Error::GRS_THROW_IF_FAILED(HRESULT_FROM_WIN32(GetLastError()), __FILE__, __LINE__);
//    }
//}
//
//void Dx12Application::InitRenderer(XMLElement* renderer_element)
//{
//#if defined(_DEBUG)
//    //打开显示子系统的调试支持
//    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
//    {
//        debugController->EnableDebugLayer();
//        nDXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG; // 打开附加的调试支持
//    }
//#endif
//    XMLElement* element = renderer_element->FirstChildElement("dxgi_factory");
//    CreateDXGIFactory(element);
//
//    element = renderer_element->FirstChildElement("adapter_and_device");
//    EnumerateAdapterAndCreateDevice(element); //2、枚举适配器，并选择合适的适配器来创建3D设备对象 3、创建D3D12.1的设备
//
//    element = renderer_element->FirstChildElement("command_queue");
//    CreateDefaultCommandQueue(element); //4、创建直接命令队列
//
//    element = renderer_element->FirstChildElement("swap_chain");
//    CreateSwapchain(element);//5、创建交换链 6、得到当前后缓冲区的序号，也就是下一个将要呈送显示的缓冲区的序号
//
//    element = renderer_element->FirstChildElement("heap_descriptor");
//    CreateHeapDescriptor(element);//7、创建RTV(渲染目标视图)描述符堆(这里堆的含义应当理解为数组或者固定大小元素的固定大小显存池)
//
//    element = renderer_element->FirstChildElement("rtv_descriptor");
//    CreateRenderTargetViewDescriptor(element);//8、创建RTV的描述符
//
//    element = renderer_element->FirstChildElement("default_root_signature");
//    CreateDefaultRootSignature(element);//9、创建一个空的根描述符，也就是默认的根描述符
//
//    element = renderer_element->FirstChildElement("pipeline_state");
//    CreatePipelineState(element);// 10、编译Shader创建渲染管线状态对象
//
//    element = renderer_element->FirstChildElement("render_stuff"); // 创建各种渲染用的数据，比如顶点，纹理，等等
//    CreateRenderStuff(element);
//
//    element = renderer_element->FirstChildElement("commands"); // 12、创建命令列表 13 创建图形命令列表
//    CreateCommands(element);
//
//    element = renderer_element->FirstChildElement("fence"); // 14、创建一个同步对象——围栏，用于等待渲染完成  15、创建一个Event同步对象，用于等待围栏事件通知
//    CreateFence(element);
//
//
//    //16、创建定时器对象，以便于创建高效的消息循环
//    HANDLE phWait = CreateWaitableTimer(nullptr, FALSE, nullptr);
//    LARGE_INTEGER liDueTime = {};
//    liDueTime.QuadPart = -1i64;//1秒后开始计时
//    SetWaitableTimer(phWait, &liDueTime, 1, nullptr, nullptr, 0);//40ms的周期
//}
//
//void Dx12Application::ReleaseRenderer()
//{
//    DX12_FRAMEWORK_SAFE_RELEASE(pIDXGIFactory5);
//    DX12_FRAMEWORK_SAFE_RELEASE(pIAdapter);
//    DX12_FRAMEWORK_SAFE_RELEASE(pID3DDevice);
//    DX12_FRAMEWORK_SAFE_RELEASE(pICommandQueue);
//    DX12_FRAMEWORK_SAFE_RELEASE(pISwapChain1);
//    DX12_FRAMEWORK_SAFE_RELEASE(pISwapChain3);
//    DX12_FRAMEWORK_SAFE_RELEASE(pIRTVHeap);
//    DX12_FRAMEWORK_SAFE_RELEASE(pICommandAllocator);
//    DX12_FRAMEWORK_SAFE_RELEASE(pIRootSignature);
//    DX12_FRAMEWORK_SAFE_RELEASE(pIPipelineState);
//    DX12_FRAMEWORK_SAFE_RELEASE(pICommandList);
//    DX12_FRAMEWORK_SAFE_RELEASE(pIVertexBuffer);
//    DX12_FRAMEWORK_SAFE_RELEASE(pIFence);
//
//    for (auto rt : pIARenderTargets)
//    {
//        DX12_FRAMEWORK_SAFE_RELEASE(rt);
//    }
//}
//
LRESULT WINAPI Dx12Application::MessageHandler(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, Message, wParam, lParam);
}