/**
 * @file
 * @brief FrameCounter型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_FRAMECOUNTER_HPP)
#else
#define XBASE_INCLUDED_FRAMECOUNTER_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
    
//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Util
//@{
    /// フレームカウンター。
    class FrameCounter
    {
    public:
        /// @name コンストラクタ
        //@{
        FrameCounter(); ///< 総フレーム数0で作成。
        FrameCounter( uint aTotalFrame ); ///< 総フレーム数を指定して作成。
        //@{

        /// @name リセット
        //@{
        void reset(); ///< 設定済みの総フレーム数でリセット。
        void reset( uint aTotalFrame ); ///< 新しい総フレーム数を指定してリセット。
        //@}

        /// @name 更新
        //@{
        /**
         * @brief フレームを1進める。
         * @details isEnd() 状態なら何もしません。
         */
        void advance();

        /**
         * @brief フレームを1進める。
         * @details isEnd() 状態で呼ぶとエラーになります。
         */
        void advanceStrict();

        /**
         * @brief 最終フレームまで進める。
         */
        void toEnd();
        //@}

        /// @name 取得
        //@{
        uint  frame()const; ///< 現在のフレーム数。
        uint  totalFrame()const; ///< 総フレーム数。
        bool  isEnd()const;     ///< 現在のフレームが総フレームに達しているか。
        bool  isCounting()const; ///< 現在のフレームが総フレームに達していないか。
        float rateFrame()const; ///< 0.0f <= 1.0f の範囲に正規化されたフレーム。
        float invRateFrame()const; ///< 1.0f - rateFrame()。
        //@}

    private:
        uint mFrame;
        uint mTotalFrame;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
