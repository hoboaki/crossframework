// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RUNTIMETEXCONTEXT_HPP)
#else
#define XG3D_INCLUDED_RUNTIMETEXCONTEXT_HPP

//------------------------------------------------------------------------------
#include <XBase/Enum.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResTexFormat.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Util
//@{
    /// RuntimeTex用コンテキスト。
    class RuntimeTexContext
    {
    public:
        /// @name 作成関数
        //@{
        static const RuntimeTexContext Create( ResTexFormat aFormat , uint aWidth , uint aHeight );
        //@}
        
        /// @name 取得
        //@{
        ResTexFormat format()const; ///< フォーマット。
        u16 width()const;  ///< 横ピクセル数。
        u16 height()const; ///< 縦ピクセル数。
        //@}

    private:
        RuntimeTexContext( ResTexFormat , uint aWidth , uint aHeight );
        //------------------------------------------------------------------------------
        ::XBase::Enum32< ResTexFormat > mFormat;
        u16 mWidth; 
        u16 mHeight;
    };
//@}

} // namespace
#endif
// EOF
