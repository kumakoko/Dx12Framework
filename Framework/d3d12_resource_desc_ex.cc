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
#include "d3d12_resource_desc_ex.h"
#include "error.h"
#include "xml_config_helper.h"

D3D12ResourceDescEx::D3D12ResourceDescEx()
{
}

D3D12ResourceDescEx::D3D12ResourceDescEx(const D3D12_RESOURCE_DESC &o) :D3D12_RESOURCE_DESC(o)
{
}

D3D12ResourceDescEx::D3D12ResourceDescEx(const XMLElement* elem, UINT64 w, UINT h)
{
    Init(elem, w, h);
}

D3D12ResourceDescEx::D3D12ResourceDescEx(const XMLElement* elem)
{
    Init(elem);
}

void D3D12ResourceDescEx::Init(const XMLElement* elem)
{
    this->Dimension = XmlConfigHelper::GetResourceDimensionType(elem->Attribute("Dimension")); //D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    this->Flags = XmlConfigHelper::GetResourceFlagsType(elem->Attribute("Flags"));//D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    this->Layout = XmlConfigHelper::GetTextureLayoutType(elem->Attribute("Layout"));//D3D12_TEXTURE_LAYOUT_UNKNOWN;
    this->Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("Format"));//DXGI_FORMAT_D32_FLOAT;
    this->DepthOrArraySize = XmlConfigHelper::AttributeValue(elem, "DepthOrArraySize", 1); //1;
    this->SampleDesc.Count = XmlConfigHelper::AttributeValue(elem, "SampleDescCount", 1); //1;
    this->SampleDesc.Quality = XmlConfigHelper::AttributeValue(elem, "SampleDescQuality", 0); //0;
    this->MipLevels = XmlConfigHelper::AttributeValue(elem, "MipLevels", 1); //1;
    this->Alignment = XmlConfigHelper::AttributeValue(elem, "Alignment", 0); //0;
    this->Width = XmlConfigHelper::AttributeValue(elem, "Width", 0);
    this->Height = XmlConfigHelper::AttributeValue(elem, "Height", 0);
}

void D3D12ResourceDescEx::Init(const XMLElement* elem, UINT64 w, UINT h)
{
    this->Width = w;
    this->Height = h;
    this->Dimension = XmlConfigHelper::GetResourceDimensionType(elem->Attribute("Dimension")); //D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    this->Flags = XmlConfigHelper::GetResourceFlagsType(elem->Attribute("Flags"));//D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    this->Layout = XmlConfigHelper::GetTextureLayoutType(elem->Attribute("Layout"));//D3D12_TEXTURE_LAYOUT_UNKNOWN;
    this->Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("Format"));//DXGI_FORMAT_D32_FLOAT;
    this->DepthOrArraySize = XmlConfigHelper::AttributeValue(elem, "DepthOrArraySize", 1); //1;
    this->SampleDesc.Count = XmlConfigHelper::AttributeValue(elem, "SampleDescCount", 1); //1;
    this->SampleDesc.Quality = XmlConfigHelper::AttributeValue(elem, "SampleDescQuality", 0); //0;
    this->MipLevels = XmlConfigHelper::AttributeValue(elem, "MipLevels", 1); //1;
    this->Alignment = XmlConfigHelper::AttributeValue(elem, "Alignment", 0); //0;
}