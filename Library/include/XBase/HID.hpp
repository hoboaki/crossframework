// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_HID_HPP)
#else
#define XBASE_INCLUDED_HID_HPP

//------------------------------------------------------------------------------
#include <XBase/NonCopyable.hpp>
#include <XBase/OS.hpp>

#if defined(XBASE_OS_WINDOWS)
    #include <XBase/HID_Windows.hpp>
#elif defined(XBASE_OS_MACOSX)
    #include <XBase/HID_MacOSX.hpp>
#elif defined(XBASE_OS_IOS)
    #include <XBase/HID_iOS.hpp>
#endif

//------------------------------------------------------------------------------
namespace XBase {
    class Display;
    class Keyboard;
    class Mouse;
    class Touch;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /// @brief HID(Human Interface Device)にアクセスするクラス。
    class HID : public NonCopyable
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// コンストラクタ。
        HID( Display& );
        /// デストラクタ。
        ~HID();
        //@}
        
        /// @name キーボードデバイス
        //@{
        /// キーボードの総数。
        uint           keyboardCount()const;

        /// 指定番目のキーボードを取得。
        const Keyboard keyboardAtIndex( uint aIndex )const;
        
        /// @brief 存在する環境なら0番のキーボードを取得する。
        /// @details 
        /// 存在しなければ空のキーボードを返す。
        const Keyboard keyboard()const;
        //@}
        
        /// @name マウスデバイス
        //@{
        /// マウスの総数。
        uint           mouseCount()const;

        /// 指定番目のマウスを取得。
        const Mouse mouseAtIndex( uint aIndex )const;
        
        /// @brief 存在する環境なら0番のマウスを取得する。
        /// @details 
        /// 存在しなければ空のマウスを返す。
        const Mouse mouse()const;
        //@}

        /// @name タッチデバイス
        //@{
        /// @brief この機器でサポートされているタップ数を取得する。
        /// @details 
        /// シングルタッチしかサポートしない環境は1、マルチタッチをサポートする環境では2以上の値が返ります。@n
        uint supportedTouchTapCount()const;

        /// タッチデバイスの総数。
        uint touchCount()const;

        /// 指定番目のタッチデバイスの取得。
        const Touch touchAtIndex( uint aIndex )const;
        
        /// @brief 存在する環境なら0番のタッチデバイスを取得する。
        /// @details 
        /// 存在しなければ空のタッチデバイスを返す。
        const Touch touch()const;
        //@}

        //============================================================
        // 内部実装用関数群。
        HID_EXT& ext_(); // 拡張。
    
    private:
        Display& mDisplay;
        HID_EXT  mEXT;
    };
//@}

} // namespace
#endif
// EOF
