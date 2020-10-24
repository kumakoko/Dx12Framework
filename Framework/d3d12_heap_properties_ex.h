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
#ifndef d3d12_heap_properties_ex_h__
#define d3d12_heap_properties_ex_h__

class DX12_FRAMEWORK_DLL D3D12HeapPropertiesEx : public CD3DX12_HEAP_PROPERTIES
{
public:
    /*********************************************************************************
     * @brief:
     * @return: 
     *********************************************************************************/
    D3D12HeapPropertiesEx();

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  const XMLElement * elem
     *********************************************************************************/
    D3D12HeapPropertiesEx(const XMLElement* elem);

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  const CD3DX12_HEAP_PROPERTIES & o
     *********************************************************************************/
    explicit D3D12HeapPropertiesEx(const CD3DX12_HEAP_PROPERTIES& o);

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  D3D12_CPU_PAGE_PROPERTY cpu_page_property
     * @param:  D3D12_MEMORY_POOL memory_pool_preference
     * @param:  UINT creation_node_mask
     * @param:  UINT node_mask
     *********************************************************************************/
    D3D12HeapPropertiesEx(D3D12_CPU_PAGE_PROPERTY cpu_page_property, D3D12_MEMORY_POOL memory_pool_preference, UINT creation_node_mask, UINT node_mask);

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  D3D12_HEAP_TYPE type
     * @param:  UINT creationNodeMask
     * @param:  UINT nodeMask
     *********************************************************************************/
    explicit D3D12HeapPropertiesEx(D3D12_HEAP_TYPE type,UINT creationNodeMask = 1,UINT nodeMask = 1);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem
     *********************************************************************************/
    void Init(const XMLElement* elem);
};

#endif // d3d12_heap_properties_ex_h__