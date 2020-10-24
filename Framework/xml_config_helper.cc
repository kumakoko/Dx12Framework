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

XMFLOAT4 XmlConfigHelper::AttributeVector4(const XMLElement* elem, const char* attribute_name, float default_value)
{
    if (!attribute_name || !elem)
        return XMFLOAT4(default_value, default_value, default_value, default_value);

    std::string vector4_str(elem->Attribute(attribute_name));
    boost::algorithm::trim(vector4_str); // 字符串组合中的清除掉所有的空格
    std::vector<std::string> vector4_str_array;
    boost::split(vector4_str_array, vector4_str, boost::is_any_of(","), boost::token_compress_off);

    switch (vector4_str.size())
    {
    case 0:return XMFLOAT4(default_value, default_value, default_value, default_value);
    case 1:return XMFLOAT4(vector4_str[0], default_value, default_value, default_value);
    case 2:return XMFLOAT4(vector4_str[0], vector4_str[1], default_value, default_value);
    case 3:return XMFLOAT4(vector4_str[0], vector4_str[1], vector4_str[2], default_value);
    case 4:default:return XMFLOAT4(vector4_str[0], vector4_str[1], vector4_str[2], vector4_str[3]);
    }
}

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

D3D12_RESOURCE_STATES XmlConfigHelper::GetD3D12ResourceStates(const char* state_name)
{
    static bool s_not_init = true;
    static std::map<std::string, D3D12_RESOURCE_STATES> s_res_state_dictionary;

    if (s_not_init)
    {
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_COMMON")] = D3D12_RESOURCE_STATE_COMMON;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER")] = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_INDEX_BUFFER")] = D3D12_RESOURCE_STATE_INDEX_BUFFER;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_RENDER_TARGET")] = D3D12_RESOURCE_STATE_RENDER_TARGET;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_UNORDERED_ACCESS")] = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_DEPTH_WRITE")] = D3D12_RESOURCE_STATE_DEPTH_WRITE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_DEPTH_READ")] = D3D12_RESOURCE_STATE_DEPTH_READ;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE")] = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE")] = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_STREAM_OUT")] = D3D12_RESOURCE_STATE_STREAM_OUT;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT")] = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_COPY_DEST")] = D3D12_RESOURCE_STATE_COPY_DEST;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_COPY_SOURCE")] = D3D12_RESOURCE_STATE_COPY_SOURCE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_RESOLVE_DEST")] = D3D12_RESOURCE_STATE_RESOLVE_DEST;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_RESOLVE_SOURCE")] = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE ")] = D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_GENERIC_READ")] = D3D12_RESOURCE_STATE_GENERIC_READ;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_PRESENT")] = D3D12_RESOURCE_STATE_PRESENT;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_PREDICATION")] = D3D12_RESOURCE_STATE_PREDICATION;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE")] = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VIDEO_DECODE_READ")] = D3D12_RESOURCE_STATE_VIDEO_DECODE_READ;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ")] = D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE")] = D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ")] = D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ;
        s_res_state_dictionary[std::string("D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE")] = D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE;
        s_not_init = false;
    }

    if (!state_name)
        return D3D12_RESOURCE_STATE_COMMON;

    auto iter = s_res_state_dictionary.find(std::string(state_name));

    if (s_res_state_dictionary.end() == iter)
        return D3D12_RESOURCE_STATE_COMMON;

    return iter->second;
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
        desc.SemanticIndex = XmlConfigHelper::AttributeValue(elem,"semantic_index", 0U);
        desc.Format = XmlConfigHelper::GetDXGIFormat(elem->Attribute("format"));
        desc.InputSlot = XmlConfigHelper::AttributeValue(elem,"input_slot", 0U);
        desc.AlignedByteOffset = XmlConfigHelper::AttributeValue(elem,"aligned_byte_offset", 0U);
        desc.InputSlotClass = XmlConfigHelper::GetInputClassification(elem->Attribute("input_slot_class"));
        desc.InstanceDataStepRate = XmlConfigHelper::AttributeValue(elem,"instance_data_step_rate", 0U);
        desc_array.emplace_back(desc);
        elem = elem->NextSiblingElement("D3D12_INPUT_ELEMENT_DESC");
    }
}

void XmlConfigHelper::InitGraphicsPipelineStateDesc(D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc, XMLElement* elem)
{
    desc->RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    desc->BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    desc->DepthStencilState.DepthEnable = XmlConfigHelper::AttributeValue(elem,"depth_stencil_state_depth_enable", FALSE);//FALSE;
    desc->DepthStencilState.StencilEnable = XmlConfigHelper::AttributeValue(elem,"depth_stencil_state_stencil_enable", FALSE);//FALSE;
    desc->SampleMask = XmlConfigHelper::AttributeValue(elem,"sample_mask", UINT_MAX);//UINT_MAX;
    desc->PrimitiveTopologyType = XmlConfigHelper::GetPrimtiveTopologyType(elem->Attribute("primitive_topology_type"));//D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    desc->NumRenderTargets = XmlConfigHelper::AttributeValue(elem,"number_render_targets", 1); //1;
    desc->RTVFormats[0] = XmlConfigHelper::GetDXGIFormat(elem->Attribute("rtv_0_formats"));//DXGI_FORMAT_R8G8B8A8_UNORM;
    desc->SampleDesc.Count = XmlConfigHelper::AttributeValue(elem,"sample_desc_count", 1); //1;
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
        if (_stricmp(flag_str.c_str(), "DXGI_MWA_NO_WINDOW_CHANGES") == 0)
            flags |= DXGI_MWA_NO_WINDOW_CHANGES;
        else if (_stricmp(flag_str.c_str(), "DXGI_MWA_NO_ALT_ENTER") == 0)
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

D3D12_COMMAND_QUEUE_FLAGS XmlConfigHelper::GetCommandQueueFlag(const char* command_queue_flags)
{
    if (!command_queue_flags)
        return D3D12_COMMAND_QUEUE_FLAG_NONE;
    else
    {
        if (_stricmp("D3D12_COMMAND_QUEUE_FLAG_NONE", command_queue_flags) == 0)
            return D3D12_COMMAND_QUEUE_FLAG_NONE;
        else if (_stricmp("D3D12_COMMAND_QUEUE_FLAG_DISABLE_GPU_TIMEOUT", command_queue_flags) == 0)
            return D3D12_COMMAND_QUEUE_FLAG_DISABLE_GPU_TIMEOUT;
        else
            return D3D12_COMMAND_QUEUE_FLAG_NONE;
    }
}

D3D12_COMMAND_QUEUE_PRIORITY XmlConfigHelper::GetCommandQueuePriority(const char* command_queue_priority)
{
    if (!command_queue_priority)
        return D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    else
    {
        if (_stricmp("D3D12_COMMAND_QUEUE_PRIORITY_NORMAL", command_queue_priority) == 0)
            return D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        else if (_stricmp("D3D12_COMMAND_QUEUE_PRIORITY_HIGH", command_queue_priority) == 0)
            return D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
        else if (_stricmp("D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME", command_queue_priority) == 0)
            return D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME;
        else
            return D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    }
}

D3D12_RTV_DIMENSION XmlConfigHelper::GetRenderTargetDimensionType(const char* rtv_dimension_type)
{
    if (!rtv_dimension_type)
        return D3D12_RTV_DIMENSION_UNKNOWN;
    else
    {
        if (_stricmp("D3D12_RTV_DIMENSION_UNKNOWN", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_UNKNOWN;
        else if (_stricmp("D3D12_RTV_DIMENSION_BUFFER", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_BUFFER;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE1D", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE1D;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE1DARRAY", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE1DARRAY;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE2D", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE2D;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE2DARRAY", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE2DMS", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE2DMS;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY;
        else if (_stricmp("D3D12_RTV_DIMENSION_TEXTURE3D", rtv_dimension_type) == 0)
            return D3D12_RTV_DIMENSION_TEXTURE3D;
        else
            return D3D12_RTV_DIMENSION_UNKNOWN;
    }
}

D3D12_RESOURCE_DIMENSION XmlConfigHelper::GetResourceDimensionType(const char* res_dimension_type)
{
    if (!res_dimension_type)
        return D3D12_RESOURCE_DIMENSION_UNKNOWN;
    else
    {
        if (_stricmp("D3D12_RESOURCE_DIMENSION_UNKNOWN", res_dimension_type) == 0)
            return D3D12_RESOURCE_DIMENSION_UNKNOWN;
        else if (_stricmp("D3D12_RESOURCE_DIMENSION_BUFFER", res_dimension_type) == 0)
            return D3D12_RESOURCE_DIMENSION_BUFFER;
        else if (_stricmp("D3D12_RESOURCE_DIMENSION_TEXTURE1D", res_dimension_type) == 0)
            return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
        else if (_stricmp("D3D12_RESOURCE_DIMENSION_TEXTURE2D", res_dimension_type) == 0)
            return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        else if (_stricmp("D3D12_RESOURCE_DIMENSION_TEXTURE3D", res_dimension_type) == 0)
            return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
        else
            return D3D12_RESOURCE_DIMENSION_UNKNOWN;
    }
}

D3D12_RESOURCE_FLAGS XmlConfigHelper::GetResourceFlagsType(const char* res_flag_type)
{
    if (!res_flag_type)
        return D3D12_RESOURCE_FLAG_NONE;
    else
    {
        if (_stricmp("D3D12_RESOURCE_FLAG_NONE", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_NONE;
        else if (_stricmp("D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
        else if (_stricmp("D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
        else if (_stricmp("D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
        else if (_stricmp("D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
        else if (_stricmp("D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER;
        else if (_stricmp("D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
        else if (_stricmp("D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY", res_flag_type) == 0)
            return D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY;
        else
            return D3D12_RESOURCE_FLAG_NONE;
    }
}

D3D12_TEXTURE_LAYOUT XmlConfigHelper::GetTextureLayoutType(const char* texture_layout_type)
{
    if (!texture_layout_type)
        return D3D12_TEXTURE_LAYOUT_UNKNOWN;
    else
    {
        if (_stricmp("D3D12_TEXTURE_LAYOUT_UNKNOWN", texture_layout_type) == 0)
            return D3D12_TEXTURE_LAYOUT_UNKNOWN;
        else if (_stricmp("D3D12_TEXTURE_LAYOUT_ROW_MAJOR", texture_layout_type) == 0)
            return D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        else if (_stricmp("D3D12_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE", texture_layout_type) == 0)
            return D3D12_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE;
        else if (_stricmp("D3D12_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE", texture_layout_type) == 0)
            return D3D12_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE;
        else
            return D3D12_TEXTURE_LAYOUT_UNKNOWN;
    }
}

D3D12_HEAP_TYPE XmlConfigHelper::GetHeapType(const char* heap_type)
{
    if (!heap_type)
        return D3D12_HEAP_TYPE_DEFAULT;
    else
    {
        if (_stricmp("D3D12_HEAP_TYPE_DEFAULT", heap_type) == 0)
            return D3D12_HEAP_TYPE_DEFAULT;
        else if (_stricmp("D3D12_HEAP_TYPE_UPLOAD", heap_type) == 0)
            return D3D12_HEAP_TYPE_UPLOAD;
        else if (_stricmp("D3D12_HEAP_TYPE_READBACK", heap_type) == 0)
            return D3D12_HEAP_TYPE_READBACK;
        else if (_stricmp("D3D12_HEAP_TYPE_CUSTOM", heap_type) == 0)
            return D3D12_HEAP_TYPE_CUSTOM;
        else
            return D3D12_HEAP_TYPE_DEFAULT;
    }
}

D3D12_CPU_PAGE_PROPERTY XmlConfigHelper::GetCpuPagePropertyType(const char* cpu_page_prop)
{
    if (!cpu_page_prop)
        return D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    else
    {
        if (_stricmp("D3D12_CPU_PAGE_PROPERTY_UNKNOWN", cpu_page_prop) == 0)
            return D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        else if (_stricmp("D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE", cpu_page_prop) == 0)
            return D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE;
        else if (_stricmp("D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE", cpu_page_prop) == 0)
            return D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE;
        else if (_stricmp("D3D12_CPU_PAGE_PROPERTY_WRITE_BACK", cpu_page_prop) == 0)
            return D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
        else if (_stricmp("D3D12_CPU_PAGE_PROPERTY_UNKNOWN", cpu_page_prop) == 0)
            return D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        else
            return D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    }
}

D3D12_MEMORY_POOL XmlConfigHelper::GetMemoryPoolType(const char* mem_pool)
{
    if (!mem_pool)
        return D3D12_MEMORY_POOL_UNKNOWN;
    else
    {
        if (_stricmp("D3D12_MEMORY_POOL_L0", mem_pool) == 0)
            return D3D12_MEMORY_POOL_L0;
        else if (_stricmp("D3D12_MEMORY_POOL_L1", mem_pool) == 0)
            return D3D12_MEMORY_POOL_L1;
        else if (_stricmp("D3D12_MEMORY_POOL_UNKNOWN", mem_pool) == 0)
            return D3D12_MEMORY_POOL_UNKNOWN;
        else
            return D3D12_MEMORY_POOL_UNKNOWN;
    }
}

D3D12_DSV_FLAGS XmlConfigHelper::GetDSVFlagsType(const char* flag_type)
{
    if (!D3D12_DSV_FLAG_NONE)
        return D3D12_DSV_FLAG_NONE;
    else
    {
        if (_stricmp("D3D12_DSV_FLAG_NONE", flag_type) == 0)
            return D3D12_DSV_FLAG_NONE;
        else if (_stricmp("D3D12_DSV_FLAG_READ_ONLY_DEPTH", flag_type) == 0)
            return D3D12_DSV_FLAG_READ_ONLY_DEPTH;
        else if (_stricmp("D3D12_DSV_FLAG_READ_ONLY_STENCIL", flag_type) == 0)
            return D3D12_DSV_FLAG_READ_ONLY_STENCIL;
        else
            return D3D12_DSV_FLAG_NONE;
    }
}

D3D12_DSV_DIMENSION XmlConfigHelper::GetDSVDimensionType(const char* dsv_dim_type)
{
    if (!dsv_dim_type)
        return D3D12_DSV_DIMENSION_UNKNOWN;
    else
    {
        if (_stricmp("D3D12_DSV_DIMENSION_UNKNOWN", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_UNKNOWN;
        else if (_stricmp("D3D12_DSV_DIMENSION_TEXTURE1D", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_TEXTURE1D;
        else if (_stricmp("D3D12_DSV_DIMENSION_TEXTURE1DARRAY", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_TEXTURE1DARRAY;
        else if (_stricmp("D3D12_DSV_DIMENSION_TEXTURE2D", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_TEXTURE2D;
        else if (_stricmp("D3D12_DSV_DIMENSION_TEXTURE2DARRAY", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
        else if (_stricmp("D3D12_DSV_DIMENSION_TEXTURE2DMS", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_TEXTURE2DMS;
        else if (_stricmp("D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY", dsv_dim_type) == 0)
            return D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY;
        else
            return D3D12_DSV_DIMENSION_UNKNOWN;
    }
}

D3D12_HEAP_FLAGS XmlConfigHelper::GetHeapFlagType(const char* heap_flag_type)
{
    if (!heap_flag_type)
        return D3D12_HEAP_FLAG_NONE;
    else
    {
        if (_stricmp("D3D12_HEAP_FLAG_NONE", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_NONE;
        else if (_stricmp("D3D12_HEAP_FLAG_SHARED", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_SHARED;
        else if (_stricmp("D3D12_HEAP_FLAG_DENY_BUFFERS", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_DENY_BUFFERS;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_DISPLAY", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_DISPLAY;
        else if (_stricmp("D3D12_HEAP_FLAG_SHARED_CROSS_ADAPTER", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_SHARED_CROSS_ADAPTER;
        else if (_stricmp("D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES;
        else if (_stricmp("D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES;
        else if (_stricmp("D3D12_HEAP_FLAG_HARDWARE_PROTECTED", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_HARDWARE_PROTECTED;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_WRITE_WATCH", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_WRITE_WATCH;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES;
        else if (_stricmp("D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES", heap_flag_type) == 0)
            return D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES;
        else
            return D3D12_HEAP_FLAG_NONE;
    }
}


const char* XmlConfigHelper::GetAttributeThrowError(const XMLElement* elem, const char* attribute_name)
{
    const char* attr = elem->Attribute(attribute_name);

    if (nullptr == attr)
    {
        std::wstringstream wss(L"无法从名为");
        wss << StringConvertor::UTF8toUTF16LE(elem->Name()) << L"的XML Element中\n";
        wss << L"获取到名为" << StringConvertor::UTF8toUTF16LE(attribute_name) << L"的XML Attribute";
        throw Error(wss.str().c_str());
    }
    
    return attr;
}