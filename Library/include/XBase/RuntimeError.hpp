// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_RUNTIMEERROR_HPP)
#else
#define XBASE_INCLUDED_RUNTIMEERROR_HPP

namespace XBase {
class IRuntimeErrorCallback;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Debug
//@{
    /// 実行時エラーを扱う空間。
struct RuntimeError
{
    /// @brief デフォルトで設定されているコールバックを取得する。
    /// @return コールバックオブジェクト。
    /// @see OnError
    /// @details デフォルトの実装はアプリケーションを強制終了します。
    static IRuntimeErrorCallback& DefaultCallback();

    /// @brief エラー時に使用するコールバックオブジェクトを設定する。
    /// @param aCallback 設定するコールバックオブジェクト。
    /// @see OnError
    static void SetCallback(IRuntimeErrorCallback& aCallback);

    /// @brief エラーが起きたときに呼ばれる関数。
    /// @details 実行時エラーが有効なビルドバージョンなら設定されているコールバックを呼びます。
    static void OnError();
};
//@}

} // namespace
#endif
// EOF
