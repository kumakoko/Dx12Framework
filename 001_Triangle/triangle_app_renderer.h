#ifndef triangle_app_renderer_h__
#define triangle_app_renderer_h__

#include "../Framework/dx12_renderer.h"

class TriangleAppRenderer : public Dx12Renderer
{
public:
    TriangleAppRenderer(HWND wnd_handle, UINT wnd_width, UINT wnd_height);
};

#endif // triangle_app_renderer_h__