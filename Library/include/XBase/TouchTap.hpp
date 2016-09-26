/**
 * @file
 * @brief TouchTap型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_TOUCHTAP_HPP)
#else
#define XBASE_INCLUDED_TOUCHTAP_HPP

//------------------------------------------------------------
#include <XBase/TouchTapUpdateData.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /**
     * @brief タッチのタップ入力。
     */
    class TouchTap
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        TouchTap();
        ~TouchTap();
        //@}

        /// @name 更新
        //@{
        /// 状態を更新する。
        void update( const TouchTapUpdateData& aData );

        /// 前回の更新データを取得する。
        const TouchTapUpdateData lastUpdateData()const;
        //@}

        /// @name 状態取得
        //@{
        /**
         * @brief タップ数を返す。
         * @details
         * 押されていなければ0、シングルタップなら1、ダブルタップなら2を返します。@n
         * 3以上のタップ数をサポートしている環境なら3以上の値を返します。@n
         */
        uint tapCount()const;

        /**
         * @brief 押している位置。
         * @details 離している状態なら最後に押していた位置を返します。
         */
        const ScreenPosPOD pos()const;

        bool isHold()const;    ///< 押されているか。
        bool isTrigger()const; ///< 押された瞬間か。
        bool isRelease()const; ///< 離された瞬間か。
        //@}

    private:
        TouchTapUpdateData mData;
        TouchTapUpdateData mPrevData;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
