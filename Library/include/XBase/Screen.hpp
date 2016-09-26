/**
 * @file
 * @brief Screen型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_SCREEN_HPP)
#else
#define XBASE_INCLUDED_SCREEN_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/OS.hpp>

#if defined(XBASE_OS_MACOSX)
    #include <XBase/Screen_MacOSX.hpp>
#elif defined(XBASE_OS_IOS)
    #include <XBase/Screen_iOS.hpp>
#else
    #include <XBase/Screen_Default.hpp>
#endif

//------------------------------------------------------------
namespace XBase {
    class Display_EXT;
    struct ScreenPosPOD;
}

//------------------------------------------------------------
namespace XBase {
/// @name addtogroup XBase-System
//@{
    /**
     * @brief Displayが所持する描画領域。
     * @details
     * WindowsやMacOSXなどのWindowSystem環境では１つの Display に１つの Screen が存在します。 @n
     * NintendoDSなど2枚の描画領域を持つ環境では１つの Display に２つの Screen が存在します。 @n
     */
    class Screen : public ::XBase::NonCopyable
    {
    public:
        // コンストラクタ。システムが呼ぶ。
        Screen( Display_EXT& aOwner , uint aWidth , uint aHeight );
        
        /// @name 解像度
        //@{
        /// 横ピクセル数。
        uint width()const; 

        /// 縦ピクセル数。
        uint height()const;

        /**
         * @brief 指定の位置がスクリーン内かどうか判定する。
         * @return 0 <= aPos.x < width() && 0 <= aPos.y < height()
         */
        bool isContains( const ScreenPosPOD& aPos )const;
        //@}

        //============================================================
        // 内部実装用関数群。
        Display_EXT& display_();
        Screen_EXT& ext_();
        
    private:
        Display_EXT& mOwner;
        Screen_EXT mEXT;
        uint mWidth;
        uint mHeight;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
