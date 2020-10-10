#include "pch.h"
#include "dx12_application.h"
#include "error.h"

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

Dx12Application::Dx12Application()
{
	m_WindowWidth = 1024;
	m_WindowHeight = 768;
}

void Dx12Application::Go()
{
	WNDCLASSEX WindowClass = { sizeof(WNDCLASSEX),CS_CLASSDC,
							  Dx12Application::WindowsProcedure,
							  0,0,GetModuleHandle(nullptr),
							  nullptr,nullptr,nullptr,nullptr,
							  _T("Dx12 Application"),
							  nullptr };
	RegisterClassEx(&WindowClass);

	m_hWnd = CreateWindow(_T("Dx12 Application"), _T("Dx12 Application"), WS_OVERLAPPEDWINDOW,
		0, 0, m_WindowWidth, m_WindowHeight, GetDesktopWindow(), nullptr, WindowClass.hInstance, nullptr);

	if (m_hWnd)
		ShowWindow(m_hWnd, SW_SHOW);
	else
		return;

	InitRenderDevice(nullptr);

	MSG Message;
	PeekMessage(&Message, 0, 0, 0, PM_REMOVE);

	while (Message.message != WM_QUIT)
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		PeekMessage(&Message, 0, 0, 0, PM_REMOVE);
	}
}

Dx12Application::~Dx12Application()
{
	ReleaseRenderDevice();
	if (m_hWnd)
		DestroyWindow(m_hWnd);
}


void Dx12Application::EnumerateAdapter(XMLElement* desc_element)
{
	for (UINT adapterIndex = 1; DXGI_ERROR_NOT_FOUND != pIDXGIFactory5->EnumAdapters1(adapterIndex, &pIAdapter); ++adapterIndex)
	{
		DXGI_ADAPTER_DESC1 desc = {};
		pIAdapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{//跳过软件虚拟适配器设备
			continue;
		}
		//检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
		//就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！
		if (SUCCEEDED(D3D12CreateDevice(pIAdapter, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
		{
			break;
		}
	}
}


void Dx12Application::InitDXGIFactory(XMLElement* desc_element)
{
	//1、创建DXGI Factory对象 	// 关闭ALT+ENTER键切换全屏的功能，因为我们没有实现OnSize处理，所以先关闭
	Error::GRS_THROW_IF_FAILED(CreateDXGIFactory2(nDXGIFactoryFlags, IID_PPV_ARGS(&pIDXGIFactory5)), __FILE__, __LINE__);
	Error::GRS_THROW_IF_FAILED(pIDXGIFactory5->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER), __FILE__, __LINE__);
}

void Dx12Application::CreateD3DDevice(XMLElement* desc_element)
{
	Error::GRS_THROW_IF_FAILED(D3D12CreateDevice(pIAdapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&pID3DDevice)), __FILE__, __LINE__);
}

void Dx12Application::CreateDefaultCommandQueue(XMLElement* desc_element)
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pICommandQueue)), __FILE__, __LINE__);
}

void Dx12Application::CreateSwapchain(XMLElement* desc_element)
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = nFrameBackBufCount;
	swapChainDesc.Width = m_WindowWidth;
	swapChainDesc.Height = m_WindowHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	Error::GRS_THROW_IF_FAILED(pIDXGIFactory5->CreateSwapChainForHwnd(
		pICommandQueue,		// Swap chain needs the queue so that it can force a flush on it.
		m_hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&pISwapChain1), __FILE__, __LINE__);
	//?
	// Error::GRS_THROW_IF_FAILED(pISwapChain1.As(&pISwapChain3));
}

void Dx12Application::CreateHeapDescriptor(XMLElement* desc_element)
{
	//7、创建RTV(渲染目标视图)描述符堆(这里堆的含义应当理解为数组或者固定大小元素的固定大小显存池)
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = nFrameBackBufCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	Error::GRS_THROW_IF_FAILED(pID3DDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&pIRTVHeap)), __FILE__, __LINE__);
	//得到每个描述符元素的大小
	nRTVDescriptorSize = pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void Dx12Application::InitRenderDevice(XMLElement* desc_element)
{
#if defined(_DEBUG)
	//打开显示子系统的调试支持
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		nDXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG; // 打开附加的调试支持
	}
#endif
	InitDXGIFactory(nullptr);
	EnumerateAdapter(nullptr); //2、枚举适配器，并选择合适的适配器来创建3D设备对象
	CreateD3DDevice(nullptr); //3、创建D3D12.1的设备
	CreateDefaultCommandQueue(nullptr); //4、创建直接命令队列
	CreateSwapchain(nullptr);//5、创建交换链


	//6、得到当前后缓冲区的序号，也就是下一个将要呈送显示的缓冲区的序号
	//注意此处使用了高版本的SwapChain接口的函数
	nFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();

	CreateHeapDescriptor(nullptr);//7、创建RTV(渲染目标视图)描述符堆(这里堆的含义应当理解为数组或者固定大小元素的固定大小显存池)

/*
	//8、创建RTV的描述符
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart());
		for (UINT i = 0; i < nFrameBackBufCount; i++)
		{
			GRS_THROW_IF_FAILED(pISwapChain3->GetBuffer(i, IID_PPV_ARGS(&pIARenderTargets[i])));
			pID3DDevice->CreateRenderTargetView(pIARenderTargets[i].Get(), nullptr, rtvHandle);
			rtvHandle.Offset(1, nRTVDescriptorSize);
		}
	}

	//9、创建一个空的根描述符，也就是默认的根描述符
	{
		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		GRS_THROW_IF_FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		GRS_THROW_IF_FAILED(pID3DDevice->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&pIRootSignature)));
	}

	// 10、编译Shader创建渲染管线状态对象
	{
		ComPtr<ID3DBlob> vertexShader;
		ComPtr<ID3DBlob> pixelShader;

#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif
		TCHAR pszShaderFileName[] = _T("D:\\Projects_2018_08\\D3DPipelineTest\\D3D12Trigger\\Shader\\shaders.hlsl");
		GRS_THROW_IF_FAILED(D3DCompileFromFile(pszShaderFileName, nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
		GRS_THROW_IF_FAILED(D3DCompileFromFile(pszShaderFileName, nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = pIRootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;

		GRS_THROW_IF_FAILED(pID3DDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pIPipelineState)));
	}
	*/
}

void Dx12Application::ReleaseRenderDevice()
{
	DX12_FRAMEWORK_SAFE_RELEASE(pIDXGIFactory5);
	DX12_FRAMEWORK_SAFE_RELEASE(pIAdapter);
	DX12_FRAMEWORK_SAFE_RELEASE(pID3DDevice);
	DX12_FRAMEWORK_SAFE_RELEASE(pICommandQueue);
	DX12_FRAMEWORK_SAFE_RELEASE(pISwapChain1);
	DX12_FRAMEWORK_SAFE_RELEASE(pISwapChain3);
	DX12_FRAMEWORK_SAFE_RELEASE(pIRTVHeap);
	DX12_FRAMEWORK_SAFE_RELEASE(pICommandAllocator);
	DX12_FRAMEWORK_SAFE_RELEASE(pIRootSignature);
	DX12_FRAMEWORK_SAFE_RELEASE(pIPipelineState);
	DX12_FRAMEWORK_SAFE_RELEASE(pICommandList);
	DX12_FRAMEWORK_SAFE_RELEASE(pIVertexBuffer);
	DX12_FRAMEWORK_SAFE_RELEASE(pIFence);

	for (auto rt : pIARenderTargets)
	{
		DX12_FRAMEWORK_SAFE_RELEASE(rt);
	}
}


LRESULT WINAPI Dx12Application::MessageHandler(HWND hWnd,
	UINT Message,
	WPARAM wParam,
	LPARAM lParam)
{
	return DefWindowProc(hWnd, Message, wParam, lParam);
}