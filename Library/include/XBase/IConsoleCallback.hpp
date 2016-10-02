// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ICONSOLECALLBACK_HPP)
#else
#define XBASE_INCLUDED_ICONSOLECALLBACK_HPP

#include <cstdarg>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Debug
//@{
/// コンソール用コールバックインターフェースクラス。
class IConsoleCallback
{
public:
    virtual ~IConsoleCallback();

    /// @brief コンソールに書き込み要求があったときに呼ばれる。
    /// @param aFormat printfフォーマット文字列。
    /// @param aArg aFormatの引数。
    virtual void onWrite(const char* aFormat, va_list aArg) = 0;
};
//@}

} // namespace
#endif
// EOF
