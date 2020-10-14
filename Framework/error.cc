/**************************************************************************************************************************
Copyright(C) 2014-2017 www.xionggf.com
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
#include "error.h"
#include "string_convertor.h"

Error::Error(const std::wstring& message, const char* file, uint32_t line) :
    title_(L"Regular Exception"), type_(EXCEPTION_REGULAR), message_(message),
    file_(file), line_(line)
{
}

Error::Error(const std::wstring& message, HRESULT error, const char* file, uint32_t line) :
    title_(L"DirectX12 COM Exception"), type_(EXCEPTION_DX12_COM), message_(message),
    file_(file), line_(line), hresult_(error)
{
    
}

std::wstring Error::AssembleOutput() const
{
    std::wstring file_name;
    StringConvertor::ANSItoUTF16LE(file_.c_str(), file_name);

    switch (type_)
    {
    case EXCEPTION_MESSAGE:
        return message_;
    case EXCEPTION_REGULAR:
    {
        std::wstringstream wss;
        wss << message_ << L"\n" << file_name << L"\nLine " << line_;
        return wss.str();
    }
    case EXCEPTION_DX12_COM:
    {
        LPVOID text_buffer = nullptr;
        ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, hresult_, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&text_buffer, 0, nullptr);
        std::wstringstream wss;
        wss << message_ << L"\n\nFileName: " << file_name << L"\nLine: " << line_ << "L\n\n";
        wss << "DirectX12 COM Error Code = " << hresult_ << std::hex<<L"\n";
        wss << "Error code Description: ";
        wss << reinterpret_cast<LPWSTR>(text_buffer);
        LocalFree(text_buffer);
        return wss.str();
    }
    default:
        break;
    }

    return std::wstring(L"");
}

void Error::Prompt() const
{
    std::wstring output = this->AssembleOutput() + L"\nQuit Program?";
    MessageBoxW(nullptr, output.c_str(), title_.c_str(), MB_OK);
}

void Error::Notify() const
{
    ::ShowCursor(true);
    MessageBoxW(nullptr, AssembleOutput().c_str(), title_.c_str(), MB_OK);
}

void Error::GRS_THROW_IF_FAILED(HRESULT hr, const char* file, int line)
{
    if (FAILED(hr))
    {
        throw Error(L"调用Direct3D 12 API时发生COM异常",hr, file, line);
    }
}

void Error::ThrowTinyXMLException(XMLError error, const std::wstring& xml_file, const char* file, int line)
{
    if (XML_SUCCESS == error)
        return;

    std::wstring xml_error_type;

    switch (error)
    {
    case XML_NO_ATTRIBUTE:xml_error_type = L"XML_NO_ATTRIBUTE"; break;
    case XML_WRONG_ATTRIBUTE_TYPE:xml_error_type = L"XML_WRONG_ATTRIBUTE_TYPE"; break;
    case XML_ERROR_FILE_NOT_FOUND:xml_error_type = L"XML_ERROR_FILE_NOT_FOUND"; break;
    case XML_ERROR_FILE_COULD_NOT_BE_OPENED:xml_error_type = L"XML_ERROR_FILE_COULD_NOT_BE_OPENED"; break;
    case XML_ERROR_FILE_READ_ERROR:xml_error_type = L"XML_ERROR_FILE_READ_ERROR"; break;
    case XML_ERROR_PARSING_ELEMENT:xml_error_type = L"XML_ERROR_PARSING_ELEMENT"; break;
    case XML_ERROR_PARSING_ATTRIBUTE:xml_error_type = L"XML_ERROR_PARSING_ATTRIBUTE"; break;
    case XML_ERROR_PARSING_TEXT:xml_error_type = L"XML_ERROR_PARSING_TEXT"; break;
    case XML_ERROR_PARSING_CDATA:xml_error_type = L"XML_ERROR_PARSING_CDATA"; break;
    case XML_ERROR_PARSING_COMMENT:xml_error_type = L"XML_ERROR_PARSING_COMMENT"; break;
    case XML_ERROR_PARSING_DECLARATION:xml_error_type = L"XML_ERROR_PARSING_DECLARATION"; break;
    case XML_ERROR_PARSING_UNKNOWN:xml_error_type = L"XML_ERROR_PARSING_UNKNOWN"; break;
    case XML_ERROR_EMPTY_DOCUMENT:xml_error_type = L"XML_ERROR_EMPTY_DOCUMENT"; break;
    case XML_ERROR_MISMATCHED_ELEMENT:xml_error_type = L"XML_ERROR_MISMATCHED_ELEMENT"; break;
    case XML_ERROR_PARSING:xml_error_type = L"XML_ERROR_PARSING"; break;
    case XML_CAN_NOT_CONVERT_TEXT:xml_error_type = L"XML_CAN_NOT_CONVERT_TEXT"; break;
    case XML_NO_TEXT_NODE:xml_error_type = L"XML_NO_TEXT_NODE"; break;
    case XML_ELEMENT_DEPTH_EXCEEDED:xml_error_type = L"XML_ELEMENT_DEPTH_EXCEEDEDxml_error_type"; break;
    }

    std::wstringstream wss;
    wss << L"Open " << xml_file << L" Error\n";
    wss << L"error type: " << xml_error_type;
    throw Error(wss.str(), file, line);
}