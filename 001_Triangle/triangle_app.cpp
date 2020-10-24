#include "triangle_app.h"
#include "triangle_app_renderer.h"
#include "../Framework/error.h"
#include "../Framework/string_convertor.h"

void TriangleApp::CreateDX12Renderer()
{
    dx12_renderer_ = new TriangleAppRenderer(m_hWnd, m_WindowWidth,m_WindowHeight);

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError ret = doc.LoadFile("default_renderer_setting.xml");
    Error::ThrowTinyXMLException(ret, std::wstring(L"default_renderer_setting.xml"), __FILE__, __LINE__);
    
    const XMLElement* elem = doc.FirstChildElement("renderer");

    dx12_renderer_->InitializeDXGIDevice(elem->FirstChildElement("dxgi_factory_adapter_device"));
    dx12_renderer_->InitializeCommand(elem->FirstChildElement("commands"));
    dx12_renderer_->CreateSwapChain(elem->FirstChildElement("swap_chain"));
    dx12_renderer_->CreateFinalRenderTargets(elem->FirstChildElement("final_render_target"));
    dx12_renderer_->CreateSceneView(nullptr);
    dx12_renderer_->CreateDepthStencilView(elem->FirstChildElement("default_depth_stencil_view"));
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