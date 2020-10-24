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
#include "d3d12_clear_value_ex.h"
#include "error.h"

#include "xml_config_helper.h"

D3D12ClearValueEx::D3D12ClearValueEx()
{
}

D3D12ClearValueEx::D3D12ClearValueEx(const CD3DX12_CLEAR_VALUE &o) : CD3DX12_CLEAR_VALUE(o)
{
}

D3D12ClearValueEx::D3D12ClearValueEx(DXGI_FORMAT format,const FLOAT color[4])
{
    Format = format;
    memcpy(Color, color, sizeof(Color));
}

D3D12ClearValueEx::D3D12ClearValueEx(DXGI_FORMAT format,FLOAT depth,UINT8 stencil)
{
    Format = format;
    memcpy(&DepthStencil.Depth, &depth, sizeof(depth));
    DepthStencil.Stencil = stencil;
}

D3D12ClearValueEx::D3D12ClearValueEx(const XMLElement* elem)
{
    this->Init(elem);
}

void D3D12ClearValueEx::Init(const XMLElement* elem)
{
    bool use_stencil = XmlConfigHelper::AttributeValue(elem, "use_stencil", true);
    this->Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("format"));

    if (use_stencil)
    {
        this->DepthStencil.Depth = XmlConfigHelper::AttributeValue(elem, "depth", 1.0f);
        this->DepthStencil.Stencil = XmlConfigHelper::AttributeValue(elem, "stencil", 0);
    }
    else
    {
        XMFLOAT4 clear_color = XmlConfigHelper::AttributeVector4(elem, "color", 0.0f);
        memcpy(this->Color, &clear_color, sizeof(Color));
    }
}