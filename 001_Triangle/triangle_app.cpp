#include "triangle_app.h"
#include "triangle_app_renderer.h"
#include "../Framework/error.h"
#include "../Framework/string_convertor.h"

void TriangleApp::CreateDX12Renderer()
{
    dx12_renderer_ = new TriangleAppRenderer(m_hWnd, m_WindowWidth,m_WindowHeight);
    dx12_renderer_->InitializeDXGIDevice(nullptr);
    dx12_renderer_->InitializeCommand(nullptr);
    dx12_renderer_->CreateSwapChain(nullptr);
    dx12_renderer_->CreateFinalRenderTargets(nullptr);
    dx12_renderer_->CreateSceneView(nullptr);
    dx12_renderer_->CreateDepthStencilView(nullptr);
    dx12_renderer_->CreateFence(nullptr);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    try
    {
        g_pDx12App = new TriangleApp();
        g_pDx12App->Init();
        g_pDx12App->Run();	
    }
    catch (Error e)
    {
        e.Notify();
    }
    catch (std::exception e)
    {
        std::wstring excepiton_desc;
        StringConvertor::ANSItoUTF16LE(e.what(), excepiton_desc);
        ::MessageBox(nullptr, excepiton_desc.c_str(), _T("Unhandled Exception, aborting"), MB_OK | MB_ICONERROR);
    }

    delete (g_pDx12App);
    return 0;
}