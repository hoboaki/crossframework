/**
 * @file
 * @brief IRuntimeErrorCallback型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_IRUNTIMEERRORCALLBACK_HPP)
#else
#define XBASE_INCLUDED_IRUNTIMEERRORCALLBACK_HPP

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Debug
//@{
    /// 実行時エラー用コールバックインターフェースクラス。
    class IRuntimeErrorCallback
    {
    public:
        // デストラクタ。
        virtual ~IRuntimeErrorCallback();

        /**
            * @brief エラーが起きたときに呼ばれる関数。
            * @details 
            * この関数ではアプリケーションを強制終了するなど致命的な時に実行したい処理を行ってください。
            */
        virtual void onRuntimeError()=0;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
