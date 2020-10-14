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
#include "xml_config_helper.h"
#include "error.h"

D3D12_COMMAND_LIST_TYPE XmlConfigHelper::GetCommandListType(const char* command_list_type)
{
    if (command_list_type)
    {
        if (_stricmp("D3D12_COMMAND_LIST_TYPE_DIRECT", command_list_type) == 0)
            return D3D12_COMMAND_LIST_TYPE_DIRECT;
        else if (_stricmp("D3D12_COMMAND_LIST_TYPE_BUNDLE", command_list_type) == 0)
            return D3D12_COMMAND_LIST_TYPE_BUNDLE;
        else if (_stricmp("D3D12_COMMAND_LIST_TYPE_COMPUTE", command_list_type) == 0)
            return D3D12_COMMAND_LIST_TYPE_COMPUTE;
        else if (_stricmp("D3D12_COMMAND_LIST_TYPE_COPY", command_list_type) == 0)
            return D3D12_COMMAND_LIST_TYPE_COPY;
        else if (_stricmp("D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE", command_list_type) == 0)
            return D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE;
        else if (_stricmp("D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS", command_list_type) == 0)
            return D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS;
        else
            return D3D12_COMMAND_LIST_TYPE_DIRECT;
    }
    else
    {
        return D3D12_COMMAND_LIST_TYPE_DIRECT;
    }
}

DXGI_USAGE XmlConfigHelper::GetDXGIUsage(const char* usage)
{
    if (!usage)
        return DXGI_USAGE_SHADER_INPUT;
    else
    {
        if (_stricmp("DXGI_USAGE_SHADER_INPUT", usage) == 0)
            return DXGI_USAGE_SHADER_INPUT;
        else if (_stricmp("DXGI_USAGE_RENDER_TARGET_OUTPUT", usage) == 0)
            return DXGI_USAGE_RENDER_TARGET_OUTPUT;
        else if (_stricmp("DXGI_USAGE_BACK_BUFFER", usage) == 0)
            return DXGI_USAGE_BACK_BUFFER;
        else if (_stricmp("DXGI_USAGE_SHARED", usage) == 0)
            return DXGI_USAGE_SHARED;
        else if (_stricmp("DXGI_USAGE_READ_ONLY", usage) == 0)
            return DXGI_USAGE_READ_ONLY;
        else if (_stricmp("DXGI_USAGE_DISCARD_ON_PRESENT", usage) == 0)
            return DXGI_USAGE_DISCARD_ON_PRESENT;
        else if (_stricmp("DXGI_USAGE_UNORDERED_ACCESS", usage) == 0)
            return DXGI_USAGE_UNORDERED_ACCESS;
        else
            return DXGI_USAGE_SHADER_INPUT;
    }
}

DXGI_SWAP_EFFECT XmlConfigHelper::GetDXGISwapEffect(const char* swap_effect)
{
    if (!swap_effect)
        return DXGI_SWAP_EFFECT_DISCARD;
    else
    {
        if (_stricmp("DXGI_SWAP_EFFECT_DISCARD", swap_effect) == 0)
            return DXGI_SWAP_EFFECT_DISCARD;
        else if (_stricmp("DXGI_SWAP_EFFECT_SEQUENTIAL", swap_effect) == 0)
            return DXGI_SWAP_EFFECT_SEQUENTIAL;
        else if (_stricmp("DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL", swap_effect) == 0)
            return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        else if (_stricmp("DXGI_SWAP_EFFECT_FLIP_DISCARD", swap_effect) == 0)
            return DXGI_SWAP_EFFECT_FLIP_DISCARD;
        else
            return DXGI_SWAP_EFFECT_DISCARD;
    }
}

DXGI_FORMAT XmlConfigHelper::GetDXGIFormat(const char* format_name)
{
    static bool s_not_init = true;
    static std::map<std::string, DXGI_FORMAT> s_dxgi_dictionary;

    if (s_not_init)
    {
        s_dxgi_dictionary[std::string("DXGI_FORMAT_UNKNOWN")] = DXGI_FORMAT_UNKNOWN;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32A32_TYPELESS")] = DXGI_FORMAT_R32G32B32A32_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32A32_FLOAT")] = DXGI_FORMAT_R32G32B32A32_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32A32_UINT")] = DXGI_FORMAT_R32G32B32A32_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32A32_SINT")] = DXGI_FORMAT_R32G32B32A32_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32_TYPELESS")] = DXGI_FORMAT_R32G32B32_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32_FLOAT")] = DXGI_FORMAT_R32G32B32_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32_UINT")] = DXGI_FORMAT_R32G32B32_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32B32_SINT")] = DXGI_FORMAT_R32G32B32_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16B16A16_TYPELESS")] = DXGI_FORMAT_R16G16B16A16_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16B16A16_FLOAT")] = DXGI_FORMAT_R16G16B16A16_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16B16A16_UNORM")] = DXGI_FORMAT_R16G16B16A16_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16B16A16_UINT")] = DXGI_FORMAT_R16G16B16A16_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16B16A16_SNORM")] = DXGI_FORMAT_R16G16B16A16_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16B16A16_SINT")] = DXGI_FORMAT_R16G16B16A16_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32_TYPELESS ")] = DXGI_FORMAT_R32G32_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32_FLOAT")] = DXGI_FORMAT_R32G32_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32_UINT")] = DXGI_FORMAT_R32G32_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G32_SINT")] = DXGI_FORMAT_R32G32_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32G8X24_TYPELESS")] = DXGI_FORMAT_R32G8X24_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_D32_FLOAT_S8X24_UINT")] = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS")] = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_X32_TYPELESS_G8X24_UINT")] = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R10G10B10A2_TYPELESS")] = DXGI_FORMAT_R10G10B10A2_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R10G10B10A2_UNORM")] = DXGI_FORMAT_R10G10B10A2_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R10G10B10A2_UINT")] = DXGI_FORMAT_R10G10B10A2_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R11G11B10_FLOAT")] = DXGI_FORMAT_R11G11B10_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8B8A8_TYPELESS")] = DXGI_FORMAT_R8G8B8A8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8B8A8_UNORM")] = DXGI_FORMAT_R8G8B8A8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8B8A8_UNORM_SRGB")] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8B8A8_UINT")] = DXGI_FORMAT_R8G8B8A8_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8B8A8_SNORM")] = DXGI_FORMAT_R8G8B8A8_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8B8A8_SINT")] = DXGI_FORMAT_R8G8B8A8_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16_TYPELESS")] = DXGI_FORMAT_R16G16_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16_FLOAT")] = DXGI_FORMAT_R16G16_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16_UNORM")] = DXGI_FORMAT_R16G16_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16_UINT")] = DXGI_FORMAT_R16G16_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16_SNORM")] = DXGI_FORMAT_R16G16_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16G16_SINT")] = DXGI_FORMAT_R16G16_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32_TYPELESS")] = DXGI_FORMAT_R32_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_D32_FLOAT")] = DXGI_FORMAT_D32_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32_FLOAT")] = DXGI_FORMAT_R32_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32_UINT")] = DXGI_FORMAT_R32_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R32_SINT")] = DXGI_FORMAT_R32_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R24G8_TYPELESS")] = DXGI_FORMAT_R24G8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_D24_UNORM_S8_UINT")] = DXGI_FORMAT_D24_UNORM_S8_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R24_UNORM_X8_TYPELESS")] = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_X24_TYPELESS_G8_UINT")] = DXGI_FORMAT_X24_TYPELESS_G8_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8_TYPELESS")] = DXGI_FORMAT_R8G8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8_UNORM")] = DXGI_FORMAT_R8G8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8_UINT")] = DXGI_FORMAT_R8G8_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8_SNORM")] = DXGI_FORMAT_R8G8_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8_SINT")] = DXGI_FORMAT_R8G8_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16_TYPELESS")] = DXGI_FORMAT_R16_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16_FLOAT")] = DXGI_FORMAT_R16_FLOAT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_D16_UNORM")] = DXGI_FORMAT_D16_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16_UNORM")] = DXGI_FORMAT_R16_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16_UINT")] = DXGI_FORMAT_R16_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16_SNORM")] = DXGI_FORMAT_R16_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R16_SINT")] = DXGI_FORMAT_R16_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8_TYPELESS")] = DXGI_FORMAT_R8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8_UNORM")] = DXGI_FORMAT_R8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8_UINT")] = DXGI_FORMAT_R8_UINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8_SNORM")] = DXGI_FORMAT_R8_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8_SINT")] = DXGI_FORMAT_R8_SINT;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_A8_UNORM")] = DXGI_FORMAT_A8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R1_UNORM")] = DXGI_FORMAT_R1_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R9G9B9E5_SHAREDEXP")] = DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R8G8_B8G8_UNORM")] = DXGI_FORMAT_R8G8_B8G8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_G8R8_G8B8_UNORM")] = DXGI_FORMAT_G8R8_G8B8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC1_TYPELESS")] = DXGI_FORMAT_BC1_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC1_UNORM")] = DXGI_FORMAT_BC1_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC1_UNORM_SRGB")] = DXGI_FORMAT_BC1_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC2_TYPELESS")] = DXGI_FORMAT_BC2_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC2_UNORM")] = DXGI_FORMAT_BC2_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC2_UNORM_SRGB")] = DXGI_FORMAT_BC2_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC3_TYPELESS")] = DXGI_FORMAT_BC3_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC3_UNORM")] = DXGI_FORMAT_BC3_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC3_UNORM_SRGB")] = DXGI_FORMAT_BC3_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC4_TYPELESS")] = DXGI_FORMAT_BC4_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC4_UNORM")] = DXGI_FORMAT_BC4_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC4_SNORM")] = DXGI_FORMAT_BC4_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC5_TYPELESS")] = DXGI_FORMAT_BC5_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC5_UNORM")] = DXGI_FORMAT_BC5_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC5_SNORM")] = DXGI_FORMAT_BC5_SNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B5G6R5_UNORM")] = DXGI_FORMAT_B5G6R5_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B5G5R5A1_UNORM")] = DXGI_FORMAT_B5G5R5A1_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B8G8R8A8_UNORM")] = DXGI_FORMAT_B8G8R8A8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B8G8R8X8_UNORM")] = DXGI_FORMAT_B8G8R8X8_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM")] = DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B8G8R8A8_TYPELESS")] = DXGI_FORMAT_B8G8R8A8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B8G8R8A8_UNORM_SRGB")] = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B8G8R8X8_TYPELESS")] = DXGI_FORMAT_B8G8R8X8_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B8G8R8X8_UNORM_SRGB")] = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC6H_TYPELESS")] = DXGI_FORMAT_BC6H_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC6H_UF16")] = DXGI_FORMAT_BC6H_UF16;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC6H_SF16")] = DXGI_FORMAT_BC6H_SF16;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC7_TYPELESS")] = DXGI_FORMAT_BC7_TYPELESS;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC7_UNORM")] = DXGI_FORMAT_BC7_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_BC7_UNORM_SRGB")] = DXGI_FORMAT_BC7_UNORM_SRGB;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_AYUV")] = DXGI_FORMAT_AYUV;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_Y410")] = DXGI_FORMAT_Y410;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_Y416")] = DXGI_FORMAT_Y416;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_NV12")] = DXGI_FORMAT_NV12;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_P010")] = DXGI_FORMAT_P010;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_P016")] = DXGI_FORMAT_P016;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_420_OPAQUE")] = DXGI_FORMAT_420_OPAQUE;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_YUY2")] = DXGI_FORMAT_YUY2;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_Y210")] = DXGI_FORMAT_Y210;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_Y216")] = DXGI_FORMAT_Y216;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_NV11")] = DXGI_FORMAT_NV11;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_AI44")] = DXGI_FORMAT_AI44;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_IA44")] = DXGI_FORMAT_IA44;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_P8")] = DXGI_FORMAT_P8;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_A8P8")] = DXGI_FORMAT_A8P8;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_B4G4R4A4_UNORM")] = DXGI_FORMAT_B4G4R4A4_UNORM;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_P208")] = DXGI_FORMAT_P208;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_V208")] = DXGI_FORMAT_V208;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_V408")] = DXGI_FORMAT_V408;
        s_dxgi_dictionary[std::string("DXGI_FORMAT_FORCE_UINT")] = DXGI_FORMAT_FORCE_UINT;
        s_not_init = false;
    }

    if (!format_name)
        return DXGI_FORMAT_UNKNOWN;

    auto iter = s_dxgi_dictionary.find(std::string(format_name));

    if (s_dxgi_dictionary.end() == iter)
        return DXGI_FORMAT_UNKNOWN;

    return iter->second;
}

float XmlConfigHelper::Attribute(const char* attr, float default_value)
{
    if (!attr)
        return default_value;

    return static_cast<float>(atof(attr));
}

double XmlConfigHelper::Attribute(const char* attr, double default_value)
{
    if (!attr)
        return default_value;

    return atof(attr);
}

UINT XmlConfigHelper::Attribute(const char* attr, UINT default_value)
{
    if (!attr)
        return default_value;

    return static_cast<UINT>(atoi(attr));
}

INT XmlConfigHelper::Attribute(const char* attr, INT default_value)
{
    if (!attr)
        return default_value;

    return static_cast<INT>(atoi(attr));
}

BOOL XmlConfigHelper::AttributeBOOL(const char* attr, BOOL default_value)
{
    if (!attr)
        return default_value;

    return _stricmp("TRUE", attr) == 0 ? TRUE : FALSE;
}

bool XmlConfigHelper::Attribute(const char* attr, bool default_value)
{
    if (!attr)
        return default_value;

    return _stricmp("TRUE", attr) == 0;
}

D3D12_DESCRIPTOR_HEAP_TYPE XmlConfigHelper::GetDescriptorHeapType(const char* heap_type)
{
    if (!heap_type)
        return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    else
    {
        if (_stricmp("D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV", heap_type) == 0)
            return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        else if (_stricmp("D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER", heap_type) == 0)
            return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
        else if (_stricmp("D3D12_DESCRIPTOR_HEAP_TYPE_RTV", heap_type) == 0)
            return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        else if (_stricmp("D3D12_DESCRIPTOR_HEAP_TYPE_DSV", heap_type) == 0)
            return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        else if (_stricmp("D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES", heap_type) == 0)
            return D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;
        else
            return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    }
}

D3D12_DESCRIPTOR_HEAP_FLAGS XmlConfigHelper::GetDescriptorHeapFlags(const char* heap_flags)
{
    if (!heap_flags)
        return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    else
    {
        if (_stricmp("D3D12_DESCRIPTOR_HEAP_FLAG_NONE", heap_flags) == 0)
            return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        else if (_stricmp("D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE", heap_flags) == 0)
            return D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        else
            return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    }
}

D3D12_ROOT_SIGNATURE_FLAGS XmlConfigHelper::GetRootSignatureFlags(const char* root_signature_flags)
{
    if (!root_signature_flags)
        return D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    else
    {
        if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_NONE", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_NONE;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
        else if (_stricmp("D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE", root_signature_flags) == 0)
            return D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE;
        else
            return D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    }
}

D3D_ROOT_SIGNATURE_VERSION XmlConfigHelper::GetRootSignatureVersion(const char* root_signature_version)
{
    if (!root_signature_version)
        return D3D_ROOT_SIGNATURE_VERSION_1;
    else
    {
        if (_stricmp("D3D_ROOT_SIGNATURE_VERSION_1", root_signature_version) == 0)
            return D3D_ROOT_SIGNATURE_VERSION_1;
        else if (_stricmp("D3D_ROOT_SIGNATURE_VERSION_1_0", root_signature_version) == 0)
            return D3D_ROOT_SIGNATURE_VERSION_1_0;
        else if (_stricmp("D3D_ROOT_SIGNATURE_VERSION_1_1", root_signature_version) == 0)
            return D3D_ROOT_SIGNATURE_VERSION_1_1;
        else
            return D3D_ROOT_SIGNATURE_VERSION_1;
    }
}

void XmlConfigHelper::GetInputElementDesc(std::vector<D3D12_INPUT_ELEMENT_DESC>& desc_array, XMLElement* input_elemnt)
{
    desc_array.clear();
    XMLElement* elem = input_elemnt->FirstChildElement("D3D12_INPUT_ELEMENT_DESC");
    D3D12_INPUT_ELEMENT_DESC desc;

    while (elem)
    {
        desc.SemanticName = elem->Attribute("semantic_name");
        desc.SemanticIndex = XmlConfigHelper::Attribute(elem->Attribute("semantic_index"), 0U);
        desc.Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("format"));
        desc.InputSlot = XmlConfigHelper::Attribute(elem->Attribute("input_slot"), 0U);
        desc.AlignedByteOffset = XmlConfigHelper::Attribute(elem->Attribute("aligned_byte_offset"), 0U);
        desc.InputSlotClass = XmlConfigHelper::GetInputClassification(elem->Attribute("input_slot_class"));
        desc.InstanceDataStepRate = XmlConfigHelper::Attribute(elem->Attribute("instance_data_step_rate"), 0U);
        desc_array.emplace_back(desc);
        elem = elem->NextSiblingElement("D3D12_INPUT_ELEMENT_DESC");
    }
}

void XmlConfigHelper::InitGraphicsPipelineStateDesc(D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc, XMLElement* elem)
{
   // D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    //  psoDesc.InputLayout = { inputElementDescs.data(), inputElementDescs.size()/*_countof(inputElementDescs)*/ };
    //  psoDesc.pRootSignature = pIRootSignature;
     // psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
    //  psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
    desc->RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    desc->BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    desc->DepthStencilState.DepthEnable = XmlConfigHelper::AttributeBOOL(elem->Attribute("depth_stencil_state_depth_enable"),FALSE);//FALSE;
    desc->DepthStencilState.StencilEnable = XmlConfigHelper::AttributeBOOL(elem->Attribute("depth_stencil_state_stencil_enable"),FALSE);//FALSE;
    desc->SampleMask = XmlConfigHelper::Attribute(elem->Attribute("sample_mask"),UINT_MAX);//UINT_MAX;
    desc->PrimitiveTopologyType = XmlConfigHelper::GetPrimtiveTopologyType(elem->Attribute("primitive_topology_type"));//D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    desc->NumRenderTargets = XmlConfigHelper::Attribute(elem->Attribute("number_render_targets"),1); //1;
    desc->RTVFormats[0] = XmlConfigHelper::GetDXGIFormat(elem->Attribute("rtv_0_formats"));//DXGI_FORMAT_R8G8B8A8_UNORM;
    desc->SampleDesc.Count = XmlConfigHelper::Attribute(elem->Attribute("sample_desc_count"), 1); //1;
}

D3D12_PRIMITIVE_TOPOLOGY_TYPE XmlConfigHelper::GetPrimtiveTopologyType(const char* topology_type)
{
    if (!topology_type)
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    else
    {
        if (_stricmp("D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED", topology_type) == 0)
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
        else if (_stricmp("D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT", topology_type) == 0)
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
        if (_stricmp("D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE", topology_type) == 0)
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
        if (_stricmp("D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE", topology_type) == 0)
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        if (_stricmp("D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH", topology_type) == 0)
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
        else
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    }
}

D3D12_INPUT_CLASSIFICATION XmlConfigHelper::GetInputClassification(const char* classification)
{
    if (!classification)
        return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
    else
    {
        if (_stricmp("D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA", classification) == 0)
            return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
        else if (_stricmp("D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA", classification) == 0)
            return D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
        else
            return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
    }
}

UINT XmlConfigHelper::ParseWindowAssociationFlag(const char* flags_compose)
{
    std::string flags_compose_str(flags_compose);
    boost::algorithm::trim(flags_compose_str); // 字符串组合中的清除掉所有的空格
    std::vector<std::string> flag_str_array;
    boost::split(flag_str_array, flags_compose_str, boost::is_any_of("|"), boost::token_compress_off);
    UINT flags = 0U;

    for (auto& flag_str : flag_str_array)
    {
        if (_stricmp(flag_str.c_str(),"DXGI_MWA_NO_WINDOW_CHANGES") == 0 )
            flags |= DXGI_MWA_NO_WINDOW_CHANGES;
        else if(_stricmp(flag_str.c_str(), "DXGI_MWA_NO_ALT_ENTER") == 0)
            flags |= DXGI_MWA_NO_ALT_ENTER;
        else if (_stricmp(flag_str.c_str(), "DXGI_MWA_NO_PRINT_SCREEN") == 0)
            flags |= DXGI_MWA_NO_PRINT_SCREEN;
    }

    return flags;
}

UINT XmlConfigHelper::ParseShaderCompileFlags(const char* compile_flags_compose)
{
    static bool s_not_init = true;
    static std::map<std::string, UINT> s_compile_flag_dictionary;

    if (s_not_init)
    {
        s_compile_flag_dictionary[std::string("D3DCOMPILE_DEBUG")] = D3DCOMPILE_DEBUG;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_SKIP_VALIDATION")] = D3DCOMPILE_SKIP_VALIDATION;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_SKIP_OPTIMIZATION")] = D3DCOMPILE_SKIP_OPTIMIZATION;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_PACK_MATRIX_ROW_MAJOR")] = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR")] = D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_PARTIAL_PRECISION")] = D3DCOMPILE_PARTIAL_PRECISION;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT")] = D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT")] = D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_NO_PRESHADER")] = D3DCOMPILE_NO_PRESHADER;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_AVOID_FLOW_CONTROL")] = D3DCOMPILE_AVOID_FLOW_CONTROL;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_PREFER_FLOW_CONTROL")] = D3DCOMPILE_PREFER_FLOW_CONTROL;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_ENABLE_STRICTNESS")] = D3DCOMPILE_ENABLE_STRICTNESS;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY")] = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_IEEE_STRICTNESS")] = D3DCOMPILE_IEEE_STRICTNESS;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_OPTIMIZATION_LEVEL0")] = D3DCOMPILE_OPTIMIZATION_LEVEL0;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_OPTIMIZATION_LEVEL1")] = D3DCOMPILE_OPTIMIZATION_LEVEL1;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_OPTIMIZATION_LEVEL2")] = D3DCOMPILE_OPTIMIZATION_LEVEL2;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_OPTIMIZATION_LEVEL3")] = D3DCOMPILE_OPTIMIZATION_LEVEL3;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_RESERVED16")] = D3DCOMPILE_RESERVED16;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_RESERVED17")] = D3DCOMPILE_RESERVED17;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_WARNINGS_ARE_ERRORS")] = D3DCOMPILE_WARNINGS_ARE_ERRORS;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_RESOURCES_MAY_ALIAS")] = D3DCOMPILE_RESOURCES_MAY_ALIAS;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES")] = D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_ALL_RESOURCES_BOUND")] = D3DCOMPILE_ALL_RESOURCES_BOUND;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_DEBUG_NAME_FOR_SOURCE")] = D3DCOMPILE_DEBUG_NAME_FOR_SOURCE;
        s_compile_flag_dictionary[std::string("D3DCOMPILE_DEBUG_NAME_FOR_BINARY")] = D3DCOMPILE_DEBUG_NAME_FOR_BINARY;
        s_not_init = false;
    }

    std::string compile_flags_compose_str(compile_flags_compose);
    boost::algorithm::trim(compile_flags_compose_str); // 字符串组合中的清除掉所有的空格
    std::vector<std::string> compile_flag_str_array;
    boost::split(compile_flag_str_array, compile_flags_compose_str, boost::is_any_of("|"), boost::token_compress_off);

    UINT flags = 0U;

    for (auto& flag_str : compile_flag_str_array)
    {
        auto iter = s_compile_flag_dictionary.find(flag_str);

        if (s_compile_flag_dictionary.end() == iter)
            continue;

        flags |= iter->second;
    }

    return flags;
}