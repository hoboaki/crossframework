/**
 * @file
 * @brief Keyboard型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_KEYBOARD_HPP)
#else
#define XBASE_INCLUDED_KEYBOARD_HPP

//------------------------------------------------------------
#include <XBase/KeyboardUpdateData.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /**
     * @brief キーボード。
     * @details
     * マスターとなるキーボードは HID が所持しています。 @n
     * @n
     * キーボードのコピーをアプリケーションが持つことによって
     * 「ポーズ中はキー情報を更新しないキーボード」といった
     * 特殊なキーボードを作成することができます。
     */
    class Keyboard
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// 何も押されていない状態のキーボードを作成。
        Keyboard();
        //@}

        /// @name 更新
        //@{
        /// 状態を更新する。
        void update( const KeyboardUpdateData& aData );

        /// 前回の更新データを取得する。
        const KeyboardUpdateData lastUpdateData()const;
        //@}

        /// @name 状態取得
        //@{
        bool isHold( KeyKind aKind )const;    ///< 押されているか。
        bool isTrigger( KeyKind aKind )const; ///< 押された瞬間か。
        bool isRepeat( KeyKind aKind )const;  ///< 押しっぱなしの状態で入力が入ったか。
        bool isPulse( KeyKind aKind )const;   ///< isTrigger() || isRepeat()。
        bool isRelease( KeyKind aKind )const; ///< 離された瞬間か。
        //@}

        /// @name ビットセット取得
        //@{
        const KeyBitSet hold()const;    ///< isHold() のビットセット。
        const KeyBitSet trigger()const; ///< isTrigger() のビットセット。
        const KeyBitSet repeat()const;  ///< isRepeat() のビットセット。
        const KeyBitSet pulse()const;   ///< isPulse() のビットセット。
        const KeyBitSet release()const; ///< isRelease() のビットセット。
        //@}

    private:
        KeyboardUpdateData mData;
        KeyBitSet mTrigger;
        KeyBitSet mRepeat;
        KeyBitSet mPulse;
        KeyBitSet mRelease;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
