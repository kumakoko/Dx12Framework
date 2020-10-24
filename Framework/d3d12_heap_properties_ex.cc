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
#include "d3d12_heap_properties_ex.h"
#include "error.h"
#include "xml_config_helper.h"

D3D12HeapPropertiesEx::D3D12HeapPropertiesEx()
{}

D3D12HeapPropertiesEx::D3D12HeapPropertiesEx(const CD3DX12_HEAP_PROPERTIES& o) : CD3DX12_HEAP_PROPERTIES(o)
{
}

D3D12HeapPropertiesEx::D3D12HeapPropertiesEx(D3D12_CPU_PAGE_PROPERTY cpu_page_property, D3D12_MEMORY_POOL memory_pool_preference, UINT creation_node_mask = 1, UINT node_mask = 1) :
    CD3DX12_HEAP_PROPERTIES(cpu_page_property, memory_pool_preference, creation_node_mask, node_mask)
{
}

D3D12HeapPropertiesEx::D3D12HeapPropertiesEx(D3D12_HEAP_TYPE type, UINT creationNodeMask, UINT nodeMask) : 
    CD3DX12_HEAP_PROPERTIES(type, creationNodeMask, nodeMask)
{
}

D3D12HeapPropertiesEx::D3D12HeapPropertiesEx(const XMLElement* elem)
{
    Init(elem);
}

void D3D12HeapPropertiesEx::Init(const XMLElement* elem)
{
    bool use_custom_struct = XmlConfigHelper::AttributeValue(elem, "use_custom_struct", false);
    this->CreationNodeMask = XmlConfigHelper::AttributeValue(elem, "CreationNodeMask", 1);
    this->VisibleNodeMask = XmlConfigHelper::AttributeValue(elem, "VisibleNodeMask", 1);

    // 根据使用自定义的格式与否，填充不同的结构
    if (use_custom_struct)
    {
        this->Type = D3D12_HEAP_TYPE_CUSTOM;
        this->CPUPageProperty = XmlConfigHelper::GetCpuPagePropertyType(elem->Attribute("CPUPageProperty"));
        this->MemoryPoolPreference = XmlConfigHelper::GetMemoryPoolType(elem->Attribute("MemoryPoolPreference"));
    }
    else
    {
        this->Type = XmlConfigHelper::GetHeapType(elem->Attribute("Type"));
        this->CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        this->MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    }
}