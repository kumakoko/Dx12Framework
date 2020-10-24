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
#ifndef d3d12_depth_stencil_view_desc_ex_h__
#define d3d12_depth_stencil_view_desc_ex_h__

class D3D12DepthStencilViewDescEx : public D3D12_DEPTH_STENCIL_VIEW_DESC
{
public:
    /*********************************************************************************
     * @brief:
     * @return: 
     *********************************************************************************/
    D3D12DepthStencilViewDescEx();

    /*********************************************************************************
     * @brief:
     * @return: 
     * @param:  const D3D12_DEPTH_STENCIL_DESC1 & o
     *********************************************************************************/
    explicit D3D12DepthStencilViewDescEx(const D3D12_DEPTH_STENCIL_VIEW_DESC &o);
    
    /*********************************************************************************
     * @brief:
     * @return: void
     * @param:  const XMLElement * elem
     *********************************************************************************/
    void Init(const XMLElement* elem);
};


#endif // d3d12_depth_stencil_view_desc_ex_h__
