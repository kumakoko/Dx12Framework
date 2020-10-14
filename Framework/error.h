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
* \file kgl_error.h
* \date 2017/12/31 13:38
*
* \author www.xionggf.com
* Contact: sun_of_lover@sina.com
*
* \brief
*
* TODO: 继承自xgf::Error的异常类,由各调用模块抛出
*
* \note
*/
#ifndef kgl_error_h__
#define kgl_error_h__


class DX12_FRAMEWORK_DLL Error : public std::exception
{
public:
    /*********************************************************************************
     * Method:    Error
     * FullName:  kgl::Error::Error
     * Access:    public
     * Returns:
     * Qualifier:
     * Parameter: const std::wstring & message
     *********************************************************************************/
    Error(const std::wstring& message);

    /*********************************************************************************
     * Method:    Error
     * FullName:  kgl::Error::Error
     * Access:    public
     * Returns:
     * Qualifier: 错误消息字符串
     * Parameter: const std::wstring & message
     * Parameter: const char * file 一般传__FILE__值进去
     * Parameter: uint32_t line 一般传__LINE__值进去
     *********************************************************************************/
    Error(const std::wstring& message, const char* file, uint32_t line);

    /*********************************************************************************
     * Method:    Error
     * FullName:  kgl::Error::Error
     * Access:    public
     * Returns:
     * Qualifier:
     * Parameter: HRESULT error
     * Parameter: const char * file
     * Parameter: uint32_t line
     *********************************************************************************/
    Error(HRESULT error, const char* file, uint32_t line);

    /// <summary>
    /// Notifies this instance.
    /// </summary>
    virtual void Notify() const;

    /// <summary>
    ///  通知用户出错了,提供一个二选一对话框给用户选择
    /// </summary>
    virtual void Prompt() const;

    /*********************************************************************************
     * Method:    GRS_THROW_IF_FAILED
     * FullName:  Error::GRS_THROW_IF_FAILED
     * Access:    public static 
     * Returns:   void
     * Qualifier:
     * Parameter: HRESULT hr
     * Parameter: const char * file
     * Parameter: int line
     *********************************************************************************/
    static void GRS_THROW_IF_FAILED(HRESULT hr, const char* file, int line);

    static void ThrowTinyXMLException(XMLError error, const std::wstring& xml_file, const char* file, int line);
protected:
    /// <summary>
    /// 组装错误消息,返回错误消息字符串
    /// </summary>
    /// <returns>错误消息字符串</returns>
    virtual std::wstring AssembleOutput() const;

    enum EXCEPTION_TYPE
    {
        EXCEPTION_MESSAGE,  ///< 返回错误消息
        EXCEPTION_REGULAR,  ///< 返回错误消息,出错的代码文件和行
        EXCEPTION_DX12    ///< 返回错误消息,出错的代码文件和行以及渲染器给的错误代码
    };

    ///错误类型
    EXCEPTION_TYPE type_;

    /// 对话框窗口标题
    std::wstring title_;

    /// 错误消息字符串
    std::wstring message_;

    /// 发生错误的代码文件名

    std::string file_;

    /// 发生错误的代码行
    uint32_t line_;
};



#endif // kgl_error_h__