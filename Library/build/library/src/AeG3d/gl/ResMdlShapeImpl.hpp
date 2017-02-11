// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLSHAPEIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLSHAPEIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include "BinResMdlShape.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMdlShapeとResMdlShapeの間にかますクラス。
class ResMdlShapeImpl : public ::ae::base::NonCopyable
{
public:
    struct VtxAttr
    {
        u16   glDataType;
        u16   glNormalize;
        const BinResMdlShape::VtxAttrInfo* info;
    };
    //============================================================
    const XdataPlus         xdata;
    const BinResMdlShape*   binPtr;
    VtxAttr vtxAttrs[ResMdlShapeInputKind::TERM];
    GLuint idxBuffer;
    GLuint vtxAttrBuffer;
    GLuint idxGLDataType;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlShapeImpl(const ::ae::xdata::Xdata& aXdata, const BinResMdlShape* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMdlShapeImpl();

    //============================================================
    void setup();
    void release();
};

}} // namespace
#endif
// EOF
