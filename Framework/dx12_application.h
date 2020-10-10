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
	virtual void ReleaseRenderDevice();
	virtual void InitRenderDevice(XMLElement* desc_element);
	virtual void InitDXGIFactory(XMLElement* desc_element);
	virtual void EnumerateAdapter(XMLElement* desc_element);
	virtual void CreateD3DDevice(XMLElement* desc_element);
	virtual void CreateDefaultCommandQueue(XMLElement* desc_element);
	virtual void CreateSwapchain(XMLElement* desc_element);
	virtual void CreateHeapDescriptor(XMLElement* desc_element);
protected:
	HWND m_hWnd;
	long m_WindowWidth;
	long m_WindowHeight;
	UINT nDXGIFactoryFlags = 0U; // DXGI的创建标识
	UINT nRTVDescriptorSize = 0U;
	UINT nFrameIndex = 0U;
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