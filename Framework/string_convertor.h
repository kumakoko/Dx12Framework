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
/*!
* \file kgl_string_convertor.h
* \date 2017/12/31 13:58
*
* \author www.xionggf.com
* Contact: sun_of_lover@sina.com
*
* \brief
*
* TODO: 字符串编解码码转换器
*
* \note
*/
#ifndef string_encoder_h__
#define string_encoder_h__

class DX12_FRAMEWORK_DLL StringConvertor
{
private:
	/// <summary>
	/// The k temporary buffer length
	/// </summary>
	static const size_t kTmpBufferLen = 16;

	/// <summary>
	/// The s_char_buffer_
	/// </summary>
	static char s_char_buffer_[kTmpBufferLen];

	/// <summary>
	/// The s_wchar_buffer_
	/// </summary>
	static char s_wchar_buffer_[kTmpBufferLen];

	/// <summary>
	/// ANSI字符集,将会根据当前系统的代码页去初始化对应的值
	/// </summary>
	static std::string s_ansi_char_set;
private:
	/*********************************************************************************
	 * Method:    CodeConvert
	 * FullName:  StringConvertor::CodeConvert
	 * Access:    private static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const char * from_charset
	 * Parameter: const char * to_charset
	 * Parameter: const char * inbuf
	 * Parameter: size_t inlen
	 * Parameter: char * outbuf
	 * Parameter: size_t * outlen
	 *********************************************************************************/
	static int CodeConvert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t* outlen);
public:
	/*********************************************************************************
	 * Method:    UTF8toUTF16LE
	 * FullName:  StringConvertor::UTF8toUTF16LE
	 * Access:    public static
	 * Returns:   int
	 * Qualifier: 把UTF8编码的字符串作为源数据,返回的得到的utf16字符串首指针
	 * Parameter: const char * utf8_str 要转换的源数据字符串,utf8编码
	 * Parameter: wchar_t * * utf16_str 转换得到的目标字符串的7指针,utf16LE编码
	 *********************************************************************************/
	static int UTF8toUTF16LE(const char* utf8_str, wchar_t** utf16_str);

	/*********************************************************************************
	 * Method:    UTF8toUTF16LE
	 * FullName:  StringConvertor::UTF8toUTF16LE
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const char * utf8_str
	 * Parameter: std::wstring & utf16_str
	 *********************************************************************************/
	static int UTF8toUTF16LE(const char* utf8_str, std::wstring& utf16_str);

	/*********************************************************************************
	 * Method:    UTF8toUTF16LE
	 * FullName:  StringConvertor::UTF8toUTF16LE
	 * Access:    public static
	 * Returns:   std::wstring
	 * Qualifier:
	 * Parameter: const char * utf8_str
	 *********************************************************************************/
	static std::wstring UTF8toUTF16LE(const char* utf8_str);

	/*********************************************************************************
	 * Method:    UTF16LEtoUTF8
	 * FullName:  StringConvertor::UTF16LEtoUTF8
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const wchar_t * utf16_str
	 * Parameter: char * * utf8_str
	 *********************************************************************************/
	static int UTF16LEtoUTF8(const wchar_t* utf16_str, char** utf8_str);

	/*********************************************************************************
	 * Method:    UTF16LEtoUTF8
	 * FullName:  StringConvertor::UTF16LEtoUTF8
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const wchar_t * utf16_str
	 * Parameter: std::string & utf8_str
	 *********************************************************************************/
	static int UTF16LEtoUTF8(const wchar_t* utf16_str, std::string& utf8_str);

	/*********************************************************************************
	 * Method:    UTF16LEtoUTF8
	 * FullName:  StringConvertor::UTF16LEtoUTF8
	 * Access:    public static
	 * Returns:   std::string
	 * Qualifier:
	 * Parameter: const wchar_t * utf16_str
	 *********************************************************************************/
	static std::string UTF16LEtoUTF8(const wchar_t* utf16_str);


	static int UTF8toGBK(const char* utf8_str, char** gbk_str);


	static int UTF8toGBK(const char* utf8_str, std::string& gbk_str);

	/*********************************************************************************
	 * Method:    GBKtoUTF8
	 * FullName:  StringConvertor::GBKtoUTF8
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const char * gbk_str
	 * Parameter: char * * utf8_str
	 *********************************************************************************/
	static int GBKtoUTF8(const char* gbk_str, char** utf8_str);

	/*********************************************************************************
	 * Method:    GBKtoUTF8
	 * FullName:  StringConvertor::GBKtoUTF8
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const char * gbk_str
	 * Parameter: std::string & utf8_str
	 *********************************************************************************/
	static int GBKtoUTF8(const char* gbk_str, std::string& utf8_str);

	/*********************************************************************************
	 * Method:    ANSItoUTF16LE
	 * FullName:  StringConvertor::ANSItoUTF16LE
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const char * ansi_str
	 * Parameter: std::wstring & utf16_str
	 *********************************************************************************/
	static int ANSItoUTF16LE(const char* ansi_str, std::wstring& utf16_str);

	/*********************************************************************************
	 * Method:    ANSItoUTF16LE
	 * FullName:  StringConvertor::ANSItoUTF16LE
	 * Access:    public static
	 * Returns:   std::wstring
	 * Qualifier:
	 * Parameter: const char * ansi_str
	 *********************************************************************************/
	static std::wstring ANSItoUTF16LE(const char* ansi_str);

	/*********************************************************************************
	 * Method:    UTF16LEtoANSI
	 * FullName:  StringConvertor::UTF16LEtoANSI
	 * Access:    public static
	 * Returns:   int
	 * Qualifier:
	 * Parameter: const wchar_t * utf16_str
	 * Parameter: std::string & ansi_str
	 *********************************************************************************/
	static int UTF16LEtoANSI(const wchar_t* utf16_str, std::string& ansi_str);

	/*********************************************************************************
	 * Method:    InitCodePageInfo
	 * FullName:  StringConvertor::InitCodePageInfo
	 * Access:    public static
	 * Returns:   void
	 * Qualifier:
	 *********************************************************************************/
	static void InitCodePageInfo();
};

#endif // kgl_string_encoder_h__