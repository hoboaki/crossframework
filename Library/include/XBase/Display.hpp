// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DISPLAY_HPP)
#else
#define XBASE_INCLUDED_DISPLAY_HPP

//------------------------------------------------------------------------------
#include <XBase/DisplayContext.hpp>
#include <XBase/OS.hpp>
#include <XBase/Screen.hpp>

#if defined(XBASE_OS_WINDOWS)
    #include <XBase/Display_Windows.hpp>
#elif defined(XBASE_OS_MACOSX)
    #include <XBase/Display_MacOSX.hpp>
#elif defined(XBASE_OS_IOS)
    #include <XBase/Display_iOS.hpp>
#else
    #include <XBase/Display_Default.hpp>
#endif
//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-System
//@{

    /// @class XBase::Display
    /// @brief ディスプレイ。
    /// @details 
    /// ここでいうディスプレイとはWindowsやMacOSX環境では１つのウィンドウのことを指します。@n
    /// ウィンドウという概念がない環境では仮想的なウィンドウが存在するとします。@n
    /// @n
    /// ディスプレイは1つ以上のスクリーンを所持します。 @n
    /// WindowsやMacOSX環境では１つのウィンドウが１つのスクリーンを所持すると考えます。@n
    /// Nintendo DSなど1つのハードに2つ以上の画面が存在するハードではスクリーンが画面の数だけ所持すると考えます。@n
    class Display
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        Display( const DisplayContext& );
        ~Display();
        //@}

        /// @name スクリーン
        //@{
        uint screenCount()const; ///< スクリーンの総数を取得する。
        Screen& screenAtIndex( uint aIndex ); ///< 指定番目のスクリーンを取得する。
        Screen& mainScreen(); ///< メインとなるスクリーンを取得する。
        //@}

        /// @name コントロール
        //@{
        /// 表示する。
        void show();
        //@}

        /// @name 状態取得
        //@{        
        /// ディスプレイが閉じられたか。
        bool isClosed()const;
        //@}

        //============================================================
        // 内部実装用関数群。
        const DisplayContext context_()const; // コンテキストの取得。
        Display_EXT& ext_(); // 拡張。

    private:
        DisplayContext mContext;
        Display_EXT mEXT;
    };

//@}

} // namespace
#endif
// EOF
