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
#ifndef xml_config_helper_h__
#define xml_config_helper_h__

#include "string_convertor.h"
#include "error.h"

class DX12_FRAMEWORK_DLL XmlConfigHelper
{
public:
    /*********************************************************************************
     * @brief:
     * @return: D3D12_DSV_FLAGS
     * @param:  const char * flag_type
     *********************************************************************************/
    static D3D12_DSV_FLAGS GetDSVFlagsType(const char* flag_type);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_DSV_DIMENSION
     * @param:  const char * heap_flag_type
     *********************************************************************************/
    static D3D12_DSV_DIMENSION GetDSVDimensionType(const char* dsv_dim_type);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_RESOURCE_STATES
     * @param:  const char * state_name
     *********************************************************************************/
    static D3D12_RESOURCE_STATES GetD3D12ResourceStates(const char* state_name);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_HEAP_FLAGS
     * @param:  const char * heap_flag_type
     *********************************************************************************/
    static D3D12_HEAP_FLAGS GetHeapFlagType(const char* heap_flag_type);

    /*********************************************************************************
     * @brief: 从XML文件中读取出D3D12_MEMORY_POOL类型的值
     * @return: D3D12_MEMORY_POOL 返回一个在xml中指定的D3D12_MEMORY_POOL类型的值
     * @param:  const char * mem_pool D3D12_MEMORY_POOL类型变量字符串
     *********************************************************************************/
    static D3D12_MEMORY_POOL GetMemoryPoolType(const char* mem_pool);

    /*********************************************************************************
     * @brief:  从XML文件中读取出D3D12_CPU_PAGE_PROPERTY类型的值
     * @return: D3D12_CPU_PAGE_PROPERTY 返回一个在xml中指定的D3D12_CPU_PAGE_PROPERTY类型的值
     * @param:  const char * cpu_page_prop D3D12_CPU_PAGE_PROPERTY类型变量字符串
     *********************************************************************************/
    static D3D12_CPU_PAGE_PROPERTY GetCpuPagePropertyType(const char* cpu_page_prop);

    /*********************************************************************************
     * @brief: 从XML文件中读取出D3D12_HEAP_TYPE类型的值
     * @return: D3D12_HEAP_TYPE 返回一个在xml中指定的D3D12_HEAP_TYPE类型的值
     * @param:  const char * heap_type D3D12_HEAP_TYPE类型变量字符串
     *********************************************************************************/
    static D3D12_HEAP_TYPE GetHeapType(const char* heap_type);

    /*********************************************************************************
     * @brief: 从XML文件中读取出D3D12_TEXTURE_LAYOUT类型的值
     * @return: D3D12_TEXTURE_LAYOUT 返回一个在xml中指定的D3D12_TEXTURE_LAYOUT类型的值
     * @param:  const char * texture_layout_type D3D12_TEXTURE_LAYOUT类型变量字符串
     *********************************************************************************/
    static D3D12_TEXTURE_LAYOUT GetTextureLayoutType(const char* texture_layout_type);

    /*********************************************************************************
     * @brief: 从XML文件中读取出D3D12_RESOURCE_FLAGS类型的值
     * @return: D3D12_RESOURCE_FLAGS  返回一个在xml中指定的D3D12_RESOURCE_FLAGS类型的值
     * @param:  const char * res_flag_type D3D12_RESOURCE_FLAGS类型变量字符串
     *********************************************************************************/
    static D3D12_RESOURCE_FLAGS GetResourceFlagsType(const char* res_flag_type);

    /*********************************************************************************
     * @brief: 从XML文件中读取出D3D12_COMMAND_QUEUE_FLAGS类型的值
     * @return: D3D12_COMMAND_QUEUE_FLAGS 返回一个在xml中指定的D3D12_COMMAND_QUEUE_FLAGS类型的值
     * @param:  const char * command_queue_flags D3D12_COMMAND_QUEUE_FLAGS类型变量字符串
     *********************************************************************************/
    static D3D12_COMMAND_QUEUE_FLAGS GetCommandQueueFlag(const char* command_queue_flags);

    /*********************************************************************************
     * @brief: 从XML文件中读取出D3D12_COMMAND_QUEUE_PRIORITY类型的值
     * @return: D3D12_COMMAND_QUEUE_PRIORITY 返回一个在xml中指定的D3D12_COMMAND_QUEUE_PRIORITY类型的值
     * @param:  const char * command_queue_priority D3D12_COMMAND_QUEUE_PRIORITY类型变量字符串
     *********************************************************************************/
    static D3D12_COMMAND_QUEUE_PRIORITY GetCommandQueuePriority(const char* command_queue_priority);

    /*********************************************************************************
     * @brief:  从XML文件中读取出D3D12_RTV_DIMENSION类型的值
     * @return: D3D12_RTV_DIMENSION 返回一个在xml中指定的D3D12_RTV_DIMENSION类型的值
     * @param:  const char * rtv_dimension_type D3D12_RTV_DIMENSION类型变量字符串
     *********************************************************************************/
    static D3D12_RTV_DIMENSION GetRenderTargetDimensionType(const char* rtv_dimension_type);

    /*********************************************************************************
     * @brief:  从XML文件中读取出D3D12_RESOURCE_DIMENSION类型的值
     * @return: D3D12_RESOURCE_DIMENSION 返回一个在xml中指定的D3D12_RESOURCE_DIMENSION类型的值
     * @param:  const char * res_dimension_type D3D12_RESOURCE_DIMENSION类型变量字符串
     *********************************************************************************/
    static D3D12_RESOURCE_DIMENSION GetResourceDimensionType(const char* res_dimension_type);

    /*********************************************************************************
     * @brief:
     * @return: DXGI_FORMAT
     * @param:  const char * format_name
     *********************************************************************************/
    static DXGI_FORMAT GetDXGIFormat(const char* format_name);

    /*********************************************************************************
     * @brief:
     * @return: DXGI_USAGE
     * @param:  const char * usage
     *********************************************************************************/
    static DXGI_USAGE GetDXGIUsage(const char* usage);

    /*********************************************************************************
     * @brief:
     * @return: DXGI_SWAP_EFFECT
     * @param:  const char * swap_effect
     *********************************************************************************/
    static DXGI_SWAP_EFFECT GetDXGISwapEffect(const char* swap_effect);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_COMMAND_LIST_TYPE
     * @param:  const char * command_list_type
     *********************************************************************************/
    static D3D12_COMMAND_LIST_TYPE GetCommandListType(const char* command_list_type);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_DESCRIPTOR_HEAP_TYPE
     * @param:  const char * heap_type
     *********************************************************************************/
    static D3D12_DESCRIPTOR_HEAP_TYPE GetDescriptorHeapType(const char* heap_type);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_DESCRIPTOR_HEAP_FLAGS
     * @param:  const char * heap_flags
     *********************************************************************************/
    static D3D12_DESCRIPTOR_HEAP_FLAGS GetDescriptorHeapFlags(const char* heap_flags);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_ROOT_SIGNATURE_FLAGS
     * @param:  const char * root_signature_flags
     *********************************************************************************/
    static D3D12_ROOT_SIGNATURE_FLAGS GetRootSignatureFlags(const char* root_signature_flags);

    /*********************************************************************************
     * @brief:
     * @return: D3D_ROOT_SIGNATURE_VERSION
     * @param:  const char * root_signature_version
     *********************************************************************************/
    static D3D_ROOT_SIGNATURE_VERSION GetRootSignatureVersion(const char* root_signature_version);

    /*********************************************************************************
     * @brief:
     * @return: D3D12_INPUT_CLASSIFICATION
     * @param:  const char * classification
     *********************************************************************************/
    static D3D12_INPUT_CLASSIFICATION GetInputClassification(const char* classification);

    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  std::vector<D3D12_INPUT_ELEMENT_DESC> & desc_array
     * @param:  XMLElement * input_elemnt
     *********************************************************************************/
    static void GetInputElementDesc(std::vector<D3D12_INPUT_ELEMENT_DESC>& desc_array, XMLElement* input_elemnt);

    /*********************************************************************************
     * @brief:
     * @return: UINT
     * @param:  const char * compile_flags_compose
     *********************************************************************************/
    static UINT ParseShaderCompileFlags(const char* compile_flags_compose);

    /*********************************************************************************
     * Method:    InitGraphicsPipelineStateDesc
     * FullName:  XmlConfigHelper::InitGraphicsPipelineStateDesc
     * Access:    public static
     * Returns:   void
     * Qualifier:
     * Parameter: D3D12_GRAPHICS_PIPELINE_STATE_DESC * desc
     * Parameter: XMLElement * elem
     *********************************************************************************/
    static void InitGraphicsPipelineStateDesc(D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc, XMLElement* elem);

    /*********************************************************************************
     * Method:    GetPrimtiveTopologyType
     * FullName:  XmlConfigHelper::GetPrimtiveTopologyType
     * Access:    public static
     * Returns:   D3D12_PRIMITIVE_TOPOLOGY_TYPE
     * Qualifier:
     * Parameter: const char * topology_type
     *********************************************************************************/
    static D3D12_PRIMITIVE_TOPOLOGY_TYPE GetPrimtiveTopologyType(const char* topology_type);

    /*********************************************************************************
     * Method:    ParseWindowAssociationFlag
     * FullName:  XmlConfigHelper::ParseWindowAssociationFlag
     * Access:    public static
     * Returns:   UINT
     * Qualifier:
     * Parameter: const char * flags_compose
     *********************************************************************************/
    static UINT ParseWindowAssociationFlag(const char* flags_compose);

private:
    /*********************************************************************************
     * @brief:
     * @return: const char*
     * @param:  const XMLElement * elem
     * @param:  const char * attribute_name
     *********************************************************************************/
    static const char* GetAttributeThrowError(const XMLElement* elem, const char* attribute_name);

public:

    /*********************************************************************************
     * @brief:
     * @return: boost::T
     * @param:  const XMLElement * elem
     * @param:  const char * attribute_name
     * @param:  T default_value
     *********************************************************************************/
    template<typename T>
    static T AttributeValue(const XMLElement* elem, const char* attribute_name, T default_value)
    {
        if (!attribute_name || !elem)
            return default_value;

        const char* attr = GetAttributeThrowError(elem, attribute_name);// elem->Attribute(attribute_name);
        return static_cast<T>(atol(attr));
    }

    template<>
    static bool AttributeValue(const XMLElement* elem, const char* attribute_name, bool default_value)
    {
        return (!attribute_name || !elem) ? default_value : elem->BoolAttribute(attribute_name, default_value);
    }

    template<>
    static float AttributeValue(const XMLElement* elem, const char* attribute_name, float default_value)
    {
        return (!attribute_name || !elem) ? default_value : elem->FloatAttribute(attribute_name, default_value);
    }

    template<>
    static double AttributeValue(const XMLElement* elem, const char* attribute_name, double default_value)
    {
        return (!attribute_name || !elem) ? default_value : elem->DoubleAttribute(attribute_name, default_value);
    }

    /*********************************************************************************
     * @brief:  从XML中取得一个四元向量出来
     * @return: float
     * @param:  const XMLElement * elem
     * @param:  const char * attribute_name
     * @param:  float default_value
     *********************************************************************************/
    static XMFLOAT4 AttributeVector4(const XMLElement* elem, const char* attribute_name, float default_value);
};


#endif // xml_config_helper_h__