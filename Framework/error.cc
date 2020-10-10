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

Error::Error(const std::wstring& message) :
	title_(L"Exception"), type_(EXCEPTION_MESSAGE), message_(message)
{
}

Error::Error(const std::wstring& message, const char* file, uint32_t line) :
	title_(L"Regular Exception"), type_(EXCEPTION_REGULAR), message_(message),
	file_(file), line_(line)
{
}

Error::Error(HRESULT error, const char* file, uint32_t line) :
	title_(L"DirectX12 Exception"), type_(EXCEPTION_DX12), message_(L""),
	file_(file), line_(line)
{

}

std::wstring Error::AssembleOutput() const
{
	switch (type_)
	{
	case EXCEPTION_REGULAR:
	{
		std::wstring file_name;
		StringConvertor::ANSItoUTF16LE(file_.c_str(), file_name);
		std::wstringstream wss;
		wss << message_ << L"\n" << file_name << L"\nLine " << line_;
		return wss.str();
	}
	case EXCEPTION_MESSAGE:
	case EXCEPTION_DX12:
		return message_;
	default:
		break;
	}

	return std::wstring(L"");
}

void Error::Prompt() const
{
	std::wstring output = this->AssembleOutput() + L"\nQuit Program?";
	MessageBoxW(nullptr, title_.c_str(), output.c_str(), MB_OK);
}

void Error::Notify() const
{
	::ShowCursor(true);
	MessageBoxW(nullptr, title_.c_str(), AssembleOutput().c_str(), MB_OK);
}

void Error::GRS_THROW_IF_FAILED(HRESULT hr, const char* file, int line)
{
	 if (FAILED(hr))
	 {
		 throw Error(hr, file, line); 
	 }
}