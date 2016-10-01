// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLSHAPEIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMDLSHAPEIMPL_HPP

//------------------------------------------------------------------------------
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/SDKHeader.hpp>
#include "BinResMdlShape.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------------------------
namespace XG3D {
    // BinResMdlShapeとResMdlShapeの間にかますクラス。
    class ResMdlShapeImpl : public ::XBase::NonCopyable
    {
    public:
        struct VtxAttr
        {
            u16   glDataType;
            u16   glNormalize;
            const BinResMdlShape::VtxAttrInfo* info;
        };
        //============================================================
        const XDataPlus         xdata;
        const BinResMdlShape*   binPtr;
        VtxAttr vtxAttrs[ ResMdlShapeInputKind_TERMINATE ];
        GLuint idxBuffer;
        GLuint vtxAttrBuffer;
        GLuint idxGLDataType;

        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResMdlShapeImpl( const ::XData::XData& aXData , const BinResMdlShape* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResMdlShapeImpl();
        
        //============================================================
        void setup();
        void release();
    };

} // namespace
#endif
// EOF
