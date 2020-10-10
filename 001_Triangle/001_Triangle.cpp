#include "001_Triangle.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	g_pDx12App = new TriangleApp();
	g_pDx12App->Go();
	delete (g_pDx12App);
	return 0;
}