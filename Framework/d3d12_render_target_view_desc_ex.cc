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
#include "string_convertor.h"
#include "d3d12_render_target_view_desc_ex.h"
#include "error.h"
#include "xml_config_helper.h"

D3D12RenderTargetViewDescEx::D3D12RenderTargetViewDescEx()
{
}

D3D12RenderTargetViewDescEx::D3D12RenderTargetViewDescEx(const XMLElement* elem)
{
    Init(elem);
}

D3D12RenderTargetViewDescEx::D3D12RenderTargetViewDescEx(const D3D12_RENDER_TARGET_VIEW_DESC &o) :
    D3D12_RENDER_TARGET_VIEW_DESC(o)
{
}

void D3D12RenderTargetViewDescEx::Init(const XMLElement* elem)
{
    this->Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("format"));
    this->ViewDimension = XmlConfigHelper::GetRenderTargetDimensionType(elem->Attribute("view_dimension"));
}