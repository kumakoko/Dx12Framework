#include "001_Triangle.h"
#include "../Framework/error.h"
#include "../Framework/string_convertor.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	try
	{
		g_pDx12App = new TriangleApp();
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