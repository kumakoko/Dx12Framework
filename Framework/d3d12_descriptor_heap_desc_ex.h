#ifndef d3d12_descriptor_heap_desc_ex_h__
#define d3d12_descriptor_heap_desc_ex_h__

class D3D12DescriptorHeapDescEx : public D3D12_DESCRIPTOR_HEAP_DESC
{
public:
    /*********************************************************************************
     * @brief:
     * @return: 
     *********************************************************************************/
    D3D12DescriptorHeapDescEx();

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  const D3D12_DESCRIPTOR_HEAP_DESC & o
     *********************************************************************************/
    explicit D3D12DescriptorHeapDescEx(const D3D12_DESCRIPTOR_HEAP_DESC &o);

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  const XMLElement * elem
     *********************************************************************************/
    D3D12DescriptorHeapDescEx(const XMLElement* elem);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem
     *********************************************************************************/
    void Init(const XMLElement* elem);
};


#endif // d3d12_descriptor_heap_desc_ex_h__
