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

class DX12_FRAMEWORK_DLL XmlConfigHelper
{
public:
    /*********************************************************************************
     * Method:    GetDXGIFormat
     * FullName:  XmlConfigHelper::GetDXGIFormat
     * Access:    public static 
     * Returns:   DXGI_FORMAT
     * Qualifier:
     * Parameter: const char * format_name
     *********************************************************************************/
    static DXGI_FORMAT GetDXGIFormat(const char* format_name);

    /*********************************************************************************
     * Method:    GetDXGIUsage
     * FullName:  XmlConfigHelper::GetDXGIUsage
     * Access:    public static 
     * Returns:   DXGI_USAGE
     * Qualifier:
     * Parameter: const char * usage
     *********************************************************************************/
    static DXGI_USAGE GetDXGIUsage(const char* usage);

    /*********************************************************************************
     * Method:    GetDXGISwapEffect
     * FullName:  XmlConfigHelper::GetDXGISwapEffect
     * Access:    public static 
     * Returns:   DXGI_SWAP_EFFECT
     * Qualifier:
     * Parameter: const char * swap_effect
     *********************************************************************************/
    static DXGI_SWAP_EFFECT GetDXGISwapEffect(const char* swap_effect);
    /*********************************************************************************
     * Method:    GetCommandListType
     * FullName:  XmlConfigHelper::GetCommandListType
     * Access:    public static 
     * Returns:   D3D12_COMMAND_LIST_TYPE
     * Qualifier:
     * Parameter: const char * command_list_type
     *********************************************************************************/
    static D3D12_COMMAND_LIST_TYPE GetCommandListType(const char* command_list_type);

    /*********************************************************************************
     * Method:    GetDescriptorHeapType
     * FullName:  XmlConfigHelper::GetDescriptorHeapType
     * Access:    public static 
     * Returns:   D3D12_DESCRIPTOR_HEAP_TYPE
     * Qualifier:
     * Parameter: const char * heap_type
     *********************************************************************************/
    static D3D12_DESCRIPTOR_HEAP_TYPE GetDescriptorHeapType(const char* heap_type);

    static D3D12_DESCRIPTOR_HEAP_FLAGS GetDescriptorHeapFlags(const char* heap_flags);
    /*********************************************************************************
     * Method:    GetRootSignatureFlags
     * FullName:  XmlConfigHelper::GetRootSignatureFlags
     * Access:    public static 
     * Returns:   D3D12_ROOT_SIGNATURE_FLAGS
     * Qualifier:
     * Parameter: const char * root_signature_flags
     *********************************************************************************/
    static D3D12_ROOT_SIGNATURE_FLAGS GetRootSignatureFlags(const char* root_signature_flags);

    /*********************************************************************************
     * Method:    GetRootSignatureVersion
     * FullName:  XmlConfigHelper::GetRootSignatureVersion
     * Access:    public static 
     * Returns:   D3D_ROOT_SIGNATURE_VERSION
     * Qualifier:
     * Parameter: const char * root_signature_version
     *********************************************************************************/
    static D3D_ROOT_SIGNATURE_VERSION GetRootSignatureVersion(const char* root_signature_version);

    /*********************************************************************************
     * Method:    GetInputClassification
     * FullName:  XmlConfigHelper::GetInputClassification
     * Access:    public static 
     * Returns:   D3D12_INPUT_CLASSIFICATION
     * Qualifier:
     * Parameter: const char * classification
     *********************************************************************************/
    static D3D12_INPUT_CLASSIFICATION GetInputClassification(const char* classification);

    /*********************************************************************************
     * Method:    GetInputElementDesc
     * FullName:  XmlConfigHelper::GetInputElementDesc
     * Access:    public static 
     * Returns:   void
     * Qualifier:
     * Parameter: std::vector<D3D12_INPUT_ELEMENT_DESC> & desc_array
     * Parameter: XMLElement * input_elemnt
     *********************************************************************************/
    static void GetInputElementDesc(std::vector<D3D12_INPUT_ELEMENT_DESC>& desc_array, XMLElement* input_elemnt);

    /*********************************************************************************
     * Method:    ParseShaderCompileFlags
     * FullName:  XmlConfigHelper::ParseShaderCompileFlags
     * Access:    public static 
     * Returns:   UINT
     * Qualifier:
     * Parameter: const char * compile_flags_compose
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

    /*********************************************************************************
     * Method:    Attribute
     * FullName:  XmlConfigHelper::Attribute
     * Access:    public static 
     * Returns:   float
     * Qualifier:
     * Parameter: const char * attr
     * Parameter: float default_value
     *********************************************************************************/
    static float AttributeValue(const char* attr, float default_value);

    /*********************************************************************************
     * Method:    Attribute
     * FullName:  XmlConfigHelper::Attribute
     * Access:    public static 
     * Returns:   double
     * Qualifier:
     * Parameter: const char * attr
     * Parameter: double default_value
     *********************************************************************************/
    static double AttributeValue(const char* attr, double default_value);

    /*********************************************************************************
     * Method:    Attribute
     * FullName:  XmlConfigHelper::Attribute
     * Access:    public static 
     * Returns:   UINT
     * Qualifier:
     * Parameter: const char * attr
     * Parameter: UINT default_value
     *********************************************************************************/
    static UINT AttributeValue(const char* attr, UINT default_value);

    /*********************************************************************************
     * Method:    Attribute
     * FullName:  XmlConfigHelper::Attribute
     * Access:    public static 
     * Returns:   INT
     * Qualifier:
     * Parameter: const char * attr
     * Parameter: INT default_value
     *********************************************************************************/
    static INT AttributeValue(const char* attr, INT default_value);

    static BOOL AttributeValueBOOL(const char* attr, BOOL default_value);

    static bool AttributeValue(const char* attr, bool default_value);
};


#endif // xml_config_helper_h__